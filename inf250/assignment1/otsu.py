# -*- coding: utf-8 -*-

"""
OTSU thresholding
Coursework as part of INF250 at NMBU (Autumn 2017).

Based on the provided skeleton by Yngve Mardal Moe
"""

__author__ = "Jon Nordby"
__email__ = "jonord@nmbu.no"

import numpy as np
import scipy.misc

def threshold(image, th=None):
    """Returns a binarised version of given image, thresholded at given value.

    Binarises the image using a global threshold `th`. Uses Otsu's method
    to find optimal thrshold value if the threshold variable is None. The
    returned image will be in the form of an 8-bit unsigned integer array
    with 255 as white and 0 as black.

    Parameters:
    -----------
    image : np.ndarray
        Image to binarise. If this image is a colour image then the last
        dimension will be the colour value (as RGB values).
    th : numeric
        Threshold value. Uses Otsu's method if this variable is None.

    Returns:
    --------
    binarised : np.ndarray(dtype=np.uint8)
        Image where all pixel values are either 0 or 255.
    """
    # Setup
    shape = np.shape(image)
    binarised = np.zeros([shape[0], shape[1]], dtype=np.uint8)

    if len(shape) == 3:
        # FIXME: use a better conversion of color image to luminance
        image = image.mean(axis=2)
    elif len(shape) > 3:
        raise ValueError('Must be at 2D image')

    if th is None:
        th = find_threshold_otsu(image)

    # Apply thresholding
    for (x, y), value in np.ndenumerate(image):
        binarised[x][y] = 255 if value > th else 0

    return binarised


def histogram(image):
    """Returns the image histogram with 256 bins.
    """
    # Setup
    shape = np.shape(image)

    if len(shape) != 2:
        raise ValueError('Must be a 2D image')

    # Start to make the histogram
    ## WRITE YOUR CODE HERE

    histogram, _ = np.histogram(image, bins=256)

    return histogram


def find_threshold_otsu(image):
    """Finds the optimal thresholdvalue of given image using Otsu's method.
    """
    hist = histogram(image)
    th = 0

    print(hist)

    ## WRITE YOUR CODE HERE

    return th



    
