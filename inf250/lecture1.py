
import numpy
import matplotlib.pyplot as plt

import skimage.io
import skimage.color

def threshold(img, t):
    shape = numpy.shape(img)
    for x in range(shape[0]):
        for y in range(shape[1]):
            v = img[x, y]
            img[x, y] = 255 if v > t else 0

def linear_map(val, alow, ahigh, amin, amax):
    scale = float(amax-amin)/(ahigh-alow)
    return amin + ((val - alow) * scale)

# TODO: autocontrast by ignoring some percentage of lowest/smallest
def autocontrast(img):
    alow = min(img.flatten())
    ahigh = max(img.flatten())

    print('a', alow, ahigh)

    shape = numpy.shape(img)
    for x in range(shape[0]):
        for y in range(shape[1]):
            img[x, y] = linear_map(img[x, y], alow, ahigh, 0, 255)

def histogram(img):
    histogram = numpy.zeros(256)
    shape = numpy.shape(img)
    for x in range(shape[0]):
        for y in range(shape[1]):
            val = int(img[x,y])
            histogram[val] += 1
    return histogram

# TODO: histogram equalization
# TODO: histogram mapping

def main():
    filename = 'lowcontrast.jpg'
    img = skimage.io.imread(filename)
    img = skimage.color.rgb2gray(img)
    img = skimage.img_as_ubyte(img)

    #plt.hist(img.ravel(), 256, [0, 255])
    #threshold(img, 100)

    _, (p1,p2) = plt.subplots(2)
    original = img.copy()
    p1.imshow(original, 'gray')


    # TODO: also plot histograms

    h = histogram(img)
    #plt.plot(h)
    #plt.show()

    autocontrast(img)

    p2.imshow(img, 'gray')
    plt.show()

if __name__ == '__main__':
    main()
    
