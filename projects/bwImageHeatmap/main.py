#!/bin/python3

''' Program to compile black and white images into a heatmap '''

import os
import imageio.v3 as iio
import argparse
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

def GetImages(path, filetype):
    '''
    Helper function to traverse a directory to obtain its images and convert to numpy array

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
    images = [] #array of images
    #traverse directory
    for f in os.scandir(path):
        if not f.is_file(): continue #skip if not file
        
        #obtain file name
        fname = os.path.basename(f.name)
        #skip if not desired filetype
        if fname.split(".")[-1] not in filetype: continue
        #skip if heatmap
        if "heatmap" in fname: continue
        fname = f"{path}/{fname}"

        #convert to 2d array
        _image = iio.imread(fname)
        _arr = np.asarray(_image)

        images.append(_arr)

    return images

def CreateHeatmap(images, cmap="rocket", reverse=True, output="./heatmap.png"):
    '''
    Create a heatmap from a list of images as 2d numpy arrays

    parameters:
        - name: images
          type: array of numpy arrays
          description: The list of images as 2d pixel arrays to create the heatmap from

        - name: cmap
          type: string
          example: "rocket", "gray"
          description: The seaborn colormap to use for the heatmap

        - name: reverse
          type: bool
          example: False, True
          description: Whether or not to reverse the heatmap

        - name: output
          type: string
          example: "path/to/out-heatmap.png"
          description: The destination name of the heatmap file
    '''
    #initialize heatmap
    _s = images[0].shape
    _valShape = (_s[0], _s[1])
    #valuemap is a float [0,1] to construct heatmap from
    valuemap = np.zeros(_valShape)
    if reverse: valuemap = np.ones(_valShape)

    #create valuemap
    for im in images:
        #loop through each pixel
        for iy, ix, iz in np.ndindex(im.shape):
            #skip if empty
            if (im[iy, ix] == 0).all(): continue

            #normalize to one
            _norm = im[iy, ix, iz]/255
            #scale to images count
            scale = _norm/len(images)

            #add to heatmap values
            if reverse: valuemap[iy, ix] -= scale
            else: valuemap[iy, ix] += scale

    #generate heatmap
    plt.figure(figsize=(6,6), dpi=600)
    heatmap = sns.heatmap(valuemap, square=True, xticklabels=False, yticklabels=False, cmap=cmap.lower())
    heatmapFig = heatmap.get_figure()
    heatmapFig.savefig(output)

def CreateArgs():
    ''' Helper function to create argparser object '''
    #create parser object
    parser = argparse.ArgumentParser(description="A tool to compile black and white images into a heatmap.")

    #input directory
    parser.add_argument("input", nargs="?", default=".", help="Directory to scan images from (default: png and jpg).")

    #output file
    parser.add_argument("-o", "--output", type=str, default="./heatmap.png", help="The file to output the heatmap to.")

    #file type
    parser.add_argument("--type", nargs="+", action="extend", type=str, default=None, help="The desired image filetype (default: png and jpg).")

    #reverser flag
    parser.add_argument("-r", "--reverse", action="store_false", help="Reverse black and white for heatmap (default: heatmap is of black pixels).")

    #colormap
    parser.add_argument("-c", "--cmap", action="store", type=str, default="rocket", help="The seaborn colormap to use in the heatmap")

    return parser

if __name__ == "__main__":
    #parse args
    parser = CreateArgs()
    args = parser.parse_args()
    
    #store args
    path = str(args.input)
    out = args.output
    filetype = args.type
    if filetype is None: #default values
        filetype = ["png","jpg","jpeg"]
    reverse = args.reverse
    cmap = args.cmap

    #get images and convert to np array
    images = GetImages(path, filetype)

    #construct heatmap
    CreateHeatmap(images, cmap, reverse, out)
