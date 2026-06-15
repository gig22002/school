#!/bin/python3

''' Program to compile black and white images into a heatmap '''

import os
import imageio as iio
import argparse

def GetImages(path, filetype):
    '''
    Helper function to traverse a directory to obtain its images

    parameters:
        - name: path
          type: string
          example: /path/to/images
          description: The directory where the images are stored

        - name: filetype
          type: array of strings
          example: ["png","jpg"]
          description: The file extensions to look for
    '''
    #traverse directory
    for f in os.scandir(path):
        if not f.is_file(): continue #skip if not file
        
        #obtain file name
        fname = os.path.basename(f.name)
        #skip if not desired filetype
        if fname.split(".")[-1] not in filetype: continue

        fname = f"{path}/{fname}"

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

    GetImages(path, filetype)
