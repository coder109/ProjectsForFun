import argparse
from tqdm import tqdm


def parseLine(line: str, output_fp):
    # Titles
    if line.startswith("#"):
        output_fp.write("<h1>" + parseLine(line[2:], output_fp) + "</h1>\n")
    elif line.startswith("##"):
        output_fp.write("<h2>" + parseLine(line[3:], output_fp) + "</h2>\n")
    elif line.startswith("###"):
        output_fp.write("<h3>" + parseLine(line[4:], output_fp) + "</h3>\n")
    elif line.startswith("####"):
        output_fp.write("<h4>" + parseLine(line[5:], output_fp) + "</h4>\n")
    elif line.startswith("#####"):
        output_fp.write("<h5>" + parseLine(line[6:], output_fp) + "</h5>\n")
    elif line.startswith("######"):
        output_fp.write("<h6>" + parseLine(line[7:], output_fp) + "</h6>\n")
    # Lists
    elif line.startswith("-"):
        output_fp.write("<li>" + parseLine(line[2:], output_fp) + "</li>\n")
    # Italic
    elif line.startswith("*"):
        output_fp.write("<i>" + parseLine(line[1:], output_fp) + "</i>\n")
    # Bold
    elif line.startswith("**"):
        output_fp.write("<b>" + parseLine(line[2:], output_fp) + "</b>\n")
    # Code
    elif line.startswith("```"):
        output_fp.write("<pre>" + parseLine(line[3:], output_fp) + "</pre>\n")
    # Link
    elif line.startswith("["):
        output_fp.write("<a href=\"" + parseLine(line[1:], output_fp) + "\">" + parseLine(line[1:], output_fp) + "</a>\n")
    # Image
    elif line.startswith("!"):
        output_fp.write("<img src=\"" + parseLine(line[2:], output_fp) + "\">\n")
    else:
        output_fp.write(line)

def parse(lines: list[str], output_fp, css_file) -> str:
    output_fp.write("<html>\n")
    for line in tqdm(lines):
        parseLine(line, output_fp)
    if css_file is not None:
        output_fp.write("<link rel=\"stylesheet\" href=\"" + css_file + "\">\n")
    output_fp.write("</html>")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--input_file", "-i", type=str, required=True)
    parser.add_argument("--css_file", "-c", type=str, default="basic.css")
    parser.add_argument("--output_file", "-o", type=str, required=True)
    args = parser.parse_args()

    with open(args.input_file, "r") as f:
        input_lines = f.readlines()
    output_fp = open(args.output_file, "w")

    output = parse(input_lines, output_fp, args.css_file)