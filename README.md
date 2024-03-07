# F28HS Coursework 1

H00458396: HSDEC MEDIAN NORM

# Image Processing Coursework

This project implements a basic image processing technique in C, includes median filter (apply_MEDIAN) and normalization (apply_NORM).

## Overview 
* **Median Filter (apply_MEDIAN):** Smoothens the image by replacing each pixel's value with the median of its neighbors in 1x1 matrix (top, bottom, left, right,).
* **Normalization (apply_NORM):** Rescales pixel values to the range of 0-255 for better visualization and consistency.

## Prerequisits 
1. Using any linux machine (WSL/ Virtual Machine also works)
2. Root access to the program by the computer (this can be done with 'chmod -x ./process' for example)
3. Any image file in '.hsdec' format in the same folder as the program (i've included 2 example images and their output ppm image in the folder). 

## Usage
1. Compile the code using the already included makefile. eg. run - 'make'
2. Run the code using './process INPUTFILENAME OUTPUTFILENAME'. eg. run './process portrait.hsdec newPortrait.hsdec'
3.Convert the output file from '.hsdec' to '.ppm' using the already included 'hsconvert.py' file. eg. run './hsconvert -f PPM newPortrait.hsdec viewPortrait.ppm'
4. View the output image using any compatible image viewer in your machine.

## Dependencies
* Standard C libraries (no external dependencies)