//  Copyright 2019 Yingan Wang
//
//  Transformation.hpp
//  image-compressor
//
//  Created by Yingan on 4/23/19.
//

#pragma once


#include <stdint.h>
#include "Preprocess.hpp"

#define RCW_90 90 // Rotate clockwise 90 degrees
#define RCW_180 180 // Rotate clockwise 180 degrees
#define RCC_90 270 // Rotate counterclockwise 90 degrees
#define ROUND 360 // The degree of a round is 360

using cv::Mat;

/*
 * The flipCode of ofxCv
 */
enum flipCode {
    FLIP_AROUND_X = 0, // Flip around the x-axis
    FLIP_AROUND_Y = 1, // Flip around the y-axis
    FLIP_AROUND_BOTH = -1, // Flip around both axes
};

/*
 * Rotate image through modifying processed_image
 *
 * Angles have to be DIVISIBLE BY 90. If rotate the image with any degree,
 * then the image might be resized to adjust to the screen, and will affect
 * the perciseness of the compression.
 *
 * Because the cv::rotate is no longer able to use, here applies cv::flip and
 * the transpose of processed_image to get rotated images.
 */
Mat rotate_image(Mat processed_image, int angle);

/*
 * Flip image through modifying processed_image
 *
 * If the flage flipped is true, flip the image around the y-axis.
 * Else, make no change to the processed_image.
 */
Mat flip_image(Mat processed_image, bool flipped);
/*
 * Reduce the size of an image by averaging the pixel values of the neighborhoods.
 *
 * The factor is the width and length of the square that the image is divided
 * into for averaging the pixel values.
 */
Mat reduce_image(Mat processed_image, int factor);

/*
 * Apply transformation following the formula
 fl(xDk)=s*rotateθ(flipd(reduce(xDk)))+b,
 * with s = contrast constant, and b = brightness constant.
 *
 * Only call this function when doing affine transformation.
 */
Mat apply_transformation(Mat processed_image, bool flipped, int angle,
                         double contrast, double brightness);
