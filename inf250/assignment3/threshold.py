# -*- coding: utf-8 -*-

"""
Skeleton for first part of the blob-detection coursework as part of INF250
at NMBU (Autumn 2017).
"""

__author__ = "Yngve Mardal Moe"
__email__ = "yngve.m.moe@gmail.com"

import numpy as np


def threshold(image, th=None):
    """Returns a binarised version of given image, thresholded at given value.

    Binarises the image using a global threshold `th`. Uses Otsu's method
    to find optimal thrshold value if the threshold variable is None. The
    returned image will be in the form of an 8-bit unsigned integer array
    with 255 as white and 0 as black.

    Arguments:
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
    binarised = np.zeros((shape[0], shape[1]), dtype=np.uint8)

    if len(shape) == 3:
        image = image.mean(axis=2)
    elif len(shape) > 3:
        raise ValueError('Must be at 2D image')

    if th is None:
        th = otsu(image)

    #------------------------------START YOUR CODE-----------------------------#
    binarised[image > th] = 255

    # Or, equivalently
    # for i in range(shape[0]):
    #    for j in range(shape[1]):
    #         if image[i, j] > th:
    #             binarised[i, j] = 255
    #-------------------------------END YOUR CODE------------------------------#

    return binarised


def histogram(image):
    """Returns the image histogram with 255 bins.
    """
    # Setup
    shape = np.shape(image)
    histogram = np.zeros(256)

    if len(shape) == 3:
        image = image.mean(axis=2)
    elif len(shape) > 3:
        raise ValueError('Must be at 2D image')

    # Start to make the histogram
    #------------------------------START YOUR CODE-----------------------------#
    #histogram, _ = np.histogram(image, bins=range(256).

    # Or, equivalently
    for pix in image.ravel():
        histogram[int(pix)] += 1
    #-------------------------------END YOUR CODE------------------------------#

    return histogram


def _between_var(histogram, th):
    """Compute the between class variance that's used in Otsu's method.

    Returns the between class variance used for Otsu thresholding at the
    given threshold value. Returns -1 if all pixels are below or above
    the threshold value.

    Arguments:
    ----------
    histogram : np.ndarray
        Image histogram, 1-D array.
    th : numeric
        Threshold value.

    Returns:
    --------
    between_var : float
        The variance between the foreground and background classes.
        If all pixels are in one of the classes, -1 is returned.
    """
    #------------------------------START YOUR CODE-----------------------------#
    no_pixels = histogram.sum()
    no_bg = histogram[:th].sum()
    no_fg = histogram[th:].sum()

    weight_bg = histogram[:th].sum()/no_pixels
    weight_fg = histogram[th:].sum()/no_pixels

    if weight_bg == 0 or weight_fg == 0:
        return -1

    mean_bg = histogram[:th].dot(np.arange(th))/no_bg
    mean_fg = histogram[th:].dot(np.arange(th, 256))/no_fg

    between_var = weight_bg*weight_fg*float(mean_bg - mean_fg)**2
    #-------------------------------END YOUR CODE------------------------------#

    return between_var


def otsu(image):
    """Finds the optimal thresholdvalue of given image using Otsu's method.

    Arguments:
    -----------
    image : numpy.ndarray(dtype=numpy.uint8)
        Image to find optimal threshold value for. Should be 8-bit.

    Returns:
    --------
    otsu : int
        Optimal threshold value.
    """
    hist = histogram(image)
    th = 0

    #------------------------------START YOUR CODE-----------------------------#
    best_var = 0
    for th_val in range(256):
        between_var = _between_var(hist, th_val)
        if between_var > best_var:
            best_var = between_var
            th = th_val

    if th == 0:
        raise Warning('All pixels has the same colour.')
    #-------------------------------END YOUR CODE------------------------------#

    return th


if __name__ == '__main__':
    import skimage.io as io
    import matplotlib.pyplot as plt

    image = io.imread('bie_threshold.jpg').mean(axis=2)

    # Compute histogram and threshold
    hist = histogram(image)
    otsu_val = otsu(image)
    th_image = threshold(image)

    # Create figure and subplots
    fig = plt.figure(figsize=(12, 3))
    subs = [None]*3
    for i in range(3):
        subs[i] = fig.add_subplot(1, 3, i+1)
        subs[i].set_xticks([])
        subs[i].set_yticks([])

    # Display original image
    subs[0].imshow(image, cmap='gray')
    subs[0].set_title('Original image')

    # Display histogram with threshold value
    subs[1].plot(hist)
    min_y, max_y = subs[1].get_ylim()
    subs[1].plot([otsu_val, otsu_val], [min_y, max_y])
    subs[1].set_ylim(min_y, max_y)
    subs[1].set_xlim(0, 255)
    subs[1].set_xticks(list(range(0, 256, 32))+[255])
    subs[1].set_title('Histogram with optimal theshold value')

    # Display thresholded image
    subs[2].imshow(th_image, cmap='gray')
    subs[2].set_title('Thresholded image')

    plt.show()
