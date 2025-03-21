import argparse
from modules import Transformer
from input import InputGenerator


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    args = parser.parse_args()
    t = Transformer()
    i = InputGenerator()
    x = i.generate()
    y = t(x, x)
    print(y)