#!/bin/python3

''' Program to compile black and white images into a heatmap '''

import os
import imageio.v3 as iio
import argparse
import numpy as np

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
        fname = f"{path}/{fname}"

        #convert to 2d array
        _image = iio.imread(fname)
        _arr = np.asarray(_image)

        images.append(_arr)

    return images

def CreateHeatmap(images):
    '''
    Create a heatmap from a list of images as 2d numpy arrays

    parameters:
        - name: images
          type: array of numpy arrays
          description: The list of images as 2d pixel arrays to create the heatmap from
    '''
    #initialize heatmap
    _s = images[0].shape
    _valShape = (_s[0], s[1])
    _shape = (_s[0], _s[1], _s[2])
    #valuemap is a float [0,1] to construct heatmap from
    valuemap = np.zeros(_valShape)
    #heatmap sized to images
    heatmap = np.zeros(_shape, dtype=np.int8)

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
            valuemap[iy, ix] += scale
            

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

    #get images and convert to np array
    images = GetImages(path, filetype)

    #construct heatmap
    CreateHeatmap(images)
