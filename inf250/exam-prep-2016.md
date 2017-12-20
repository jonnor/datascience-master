
## 1.A. Beskriv kort hvordan bilder kan digitaliseres

Digital image is represented as a set of pixels: a 2d matrix with width w and height h.
Each pixel can consist of a greyscale, or a RGB triplet.
It is stored with a certain bitdepth, for instance 8/16/32 bits per channel.
Either integer or floating point number representations can be used.
Each pixel represents a point sample. A CCD/CMOS image sensor is used to capture images,
which converts light into intensity values.

The data is often stored gamma-corrected, which is a simple approximation of the non-linearity
in typical display units, and allows to represent a wider range of colors with a given bitdepth. 

## 1.B Beskriv kort forskjeller og bruksområder på ImageJ plugin og makro
ImageJ plugin is Java code that processes pixels.
It is useful for implementing new methods using low-level code.
A macro is does image processing by applying a sequence of ImageJ operations/plugins.

## 1.C Beskriv kort et 24 bits fullfargebilde og et binært bilde

Binary image has 1 bit per channel: each pixel is either black or white.
A 24bit full-color image has 3 channels with 8 bits per channel: R, G, and B.
Typically stored with gamma-preapplied. A typical colorspace is sRGB with D65 whitepoint.

## 1.D Beskriv kort teknikken for indeksert fargebilde (palett)

Each pixel has an integer value of an enumerated set of colors, stored in a palette.
The palette stores the RGB triplet that defines this color.

## 1.E Forklar kort begrepet DPI (Dots Pr. Inch)

DPI is one way of specifying spatial resolution, how pixels correspond to a physical length,
either when captured or when displayed.
Each pixel represents is 1/DPI inches.

## 1.F Beskriv kort hovedtyper av kompresjon

There are two main classes of compression:
lossless, where the original image can be perfectly reconstructed from the compressed image.
lossy, which cannot perfectly reconstruct the original.
With lossy encoding one can achieve greater compression levels, since there is some data
that can be removed without it being easily perceived.

PNG and JPEG2000 support lossless. JPEG supports lossy.

## 1.G. Beskriv teknikken bak JPEG kompresjon

Convert from RGB to YCrCb / YUV, itensity and two chroma (color) channels.
Allows to store itensity with higher precision than chroma, since eye is more sensitive to intensity changes.
For instance chroma might be sampled at half of  intensity.
The image is split into blocks of 8x8 pixels, and each block is converted to frequency space using Discrete Cosine Transform (DCT).
The high frequency components are removed during quantization, and the data is compressed using Huffman encoding.


## 1.H. Beskriv med en figur teknikken for lineær og ikke-lineær filtrering av bilder

Linear filters are a.
Can be fully described by a matrix H, and applied by convolving the image I with H.
Linear filters are associative,commutative. A 2d filter can be separated into 2 1D filters
Reduces complexity of the convolution from N^2M^2 to N^2M, which is a large saving with large kernels.

Non-linear filters applies an arbitrary function to get I'(u,v) = f(I,u,v)
A simple example is the median filter.

## 1.I. Beskriv teknikken bak Unsharpen Mask

    unsharpenMask(I, radius, amount)
        mask = I - gaussianBlur(I, radius)
        out = I + (mask * amount)
        return out

mask is edge/detail enhancing

## 1.J. Beskriv et glattefilter

There are many different smoothening filters, both linear and non-linear.
The simplest is the uniform/box filter has all entries in H set to 1/(s*s) where s is the size of the filter: 3,5,7...
This makes the output pixel the mean of the surrounding pixels, averaging/smoothening out features.
The edge preservation can be better if using a weighted filter.

Gaussian blur is another smoothening filter.


## 1.K. Hvordan kan kan man ved hjelp av medianfilteret fjerne støy i et bilde?

Median filter is a non-linear filter which computes each output pixel as the median of its neighbouring pixels.
This rejects atypical values without smoothening as much as a box or gaussian filter.
In particular edges are preserved better


## 2. A. Forklar hvordan et 16 bits gråtonebilde kan konverteres til et 8 bits gråtonebilde
og hvilke følger dette får for oppløsning med hensyn til pixeldybde.

Basic approach is to take each pixel intensity and divide by 2**8 (256), either with nearest rounding or truncating  rounding
The precision is now reduced to 8 bits. If storing linear-light, 8bits can typically not represent an adequate dynamic range
In gradients this may cause banding, making visible shapes (that did not exist before) in the regions
Techniques like dithering or error diffusion can reduce these artifacts

## 2.B. Forklar oppbyggingen av histogrammet og det akkumulerte histogrammet til et 8 bits gråtonebilde
(matematisk og med figur)

## 2.C. Tegn opp og forklar karakteristikken til et histogram der vi har
a. Lav kontrast
b. Normal kontrast
c. Høy kontrast

a. low contrast: low and high end of histogram are empty. Dynamic range is squeezed into the middle
b. normal contrast: low,mid,end of histogram all has a good amount of values
c. high contrast: low and high end of histogram contain most of the values. Extreme case practically black and white only

## 2.D. Angi formelen for histogramutjevning og forklar prosessen for histogramutjevning

    heq(v) = round( (cdf(v)-cdf_min)/(M*N)-1 * (L-1) ), where

    cdf(v) is the cumulative histogram of the image
    L is the number of gray levels
    M,N is the number of pixels width,height

* Compute the cumulative histogram of the input
* For each of the graylevels [0:L-1] compute the mapping h
* Go through all the pixels in the image, replace the pixel value with h(pixel)

Histogram equalization is a special case of histogram matching to a uniform distributed histogram.

## 2.E. Forklar hvordan histogrammet av et 8 bits gråtonebilde kan reduseres fra 256 bins til for eksempel et 32 bins histogram.

Divide the 256 histogram values into 32 bins
0->7 bin1, 8->15 bin2 etc
Sum the number of values from the 256 histogram for each bin


## 2.F. Forklar kort prinsippet bak lineær terskling av bilder.
Assuming means binary thresholding.

Convert an grayscale or RGB color image to a 1-bit binary image,
each value above > threshold becomes 1, and each value below becomes 0 

This is often done as an early step in object segmentation

## 2.G. Beskriv kort hvordan vi kan implementere en automatisk algoritme for terskling av bilder
Hva er hensikten med en slik automatisk algoritme?

The purpose is to automatically chose an optimal threshold value, to segment.

One method is Otsus method:

Calculate the histogram of image
For each possible threshold values (0,1,2, -> 256 for 8bit),
calculate the variance of the two classes (below/above threshold) from the histogram values
Chose the threshold which gave the highest between-class variance,
or equivalently, the threshold that gives the lowest variance for each class

When a single thresholding value is chosen, this is a global thresholding operation.
In some cases with uneven lighting this may perform poorly on some areas of the image.
To fix that an adaptive thresholding algorithm must be used

## 3.A. Tegn opp og forklar prinsippet for Pixelnaboskap.
4 neighbourhood: above,below,left,right
8 neightbourhood: also include diagonals upright,upleft,downright,downleft

## 3.B. Beskriv teknikken Erosjon (Erotion)
A structuring element. For instance a 3x3 square filled with 1s.

Output pixel is set to background if *any* of then input refered by the structuring element is background,
otherwise left unchanged.
Stated otherwise: Pixel is kept as foreground if all pixels are foreground

This will have the effect of shrink foreground regions, and holes inside grow

## 3.C. Beskriv teknikken Dilasjon (Dilation)

Output pixel is set to foreground if *any* of the input refered by structuring element is foreground,
otherwise left unchanged.
Stated otherwise: Pixel is kept as background if all pixels are background

Foreground regions grows, and holes inside shrink

## 3.D. Beskriv teknikken Lukking (Closeing)
Dilation followed by Erotion

Removes holes smaller than structuring element (kernel)

## 3.E. Beskriv teknikken Åpning (Opening)
Erotion followed by Dilation

Removes foreground regions smaller than structuring element (kernel)

## 3.F.
Anta at et bilde I består av vertikal og horisontal linje med skjæringspunkt i bildets
midtpunkt. Bakgrunn er 0 og forgrunnen er 255 med en pixelbredde på 1. Du skal foreslå
et strukturerende element samt tilhørende enkelt-operasjon for følgende
a. Fjerne kun den horisontale linjen
b. Fjerne kun den vertikale linjen

Remove forground smaller than kernel using the opening operator (erode then dilate)
a) remove horizontal using a kernel which consists of a horizontal line, for instance 5 pixels wide [[ 1,1,1,1 ]]
b) .. vertical... [[1],[1],[1],[1],[1]]


# 4
I øvinger og prosjekt har du arbeidet med bildestabler. Anta at du har en bildestabel (ImageJ
Stack) av et antall overflatebilder bestående av 2 hovedklasser K1 og K2. Det er laget labler
(etiketter) i bildestabelen over klassen bilder tilhører. To bilder i har ved en feil fått byttet etikett.
Anta at du har til rådighet følgende programvare:
1. ImageJ
2. Plugin for å beregne histogrammer av hvert bilde in stack
3. Unscrambler programvare for Prinsipal Komponent Analyse (PCA) og plotting

# 4.A Beskriv teknikken PCA
Principal Component Analysis is an unsupervised technique for transforming possibly-correlated data into a new set
of orthogonal (not-correlaed) components, which are linear combinations of the original data.

It can reveal underlying structure

We specify a desired number of components.
The number of components are usually chosen such that they explain a certain amount of the variance, for instance 99.99%

# 4.B. Beskriv kort begrepet bildetekstur.

Image texture is .
Textures can be isotropic (stocastic), ansitropic (deterministic) and semi-isotropic
The texture measurements depend a lot on scale, ie an image may have one texture at a small scale, and another at a large scale.

Texture of a region can be quantified using histogram-based methods,
including variance, skewness, kurtosis.
However this fails to describe geometric features inside the region. 

A more comprehensive method is to compute a graylevel co-occurence matrix (GLCM),
which specifies how often pairs of pixels with a specific gray-level occurs with a certain spatial distance.
From this matrix one can compute statistics, like homogenity,dissimilarity,correlation,constrast and energy.

Texture measures are most often used for classification.
One can calculate it for a detected object, or for windowed regions across entire image.
However it can also be used as a basis for segmentation.

[GLCM tutorial, Uni Calgary](https://prism.ucalgary.ca/bitstream/handle/1880/51900/texture%20tutorial%20v%203_0%20170329.pdf)

# 4.C. Utfør en tenkt PCA på bildestack som har som formål å karakterisere de ulike bildene med hensyn på teksturklassene K1 og K2.

N/A

# 4.D. Skisser en visuell metode for om mulig å identifisere de to bildene som har etikett K1 og K2 byttet om.

When plotting the datapoints for K1,K2 they should show up as two (relatively) distinct regions
We can then identify the two mislabeled images as those that are inside a region with the opposite label
