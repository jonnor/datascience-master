
## what is histogram binning

how many groups of values there is in the histogram

## what is cumulative histogram



## histogram equalization

    f_eq(v) = floor(H(v)*(L-1)/(MN))

    H: is cumulative distribution of image
    L: number of intensity levels
    M,N: number of pixels in image; width,height


## name a few point operations
brightness
contrast
binary threshold
Quantization
gamma correction
color space conversion

## difference between filter and point-operation

A point operation computes each output pixel from the corresponding input pixel.
O(u,v) = pointop(I(u,v))

A filter computes each output pixel from a set of pixels.
Typically a region surrounding the pixel location, for instance all the 8 neighbours and the pixel (a 3x3 matrix) 

O(u,v) = filter(I, u, v)


## What is the principle of an gradient based edge operator ? 
Detect edges by applying a filter that computes the difference, in the direction we want to detect edges
Horizontal,vertical(diagonal)
Prewitt. Vertical:
-1-1-1
000
111

Sobel



## What is a Laplace operator ? 
An edge detecting filter by detecting where the second derivative crosses 0
Combined vertial and horizontal filters. A common approximation is

[1 -2 1] * [1; -2; -1] =
0  1  0
1 -4  0
0  1  0

This filter is very sensitive to noise. For this reason smoothening must typically be performed beforehand.
This is most efficiently done by convolving a Gaussian filter kernel with the Laplace, and then use the combined filter on images.
This is called a Laplacian of Gaussian (LoG).

## What is the principle of an unsharpen mask ? 

Compute a mask for sharpening by removing from input image I a blurred version of I
Effectively this is a high-pass filter which emphasises edges.

    unsharpenMask(I, radius, amount)
        mask = I - blur(I, radius)
        O = I + amount*mask
        return O

Typically the blur used is a Gaussian blur

## Skeletonize in morphology

TODO:

## Flood fill

TODO

## Watershed

Way of performing image segmentation.
Basic version of algorithm works by 'flooding' from some starting points until

Performs best when markers are provided

[P algorithm, a dramatic enhancement of the waterfall transformation](http://cmm.ensmp.fr/%7Ebeucher/publi/P-Algorithm_SB_BM.pdf)

## Object shape features
Area
Perimeter
Center-of-gravity
Circularity
Roundness


## Name 2 texture feature algorithms

Histogram statistics. Variance,skewness,kurtosis. First-order.
Used as inputs to multivariate model
GLCM, Gray-Level Co-occurance Matrix. Second-order (compares pixel relationships)

Gabor filters?

## Limitation of first order
Only operates on individual pixels, not the relationship of pixels to other pixels.
Misses spatial structures/patterns.
Exaggerates edges of objects

Workaround: Calculate statistics at different resolutions

## Hyperspectral images
Many bands of information. One image per wavelength, down to 10nm between.
Ex: 200 bands. Often also outside visible spectrum, ie: NIR + UV spectrum
Information in different bands often overlapping/correlated.
Multivariate methods important to reduce dimensions and extract relevant info

## Supervised algorithms on hyperspectral iamges

* Discriminant Analysis
* Gaussian Maximum Likelihood Classifier (GMLC) 
* Spectral Angle Mapper (SAM) 

## Explain how supervised classification can be used to select regions of different materials in a  hyperspectral image 
User marks 1 or more region of pixels as correspond to a class.
Does this for 1 or more classes.

User indicates how many classes to classify into.
User indicates how similar pixels must be to be considered the same.


## What are two ways of storing RGB images
Component packed: 3 matrices/vectors, one per channel, R,G,B. Each pixel an intensity number (float/integer)
Pixel packed: 1 matrix, each pixel a tuple of 3 numbers, for R,G,B. Different orderings possible


## Explain what is meant by unfolding a spectral image
Unfolding the hypercube.
Means going from a 3-d cube of width,height pixels and depth Y bands(wavelength),
to a 2-d matrix where each row is all the band data for one X,Y coordinate.


## k-means clustering on hyperspectral image
Each pixel sample is a N bands vector.
The distances of each of these pixel samples must be compared with the cluster centers.

Might want to reduce dimensionality first, for instance by performing PCA.

## How do you select number of components for a PCA  analysis ? 
High enough to account for substantial amount of variance in input, but as small as possible

## NDVI and what is it used for
Normalized difference vegetation index
NDVI = (red-nir) / (nir+red)

## how might you find vegetation in a hyperspectral image
1. Compute NDVI, observe manually a location of vegetation, threshold based on its value
2. Compute PCA on image with lots of vegetation variation. Check how axes corresponds with vegetation variation
3. Cluster pixels using k-means
4. Use supervised classification on hyperspectral data.
Indicate areas with vegetation, and one without.

