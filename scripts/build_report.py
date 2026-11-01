"""Build the Traditional Chinese PDF from the repository Markdown report."""
import argparse
from html import escape
from pathlib import Path
import re

from reportlab.lib import colors
from reportlab.lib.enums import TA_LEFT
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import ParagraphStyle
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from reportlab.platypus import (SimpleDocTemplate, Paragraph, Spacer, Table,
                               TableStyle, Image, Preformatted, KeepTogether)

ROOT = Path(__file__).resolve().parents[1]
NAVY = colors.HexColor("#15304A")
TEAL = colors.HexColor("#137C83")
INK = colors.HexColor("#243747")


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument("--font", type=Path, required=True)
    p.add_argument("--bold-font", type=Path, required=True)
    p.add_argument("--output", type=Path, default=ROOT / "output/pdf/techstream-key-analysis.zh-TW.pdf")
    args = p.parse_args()
    pdfmetrics.registerFont(TTFont("TC", str(args.font)))
    pdfmetrics.registerFont(TTFont("TCBold", str(args.bold_font)))
    pdfmetrics.registerFontFamily("TC", normal="TC", bold="TCBold")
    body = ParagraphStyle("body", fontName="TC", fontSize=9.5, leading=15.5,
                          textColor=INK, wordWrap="CJK", spaceAfter=7)
    title = ParagraphStyle("title", parent=body, fontName="TCBold", fontSize=22,
                           leading=31, textColor=NAVY, spaceAfter=16)
    h2 = ParagraphStyle("h2", parent=body, fontName="TCBold", fontSize=14,
                        leading=21, textColor=TEAL, spaceBefore=16,
                        spaceAfter=9, keepWithNext=True)
    cell = ParagraphStyle("cell", parent=body, fontSize=8, leading=12, spaceAfter=0)
    caption = ParagraphStyle("caption", parent=body, fontSize=8, leading=12,
                             textColor=colors.HexColor("#617182"), spaceAfter=12)
    code = ParagraphStyle("code", fontName="Courier", fontSize=7.5, leading=11,
                          textColor=NAVY, leftIndent=8, rightIndent=8,
                          borderPadding=9, backColor=colors.HexColor("#F0F4F8"),
                          spaceBefore=4, spaceAfter=10)
    source = ROOT / "docs/report.zh-TW.md"
    lines = source.read_text(encoding="utf-8").splitlines()
    story = []
    width = A4[0] - 96

    def inline(s):
        s = re.sub(r"\[([^\]]+)\]\([^)]+\)", r"\1", s)
        s = escape(s)
        s = re.sub(r"`([^`]+)`", r'<font color="#15304A">\1</font>', s)
        return re.sub(r"\*\*([^*]+)\*\*", r"<b>\1</b>", s)

    i = 0
    while i < len(lines):
        line = lines[i].strip()
        if not line:
            i += 1
            continue
        if line.startswith("# "):
            story.append(Paragraph(inline(line[2:]), title)); i += 1
        elif line.startswith("## "):
            story.append(Paragraph(inline(line[3:]), h2)); i += 1
        elif line.startswith("```"):
            code_lines = []; i += 1
            while i < len(lines) and not lines[i].startswith("```"):
                text = lines[i]
                # Wrap long command lines at spaces; keep hash vectors intact.
                while len(text) > 97 and " " in text[:97]:
                    at = text.rfind(" ", 0, 97)
                    code_lines.append(text[:at]); text = "  " + text[at+1:]
                code_lines.append(text); i += 1
            story.append(KeepTogether([Preformatted("\n".join(code_lines), code)])); i += 1
        elif line.startswith("|"):
            rows = []
            while i < len(lines) and lines[i].strip().startswith("|"):
                cells = [s.strip() for s in lines[i].strip().strip("|").split("|")]
                if not all(re.fullmatch(r"[:\- ]+", s) for s in cells):
                    rows.append([Paragraph(inline(s), cell) for s in cells])
                i += 1
            count = len(rows[0])
            weights = {2: [0.29, 0.71], 3: [0.30, 0.19, 0.51],
                       4: [0.13, 0.10, 0.32, 0.45]}.get(count, [1 / count] * count)
            table = Table(rows, colWidths=[width*w for w in weights], repeatRows=1,
                          hAlign="LEFT")
            table.setStyle(TableStyle([
                ("BACKGROUND", (0, 0), (-1, 0), colors.HexColor("#E5EFF2")),
                ("ROWBACKGROUNDS", (0, 1), (-1, -1), [colors.white, colors.HexColor("#F7F9FB")]),
                ("LINEBELOW", (0, 0), (-1, 0), 0.7, TEAL),
                ("VALIGN", (0, 0), (-1, -1), "TOP"),
                ("LEFTPADDING", (0, 0), (-1, -1), 7),
                ("RIGHTPADDING", (0, 0), (-1, -1), 7),
                ("TOPPADDING", (0, 0), (-1, -1), 7),
                ("BOTTOMPADDING", (0, 0), (-1, -1), 7),
            ]))
            prior = []
            if story and isinstance(story[-1], Paragraph) and story[-1].style.name == "h2":
                prior = [story.pop()]
            story.extend([KeepTogether(prior + [table]), Spacer(1, 10)])
        elif line.startswith("!["):
            match = re.fullmatch(r"!\[(.*?)\]\((.*?)\)", line)
            path = (source.parent / match[2]).resolve()
            img = Image(str(path))
            ratio = min(width / img.imageWidth, 300 / img.imageHeight)
            img.drawWidth, img.drawHeight = img.imageWidth*ratio, img.imageHeight*ratio
            img.hAlign = "CENTER"
            group = [Spacer(1, 5), img, Spacer(1, 6)]
            if i+2 < len(lines) and lines[i+2].startswith("圖 "):
                group.append(Paragraph(inline(lines[i+2]), caption)); i += 2
            story.append(KeepTogether(group)); i += 1
        else:
            paragraph = [line]; i += 1
            while i < len(lines) and lines[i].strip() and not lines[i].startswith(("#", "|", "```", "![")):
                if re.match(r"^[0-9]+\. ", lines[i]):
                    break
                paragraph.append(lines[i].strip()); i += 1
            story.append(Paragraph(inline(" ".join(paragraph)), body))

    def page(canvas, doc):
        canvas.setStrokeColor(TEAL); canvas.setLineWidth(1.5)
        canvas.line(48, A4[1]-33, A4[0]-48, A4[1]-33)
        canvas.setFont("TC", 7.5); canvas.setFillColor(colors.HexColor("#617182"))
        canvas.drawString(48, A4[1]-25, "TECHSTREAM 18 | New Key 演算法分析")
        canvas.drawString(48, 25, "2026-11-02  |  反編譯與本機實測")
        canvas.drawRightString(A4[0]-48, 25, str(doc.page))

    args.output.parent.mkdir(parents=True, exist_ok=True)
    doc = SimpleDocTemplate(str(args.output), pagesize=A4, rightMargin=48,
                            leftMargin=48, topMargin=51, bottomMargin=47,
                            title="Techstream 18.00.008 New Key 演算法分析報告",
                            author="Techstream Key Analysis", pageCompression=1)
    doc.build(story, onFirstPage=page, onLaterPages=page)
    print(args.output)


if __name__ == "__main__":
    main()
