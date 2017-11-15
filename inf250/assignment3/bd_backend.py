# -*- coding: utf-8 -*-

"""
Backend for the blob detection coursework for INF250 at NMBU.
"""

__author__ = "Yngve Mardal Moe"
__email__ = "yngve.m.moe@gmail.com"

import numpy as np
from threshold import threshold, histogram
import sys


def _remove_and_relabel_blobs(labeled, wanted_blobs):
    """This function removes unwanted blobs.
    """
    labeled = labeled.copy()
    wanted_blobs = np.array(wanted_blobs)
    no_blobs = len(wanted_blobs)
    unwanted_blobs = np.arange(1, no_blobs+1)[np.logical_not(wanted_blobs)]
    wanted_blobs = np.arange(1, no_blobs+1)[wanted_blobs]

    for unwanted_blob in unwanted_blobs:
        labeled[labeled == unwanted_blob] = 0

    for new_label, wanted_blob in enumerate(wanted_blobs):
        new_label += 1
        labeled[labeled == wanted_blob] = -new_label

    return -labeled


def region_labeling(image, th=None, black_blobs=True,  set_recursion_limit=True,
                         recursion_limit=10000):
    """Uses flood fill labeling to detect and label blobs in an image.

    The flood-fill algorithm is one of the simplest blob-detection
    algorithms that exists. As part of this algorithm, the image needs
    to be binarised. This is done using global thresholding at given threshold
    value, or, if no threshold value is given, Otsu's method is used to find
    the optimal value. the output of this algorithm is a new image, of same
    size as the input image, however it is thresholded and each blob
    has its own gray-value. The BLOBs are assumed to be black on white
    background after binarisation, if this is not the case set `black_blobs`
    to False.


    Parameters:
    -----------
    image : np.ndarray
        Image to detect blobs in. If this image is a colour image then
        the last dimension will be the colour value (as RGB values).
    th : numeric
        Threshold value  for binarisation step. Uses Otsu's method if
        this variable is None.
    black_blobs : Bool
        Whether the blobs should be black or white
    set_recursion_limit : Bool
        Whether or not the system recursion limit should be updated (reset after function)
    recursion_limit : int
        Recursion limit to use for this function.

    Returns:
    --------
    labeled : np.ndarray(np.uint)
        Image where the background is completely black and the blobs each have
        their own grayscale value (starting at 1 and increasing linearly)
    """

    # Setup
    shape = np.shape(image)
    old_recursion_limit = sys.getrecursionlimit()
    if set_recursion_limit:
        sys.setrecursionlimit(recursion_limit)

    if len(shape) == 3:
        image = image.mean(axis=2)
    elif len(shape) > 3:
        raise ValueError('Must be at 2D image')

    # Threshold image
    labeled = threshold(image, th=th).astype(int)
    labeled = 255-labeled if black_blobs else labeled
    labeled[labeled == 255] = -1

    # Label blobs
    blobs = 0
    for i in range(shape[0]):
        for j in range(shape[1]):
            if labeled[i, j] == -1:
                blobs += 1
                flood_fill(labeled, y=i, x=j, colour=blobs)

    # Cleanup
    sys.setrecursionlimit(old_recursion_limit)

    return labeled


def flood_fill(image, y, x, colour):
    """Performs depth-first-search flood fill on the image at given location.
    """
    curr_colour = image[y, x]
    image[y, x] = colour

    if y > 0:
        if image[y-1, x] == curr_colour:
            flood_fill(image, y=y-1, x=x, colour=colour)
    if x > 0:
        if image[y, x-1] == curr_colour:
            flood_fill(image, y=y, x=x-1, colour=colour)
    if y+1 < image.shape[0]:
        if image[y+1, x] == curr_colour:
            flood_fill(image, y=y+1, x=x, colour=colour)
    if x+1 < image.shape[1]:
        if image[y, x+1] == curr_colour:
            flood_fill(image, y=y, x=x+1, colour=colour)
