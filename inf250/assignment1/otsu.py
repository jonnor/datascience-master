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
import math

def to_grayscale(image):
  shape = np.shape(image)
  if len(shape) == 3:
    # sRGB image, convert to luminance (Y)
    srgb = np.array((0.2126, 0.7152, 0.0722))
    image = (image * srgb).sum(axis=-1)
  elif len(shape) > 3:
    raise ValueError('Must be at 2D image')
  return image

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
    image = image = to_grayscale(image)

    if th is None:
        th = find_threshold(image)

    # Apply thresholding
    binarised = np.where(image > th, 255, 0)

#   Note: above is equivalent to looping over manually, just much faster
#    binarised = np.zeros([shape[0], shape[1]], dtype=np.uint8)
#    for (x, y), value in np.ndenumerate(image):
#      binarised[x][y] = 255 if value > th else 0

    return binarised


def histogram(image):
    """Returns the image histogram with 256 bins.
    """
    # Setup
    shape = np.shape(image)

    if len(shape) != 2:
        raise ValueError('Must be a 2D image')

    histogram, _ = np.histogram(image, bins=256, range=(0, 255))
    
#   Note: above equivalent to looping over manually, just faster
#    histogram = np.zeros([256], dtype=np.uint64)
#    for value in np.nditer(image):
#      v = int(value)
#      histogram[v] += 1

    return histogram


def find_threshold(image):
    """Finds the optimal thresholdvalue of given image using Otsu's method.
    """

    image = to_grayscale(image)

    hist = histogram(image)

    # Find threshold by maximizing between-class variance
    # This gives same result as minimizing within-class variance,
    # but with fewer calculations

    # Precompute cumulative number of histogram entries, and the weighted-sum
    # Allows quick lookup when going through the possible thresholds
    total_pixels = image.size
    cumsum = np.cumsum(hist)
    cumvalues = np.cumsum(np.arange(256) * hist)
    total_values = cumvalues[255]

    # background class (_b) has pixel values {0,t}
    # foreground class (_f) has pixel values {t,255}
    def between_class_variance(t):
      weight_b = cumsum[t]
      weight_f = total_pixels - weight_b 

      if weight_b == 0 or weight_f == 0:
        # no pixel values in class, avoid division-by-zero
        return -math.inf

      s = cumvalues[t]
      mean_b = s / weight_b
      mean_f = (total_values - s) / weight_f

      between = weight_b * weight_f * (mean_b - mean_f)**2
      return between

    # Calculate between-class-variance for possible thresholds
    scores = list(between_class_variance(t) for t in range(256))

    # Chose threshold which maximises between-class-variance
    th = max(range(256), key=lambda t: scores[t])

    return th

def test():
  filepath = 'bie_threshold.jpeg'
  #p = 'a1.jpg'
  img = scipy.misc.imread(filepath)

  th = find_threshold(img)
  expected = 104 # verified visually. Also very close to what OpenCV returns
  assert th == expected, "{} != {}".format(th, expected)

  binary = threshold(img, None)

if __name__ == '__main__':
  test()



