# -*- coding: utf-8 -*-

"""
Blob-detection coursework as part of INF250 at NMBU (Autumn 2017).

Based on skeleton code by Yngve Mardal Moe
"""

__author__ = "Jon Nordby"
__email__ = "jononor@gmail.com"

import numpy as np
from threshold import threshold, histogram
from bd_backend import region_labeling, _remove_and_relabel_blobs

def centre_of_mass(image, black_blob=False):
    """Computes the centre of mass of the image.

    The 'mass', M, of an (n x m) image is given by the formula
    .. math::
        M = \sum_{i=1}^n \sum_{j=1}^m p[i, j],
    where p[i, j] is the colour value in pixel [i, j].

    The centre of mass of an (n x m) image is computed by the formula
    .. math::
        CoM_y = \sum_{i=1}^n \sum_{j=1}^m i*p[i, j]/M,
        CoM_x = \sum_{i=1}^n \sum_{j=1}^m j*p[i, j]/M,
    where CoM_y is the vertical centre of mass and CoM_x is the horisontal
    centre of mass.

    Parameters:
    -----------
    image : numpy.ndarray
        A two dimensional numpy array containing a grayscale or thresholded image.
    black_blobs : bool
        Wether the blobs are black or not.

    Returns:
    --------
    centre : np.ndarray
        A numpy array of length two, where the first value is the centre of mass
        in the vertical direction and the second value is the centre of mass in
        the horisontal direction.
    """
    image = image.copy()
    shape = image.shape
    if black_blob:
        image = 255-image
    centre = np.array([0, 0]).astype(float)

    #------------------------------START YOUR CODE-----------------------------#
    s = np.sum(image)
    indices = np.mgrid[0:image.shape[0],0:image.shape[1]]
    ys = np.sum(indices[0]*image)
    xs = np.sum(indices[1]*image)

    # Equivalent, but slower
    #xs = 0.0
    #ys = 0.0
    #s = 0.0    
    #for y in range(shape[0]):
    #    for x in range(shape[1]):
    #         p = image[y, x]
    #         xs += x*p
    #         ys += y*p
    #         s += p

    centre = np.array([ ys/s, xs/s ])
    #-------------------------------END YOUR CODE------------------------------#
    return centre.astype(int)


def select_one_blob(labeled, colour):
    """Takes an image and sets all colours but `colour` to zero.

    Arguments:
    ----------
    labeled : numpy.ndarray
        A region labeled image, each blob has its own colour.
    colour : numeric
        All pixels but those with this colour is set to zero.

    Returns:
    --------
    one_blob : numpy.ndarray
        Image of same size as original, with
            one_blob[i, j] = 0, if labeled[i, j] != colour
            one_blob[i, j] = labeled[i, j] if labeled[i, j] = colour
    """
    one_blob = labeled.copy()

    #------------------------------START YOUR CODE-----------------------------#
    one_blob[labeled != colour] = 0
    # Equivalent, but slower    
    #shape = one_blob.shape
    #for y in range(shape[0]):
    #    for x in range(shape[1]):
    #         p = one_blob[y, x]
    #         if p != colour:
    #            one_blob[y, x] = 0
    #-------------------------------END YOUR CODE------------------------------#

    return one_blob


def blob_detection(image, th=None, black_blobs=True, min_area=None,
                   max_area=None):
    """Detect all the blobs in the image that is within the given size range.

    This function uses region labeling to find blobs, it then filteres out
    the blobs that are not according to specifications before returning a
    list of blobs. Each value of this list is a dictionary with the follwing
    key and value pairs:
      - 'pos': The position of one of blob's centre.
      - 'area': The area of the blob.

    Parameters:
    -----------
    image : np.ndarray
        Image to detect blobs in. If this image is a colour image then
        the last dimension will be the colour value (as RGB values).
    th : numeric
        Threshold value  for binarisation step. Uses Otsu's method if
        this variable is None.
    black_blobs : Bool
        Whether the blobs are black or white image after binarisation

    Returns:
    --------
    blobs : list
        List with a dictionary for each blob in the image
    labeled : np.ndarray(int)
        The labeled image.
    """
    # Setup
    shape = np.shape(image)
    labeled = region_labeling(image, th=th,  black_blobs=black_blobs)
    no_blobs = labeled.max()

    min_area = -np.float('inf') if min_area is None else min_area
    max_area = np.float('inf') if max_area is None else max_area


    # Find areas:
    areas = histogram(labeled)[1:]
    areas = np.trim_zeros(areas, 'b') # Remove trailing zeros
    #-----WRITE A SHORT DESRIPTION OF WHY THIS GIVES THE AREA OF EACH BLOB-----#
    # Each blob has its pixel values set to
    # The histogram counts how many times each value appears,
    # effectively counting how many pixels the blob consists of,
    # that is: the area of the blob
    #------------------------------END DESCRIPTION-----------------------------#

    # Filter blobs:
    # Array with the blob-labels to consider
    # The i-th value in the `wanted_blobs list should be True if the
    # corresponding blob has an area within the range we consider.    
    #------------------------------START YOUR CODE-----------------------------#
    wanted_blobs = [ max_area > a > min_area for a in areas ]
    #-------------------------------END YOUR CODE------------------------------#

    # Remove unwanted blobs and recompute areas
    labeled = _remove_and_relabel_blobs(labeled, wanted_blobs)
    areas = histogram(labeled)[1:]
    areas = np.trim_zeros(areas, 'b') # Remove trailing zeros

    no_blobs = labeled.max()
    blobs = [{
        'pos' : np.array([None, None]),
        'area' : None,
    } for _ in range(no_blobs)]
    #-----------------------------YOUR CODE HERE-------------------------------#
    for blob in range(no_blobs): 
        blobs[blob]['area'] = areas[blob]
        color = blob + 1 # Blob labels start at 1
        isolated = select_one_blob(labeled, color) 
        blobs[blob]['pos'] = centre_of_mass(isolated)
    #-----------------------------END YOUR CODE--------------------------------#

    return blobs, labeled


if __name__ == '__main__':
    import matplotlib.pyplot as plt
    import skimage.io as io

    image = io.imread('bie_threshold.jpg').mean(axis=2)

    # Detect blobs
    blobs, labeled = blob_detection(image, min_area=370)
    blob_coords = np.array([[blob['pos'][1], blob['pos'][0]] for blob in blobs])

    # Create figure and axes
    fig = plt.figure()
    sub1 = fig.add_subplot(121)
    sub2 = fig.add_subplot(122)

    # Display images
    sub1.imshow(image, cmap='gray')
    sub1.scatter(blob_coords[:, 0], blob_coords[:, 1])
    sub2.imshow(labeled)

    # Set title and axes
    sub1.set_title('Original image')
    sub2.set_title('Region labeled image')
    sub1.set_xticks([])
    sub1.set_yticks([])
    sub2.set_xticks([])
    sub2.set_yticks([])

    # Format print with blob information
    print('|{:<10}|{:<10}|{:<10}|{:<10}|'.format('Blob no:', 'x pos:', 'y pos:', 'Area:'))
    for i, blob in enumerate(blobs):
        print('|{:<10}|{:<10}|{:<10}|{:<10}|'.format(i, blob['pos'][1],
                                                     blob['pos'][0], blob['area']))

    plt.show()
