//  Copyright 2019 Yingan Wang
//
//  TransformationTest.cpp
//  image-compressor-final
//
//  Created by vivianfca on 4/24/19.
//


#include "ofApp.h"
#include "../src/Transformation.hpp"
#include "catch.h"


// Transformation Test
TEST_CASE("rotate clockwise 0 degree") {
    ofImage input_ofimage;
    input_ofimage.setUseTexture(false);
    input_ofimage.load("/Users/vivianfca/Desktop/Alma_IMG/UIUCAlma.png");
    Mat input_image = toCv(input_ofimage);
    Mat output_image = rotate_image(input_image, 0);
    
    ofImage test_ofimage;
    test_ofimage.setUseTexture(false);
    test_ofimage.load("/Users/vivianfca/Desktop/Alma_IMG/UIUCAlma.png");
    Mat test_image = toCv(test_ofimage);
    
    Mat converted_gray_output;
    cvtColor(output_image, converted_gray_output, cv::COLOR_RGB2GRAY);
    Mat converted_gray_test;
    cvtColor(test_image, converted_gray_test, cv::COLOR_RGB2GRAY);
    
    cv::Mat diff;
    cv::compare(converted_gray_output, converted_gray_test, diff, cv::CMP_NE);
    int nz = cv::countNonZero(diff);
    REQUIRE(nz == 0);
}

TEST_CASE("rotate clockwise 90 degree") {
    ofImage input_ofimage;
    input_ofimage.setUseTexture(false);
    input_ofimage.load("/Users/vivianfca/Desktop/Alma_IMG/UIUCAlma.png");
    Mat input_image = toCv(input_ofimage);
    Mat output_image = rotate_image(input_image, 90);
    
    ofImage test_ofimage;
    test_ofimage.setUseTexture(false);
    test_ofimage.load("/Users/vivianfca/Desktop/Alma_IMG/UIUCAlma_90.png");
    Mat test_image = toCv(test_ofimage);
    
    Mat converted_gray_output;
    cvtColor(output_image, converted_gray_output, cv::COLOR_RGB2GRAY);
    Mat converted_gray_test;
    cvtColor(test_image, converted_gray_test, cv::COLOR_RGB2GRAY);
    
    cv::Mat diff;
    cv::compare(converted_gray_output, converted_gray_test, diff, cv::CMP_NE);
    int nz = cv::countNonZero(diff);
    REQUIRE(nz == 0);
}

TEST_CASE("rotate clockwise 180 degree") {
    ofImage input_ofimage;
    input_ofimage.setUseTexture(false);
    input_ofimage.load("/Users/vivianfca/Desktop/Alma_IMG/UIUCAlma.png");
    Mat input_image = toCv(input_ofimage);
    Mat output_image = rotate_image(input_image, 180);
    
    ofImage test_ofimage;
    test_ofimage.setUseTexture(false);
    test_ofimage.load("/Users/vivianfca/Desktop/Alma_IMG/UIUCAlma_180.png");
    Mat test_image = toCv(test_ofimage);
    
    Mat converted_gray_output;
    cvtColor(output_image, converted_gray_output, cv::COLOR_RGB2GRAY);
    Mat converted_gray_test;
    cvtColor(test_image, converted_gray_test, cv::COLOR_RGB2GRAY);
    
    cv::Mat diff;
    cv::compare(converted_gray_output, converted_gray_test, diff, cv::CMP_NE);
    int nz = cv::countNonZero(diff);
    REQUIRE(nz == 0);
}


TEST_CASE("rotate clockwise 270 degree") {
    ofImage input_ofimage;
    input_ofimage.setUseTexture(false);
    input_ofimage.load("/Users/vivianfca/Desktop/Alma_IMG/UIUCAlma.png");
    Mat input_image = toCv(input_ofimage);
    Mat output_image = rotate_image(input_image, 270);
    
    ofImage test_ofimage;
    test_ofimage.setUseTexture(false);
    test_ofimage.load("/Users/vivianfca/Desktop/Alma_IMG/UIUCAlma_270.png");
    Mat test_image = toCv(test_ofimage);
    
    Mat converted_gray_output;
    cvtColor(output_image, converted_gray_output, cv::COLOR_RGB2GRAY);
    Mat converted_gray_test;
    cvtColor(test_image, converted_gray_test, cv::COLOR_RGB2GRAY);
    
    cv::Mat diff;
    cv::compare(converted_gray_output, converted_gray_test, diff, cv::CMP_NE);
    int nz = cv::countNonZero(diff);
    REQUIRE(nz == 0);
}

// Flip
TEST_CASE("flip the image, true") {
    ofImage input_ofimage;
    input_ofimage.setUseTexture(false);
    input_ofimage.load("/Users/vivianfca/Desktop/Alma_IMG/UIUCAlma.png");
    Mat input_image = toCv(input_ofimage);
    Mat output_image = flip_image(input_image, true);
    
    ofImage test_ofimage;
    test_ofimage.setUseTexture(false);
    test_ofimage.load("/Users/vivianfca/Desktop/Alma_IMG/UIUCAlma_flip.png");
    Mat test_image = toCv(test_ofimage);
    
    Mat converted_gray_output;
    cvtColor(output_image, converted_gray_output, cv::COLOR_RGB2GRAY);
    Mat converted_gray_test;
    cvtColor(test_image, converted_gray_test, cv::COLOR_RGB2GRAY);
    
    cv::Mat diff;
    cv::compare(converted_gray_output, converted_gray_test, diff, cv::CMP_NE);
    int nz = cv::countNonZero(diff);
    REQUIRE(nz == 0);
}

TEST_CASE("flip the image, false") {
    ofImage input_ofimage;
    input_ofimage.setUseTexture(false);
    input_ofimage.load("/Users/vivianfca/Desktop/Alma_IMG/UIUCAlma.png");
    Mat input_image = toCv(input_ofimage);
    Mat output_image = flip_image(input_image, false);
    
    ofImage test_ofimage;
    test_ofimage.setUseTexture(false);
    test_ofimage.load("/Users/vivianfca/Desktop/Alma_IMG/UIUCAlma.png");
    Mat test_image = toCv(test_ofimage);
    
    Mat converted_gray_output;
    cvtColor(output_image, converted_gray_output, cv::COLOR_RGB2GRAY);
    Mat converted_gray_test;
    cvtColor(test_image, converted_gray_test, cv::COLOR_RGB2GRAY);
    
    cv::Mat diff;
    cv::compare(converted_gray_output, converted_gray_test, diff, cv::CMP_NE);
    int nz = cv::countNonZero(diff);
    REQUIRE(nz == 0);
}
