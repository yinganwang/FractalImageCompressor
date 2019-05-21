//  Copyright 2019 Yingan Wang
//
//  Preprocess.hpp
//  image-compressor
//
//  Created by Yingan on 4/26/19.
//


#pragma once

#include <stdio.h>
#include <vector>
#include "ofxCv.h"
#include "ofxOpenCv.h"


using cv::Mat;

// This functio extracts the BGR channels from a colored image and return a vector of matrices, which will each be treated as grayscale channel in furthur manipulations.
std::vector<Mat> extract_BGR(Mat output_image);
