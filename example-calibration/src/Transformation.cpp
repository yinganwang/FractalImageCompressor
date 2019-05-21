//  Copyright 2019 Yingan Wang
//
//  Transformation.cpp
//  image-compressor
//
//  Created by Yingan on 4/23/19.
//

#include "Transformation.hpp"


Mat rotate_image(Mat processed_image, int angle) {
    cout << "rotate_image called" << endl;
    int rotate_flag = 0;
    if (angle % ROUND == RCW_90) {
        rotate_flag = FLIP_AROUND_Y;
        cv::flip(processed_image.t(), processed_image, rotate_flag);
    } else if (angle % ROUND == RCC_90) {
        rotate_flag = FLIP_AROUND_X;
        cv::flip(processed_image.t(), processed_image, rotate_flag);
    } else if (angle % ROUND == RCW_180) {
        rotate_flag = FLIP_AROUND_BOTH;
        cv::flip(processed_image, processed_image, rotate_flag);
    }
    return processed_image;
}

Mat flip_image(Mat processed_image, bool flipped) {
    cout << "flip_image called" << endl;
    if (flipped) {
        cv::flip(processed_image, processed_image, FLIP_AROUND_Y);
    }
    return processed_image;
}

Mat reduce_image(Mat processed_image, int factor) {
    cout << "reduce_image called" << endl;
    // Only take the quotient part of the division
    int row = processed_image.rows / factor;
    int col = processed_image.cols / factor;
    Mat resized_image(row, col, processed_image.type());
    
    // Assign the mean value of the pixels in the sub_image to the current pixel in the resized image
    for (int i = 0; i < row - 1; i++) {
        for (int j = 0; j < col - 1; j++) {
            cv::Range i_range(i, i + 1);
            cv::Range j_range(j, j + 1);
            Mat sub_image(processed_image,
                          cv::Rect(i * factor, j * factor, factor, factor));
            resized_image(i_range, j_range) = mean(sub_image);
        }
    }
    return resized_image;
}

Mat apply_transformation(Mat processed_image, bool flipped, int angle, double contrast, double brightness) {
    cout << "apply_transformation called" << endl;

    Mat flipped_image = flip_image(processed_image, flipped);
    Mat rotated_image = rotate_image(flipped_image, angle);
    return contrast * rotated_image + brightness;
}
