#!/bin/python3

''' Program to compile black and white images into a heatmap '''

import imageio as iio
import argparse

def CreateArgs():
    ''' Helper function to create argparser object '''
    #create parser object
    parser = argparse.ArgumentParser(description="A tool to compile black and white images into a heatmap.")

    #input directory
    parser.add_argument("input", nargs="?", default=".", help="Directory to scan images from (default: png and jpg).")

    #file type
    parser.add_argument("--type", nargs="+", action="extend", type=str, default=None, help="The desired image filetype (default: png and jpg).")

    #reverser flag
    parser.add_argument("-r", "--reverse", action="store_true", help="Reverse black and white for heatmap (default: heatmap is of black pixels).")

    return parser

if __name__ == "__main__":
    #parse args
    parser = CreateArgs()
    args = parser.parse_args()
    
    #store args
    path = str(args.input)
    filetype = args.type
    if filetype is None: #default values
        filetype = ["png","jpg","jpeg"]
    reverse = args.reverse

