# Black and White Image Heatmap

## Overview

This is a biology project for my friend Abby, who needed a heatmap for a series of black and white, flattened images of frogs. This program converts an array of black and white rasters and scales a heatmap accordingly. Note that centering and image normalization must be performed by the user.

To rotate the images, I used [this tool](https://www.batchimagetools.com/rotate). Using this, you can individually rotate each one to normalize them to the same orientation.  
In order to center the images, I used [this tool](https://www.batchpngtools.com/center-png). Be sure that the image size is the same for all images.

## Usage

Install all required dependencies with `pip install -r requirements.txt`.

Run the program with `python3 main.py`.

This program, by default, iterates over the current working directory. You can specify a specific directory as an argument, however.

Optional Arguments:

`-r`, `--reverse`: Invert the heatmap.  
`-c VALUE`, `--cmap VALUE`: Specify the Seaborn colormap to use. Default=rocket  
`--type VALUE1 VALUE2 ...`: Specify the filetype(s) to use. Default=[png, jpg, jpeg]

###### Created by Gio Girasoli 6/15/26
