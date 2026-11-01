using System;
using System.Runtime.InteropServices;
using System.Text;

// Compile with the 32-bit .NET Framework csc.exe, /platform:x86.
// Calls the installed library; does not patch files or connect to a vehicle.
public static class NativeProbe {
    [DllImport("kernel32", CharSet=CharSet.Unicode, SetLastError=true)]
    static extern IntPtr LoadLibraryW(string path);
    [DllImport("kernel32", CharSet=CharSet.Ansi, ExactSpelling=true, SetLastError=true)]
    static extern IntPtr GetProcAddress(IntPtr module, string name);
    [DllImport("kernel32", CharSet=CharSet.Unicode, SetLastError=true)]
    static extern bool SetDllDirectoryW(string path);
    [UnmanagedFunctionPointer(CallingConvention.ThisCall, CharSet=CharSet.Ansi)]
    delegate int Registration(IntPtr instance, string a, string b, string c,
                              string d, string e, StringBuilder result);
    [UnmanagedFunctionPointer(CallingConvention.StdCall, CharSet=CharSet.Ansi)]
    delegate void DecodeRegion(int shift, int length, string encoded, [Out] byte[] output);
    public static int Main(string[] args) {
        if(args.Length != 3) { Console.Error.WriteLine("NativeProbe BIN_DIRECTORY PART1 PART2"); return 2; }
        SetDllDirectoryW(args[0]);
        if(args[1] == "--decode-region") {
            IntPtr versatile=LoadLibraryW(System.IO.Path.Combine(args[0],"IT3Versatile.dll"));
            if(versatile==IntPtr.Zero) throw new System.ComponentModel.Win32Exception();
            IntPtr decodeFn=GetProcAddress(versatile,"DecryptByRotatShiftVariable");
            if(decodeFn==IntPtr.Zero) throw new System.ComponentModel.Win32Exception();
            var decode=(DecodeRegion)Marshal.GetDelegateForFunctionPointer(decodeFn,typeof(DecodeRegion));
            var decoded=new byte[args[2].Length+1];
            decode(13,args[2].Length,args[2],decoded);
            Console.WriteLine("{\"decoded_value\":\""+Encoding.ASCII.GetString(decoded,0,args[2].Length)+"\"}");
            return 0;
        }
        IntPtr module=LoadLibraryW(System.IO.Path.Combine(args[0],"tiswebapi.dll"));
        if(module==IntPtr.Zero) throw new System.ComponentModel.Win32Exception();
        IntPtr fn=GetProcAddress(module,"?TisServiceRegistration@CWebService@@QAEHPBD0000PAD@Z");
        if(fn==IntPtr.Zero) throw new System.ComponentModel.Win32Exception();
        var call=(Registration)Marshal.GetDelegateForFunctionPointer(fn,typeof(Registration));
        var output=new StringBuilder(1024);
        int status=call(IntPtr.Zero,args[1],args[2],null,null,null,output);
        Console.WriteLine("{\"status\":"+status+",\"native_hash\":\""+output+"\"}");
        return status==1 ? 0 : 1;
    }
}
