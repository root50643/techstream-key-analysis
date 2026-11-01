// Export selected functions with pseudocode, instructions and references.
// @category TechstreamKeyResearch
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.util.*;
import com.google.gson.GsonBuilder;

public class ExportKeyEvidence extends GhidraScript {
    Map<String,Object> row(Object... args) {
        Map<String,Object> r = new LinkedHashMap<>();
        for(int i=0;i<args.length;i+=2) r.put((String)args[i],args[i+1]);
        return r;
    }
    public void run() throws Exception {
        String[] args=getScriptArgs();
        Path out=Paths.get(args[0]); Files.createDirectories(out);
        DecompInterface dec=new DecompInterface(); dec.openProgram(currentProgram);
        List<Object> funcs=new ArrayList<>();
        try {
            for(int n=1;n<args.length;n++) {
                Address address=toAddr(args[n]);
                Function f=getFunctionAt(address);
                if(f==null) f=getFunctionContaining(address);
                if(f==null) { disassemble(address); f=createFunction(address,"FUN_"+address); }
                if(f==null) throw new IllegalStateException("No function: "+address);
                DecompileResults result=dec.decompileFunction(f,60,monitor);
                String c=result.getDecompiledFunction()==null?result.getErrorMessage():result.getDecompiledFunction().getC();
                Files.writeString(out.resolve(f.getEntryPoint()+".c"),c,StandardCharsets.UTF_8);
                StringBuilder asm=new StringBuilder();
                InstructionIterator ii=currentProgram.getListing().getInstructions(f.getBody(),true);
                while(ii.hasNext()) {
                    Instruction i=ii.next();
                    asm.append(i.getAddress()).append("  ").append(i.toString());
                    for(Reference r:i.getReferencesFrom()) {
                        Address t=r.getToAddress();
                        Symbol s=getSymbolAt(t); Data d=getDataAt(t);
                        if(s!=null) asm.append(" ; ").append(s.getName());
                        if(d!=null && d.getValue() instanceof String) asm.append(" = ").append(d.getValue());
                    }
                    asm.append("\n");
                }
                Files.writeString(out.resolve(f.getEntryPoint()+".asm.txt"),asm.toString(),StandardCharsets.UTF_8);
                List<String> refs=new ArrayList<>();
                for(Reference r:getReferencesTo(f.getEntryPoint())) refs.add(r.getFromAddress()+" "+r.getReferenceType());
                funcs.add(row("requested",args[n],"entry",f.getEntryPoint().toString(),"name",f.getName(),"complete",result.decompileCompleted(),"references",refs));
            }
        } finally { dec.dispose(); }
        Files.writeString(out.resolve("index.json"),new GsonBuilder().setPrettyPrinting().create().toJson(row("program",currentProgram.getName(),"image_base",currentProgram.getImageBase().toString(),"functions",funcs)),StandardCharsets.UTF_8);
    }
}
