# Instructions to Convert Report.md to PDF

## Option 1: Using Pandoc (Recommended)

1. Install Pandoc: https://pandoc.org/installing.html

2. Run this command in the project directory:
```bash
pandoc Report.md -o Report.pdf --pdf-engine=xelatex -V geometry:margin=1in
```

Or if you have LaTeX installed:
```bash
pandoc Report.md -o Report.pdf
```

## Option 2: Using Online Converters

1. Go to https://www.markdowntopdf.com/ or https://dillinger.io/
2. Copy the contents of Report.md
3. Export as PDF

## Option 3: Using VS Code

1. Install "Markdown PDF" extension in VS Code
2. Open Report.md
3. Right-click and select "Markdown PDF: Export (pdf)"

## Option 4: Using Google Docs

1. Copy the contents of Report.md
2. Paste into Google Docs
3. File → Download → PDF

## Option 5: Using Microsoft Word

1. Open Report.md in Word
2. File → Save As → PDF

---

**Note:** Remember to add your name to the report before converting to PDF!

