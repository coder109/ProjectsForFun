from PIL import Image
import argparse

def convert(args):
    targetWidth = args.target_width
    # Check if the file exists
    try:
        f = Image.open(args.file)
    except:
        print("The file seems to be non-existent. Aborting...\n")
        exit(-1)

    # Get information of the picture
    width, height = f.size[0], f.size[1]

    # Prepare target chars
    targetChar =" .,:;+*%S#@"

    # Get the target height
    ratio = (int)(width / height)
    targetHeight = targetWidth * ratio
    f = f.resize((targetWidth, targetHeight))
    f = f.convert("L") # Convert to black and white

    # Get the interval to sample the pixel
    heightInterval = (int)(targetHeight / height)
    widthInterval = (int)(targetWidth / width)
    if(heightInterval == 0):
        heightInterval = 1
    if(widthInterval == 0):
        widthInterval = 1

    # Convert
    for i in range(0, targetHeight, heightInterval):
        for j in range(0, targetWidth, widthInterval):
            greyVal = f.getpixel((j,i))
            # Apply character based on the grey value
            greyVal = int(greyVal * (len(targetChar) - 1) / 255)
            if args.out_file:
                with open(args.out_file, "a") as f:
                    f.write(targetChar[greyVal])
            print(targetChar[greyVal], end="")
        if args.out_file:
            with open(args.out_file, "a") as f:
                f.write("\n")
        print("\n", end="")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--file", "-f", type=str, help="The file to be processed.")
    parser.add_argument("--target_width", "-t", type=int, help="The target width of the output.")
    parser.add_argument("--out_file", "-o", type=str, help="The output file. If not provided, the output will be only printed to the console.")
    args = parser.parse_args()

    assert args.file and args.target_width

    convert(args)