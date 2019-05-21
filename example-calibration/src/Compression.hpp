//  Copyright 2019 Yingan Wang
//
//  Compression.hpp
//  image-compressor
//
//  Created by Yingan on 4/25/19.
//


#pragma once

#include <stdio.h>
#include <iostream>
#include <random>
#include <vector>

#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "Preprocess.hpp"
#include "Transformation.hpp"


using cv::Mat;
using std::vector;


// A structure containing all the information of the transformed matrix
// for generating mappings
struct block {
    int row_t; // correspoing row in the domain block
    int col_t; // correspoing col in the domain block
    bool flipped;
    int angle;
    Mat matrix; // the transformed matrix
};

// A structure containing all the information of the best-fitted transformed
// matrix for the compressed images
struct pixel {
    int row_p; // correspoing row in the domain block
    int col_p; // correspoing row in the domain block
    bool flipped;
    int angle;
    double contrast;
    double brightness;
};



/*
 * This function generate a vector of blocks of all the possible
 * transformation mappings, and the blocks contain all the information
 * for each of the transformed matrices.
 */
vector<block> generate_transformed_blocks(Mat output_image, int domain_size,
                                          int range_size, int step);

/*
 * This function return a 2D vector of pixel with the information of the best
 * mapping for the whole image.
 *
 * For each range block, this function tries all the generated domain blocks,
 * calls find_contrast_brightness to optimize the fitted brightness and contrast,
 * applies the brightness and contrast following the formula S = contrast * S + brightness,
 * where S is a matrix, and return the best mapping results from the
 * transformation mapping of all the output_image.
 *
 * This function applies for grayscale images with only one channel.
 * Use compress_image_RGB for colored images.
 */
vector<vector<pixel>> compress_image(Mat output_image, int domain_size,
                                     int range_size, int step);

/*
 * This function calls compress_image 3 times for each of the BGR channels and
 * return a vector of the best mapping for each channels.
 */
vector<vector<vector<pixel>>> compress_image_BGR(Mat output_image,
                                                 int domain_size, int range_size, int step);

/*
 * Return the least square of two processed matrices to find the best optimized
 * contrast and brightness with the least error.
 */
Mat find_contrast_brightness(Mat domain_image, Mat range_image);

/*
 * Decompress the information in the pixel to generate images with domain size,
 * range size, step, and interation that user set before selecting the image.
 *
 * Generate the first image with ramdom pixels of grayscale. Based on the
 * contraction mapping theorem, this function applies the pixel information with
 * iteration that user set to output images. The larger the iteration,
 * the clearer the image. 
 */
vector<Mat> decompress(vector<vector<pixel> > transformations,
                       int domain_size, int range_size, int step, int nb_iter);
