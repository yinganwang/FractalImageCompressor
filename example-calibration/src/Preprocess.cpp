//  Copyright 2019 Yingan Wang
//
//  Preprocess.cpp
//  image-compressor
//
//  Created by Yingan on 4/26/19.
//

#include "Preprocess.hpp"

std::vector<cv::Mat> extract_BGR(Mat output_image) {
    vector<Mat> bgr;
    split(output_image, bgr);
    vector<Mat> BGR_image_vector;
    BGR_image_vector.push_back(bgr[0]); // blue channel
    BGR_image_vector.push_back(bgr[1]); // green channel
    BGR_image_vector.push_back(bgr[2]); // red channel
    return BGR_image_vector;
}
