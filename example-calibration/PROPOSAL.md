# Proposal
## Fractal Image Compressor

*Solution generated from http://www.ti.com/lit/an/bpra065/bpra065.pdf*

### Background
Most data contains some amount of redundancy. With a variety of algorithms to remove the repeatitive information, we can achieve mass information storage and fast communication. Inspired by fractal, a concept in Euclidian geometry, researchers have applied the features of fractal to design algorithms that maintain quality pictures while removing redundant data from images.

Become interested in fractal before knowing the application of it in image compression, I aim to design my own fractal algorithm and build an interactive platform with GUI that offers user to compress (and de-compress) high resolution images.

### Main Goal
- Develop a image compressing algorithm using fractal to encode and compress given high resolution(= large memory) images to low resolution(= lower memory) images
- Apply Qt library and ofxGUI to design a GUI for users to input image and output compressed image

### Side Goal (may not be able to implement due to time):
Develop an de-fractal algorithm to decode the compressed image and recover to the high resolution image.

### Proposed Algorithm for Encoding
**Conteractive Transformation**
- A transformation *w* is said to be conteractive if for any two points *P1*, *P2*, the distance *d(w(P1, P2))* < *sd(P1, P2)* for some *s* < 1, where d = distance. This formula says the application of a conteractive map always brings points closer together.

**The Contractive Mapping Fixed Point Theorem**
- If a transformation is contractive then when applied repeatedly strarting with any initial points, we coverage to a unique fixed points.

The previous theorems tells us that transformation *W* will have a unique fixed point in the
space of all images. That is, whatever image (or set) we start with, we can repeatedly
apply *W* to it and we will converge to a fixed image.

Suppose we are given an image *f* that we wish to encode. This means we want to find a
collection of transformations *w1*, *w2*, ...,*wn* and want *f* to be the fixed point of the map *W*. In other words, we want to partition f into pieces to which we apply the transformations *wi*, and get back the original image *f*.

### Proposed Algorithm for Decoding
The reconstruction process of the original image consists on the applications of the
transformations describe in the fractal code book iteratively to some initial image Ω*init*,
until the encoded image is retrieved back.
