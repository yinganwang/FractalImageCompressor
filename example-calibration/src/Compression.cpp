//  Copyright 2019 Yingan Wang
//
//  Compression.cpp
//  image-compressor
//
//  Created by Yingan on 4/25/19.
//

#include "Compression.hpp"

vector<block> generate_transformed_blocks(Mat output_image, int domain_size,
                                          int range_size, int step) {
    cout << "generate_transformed_blocks called" << endl;
    // The value of the factor is the ratio of the domain square versus the range square
    int factor = domain_size / range_size;
    int transformed_row = (output_image.rows - domain_size) / step;
    int transformed_col = (output_image.cols - domain_size) / step;
    
    vector<bool> direction_vector = {true, false};
    vector<int> angle_vector = {0, 90, 180, 270};
    
    // A vector of blocks with all the possible combinations of direction and angle
    vector<block> transformed_blocks;
    block current_block;
    for (int i = 0; i < transformed_row; i++) {
        for (int j = 0; j < transformed_col; j++) {
            // Extract domain matrix
            Mat reduced_image(output_image, cv::Rect(i * step, j * step,
                                                     domain_size, domain_size));
            // Construct domain block by reducing reduced matrix
            Mat domain_block = reduce_image(reduced_image, factor);
            // Construct all possible combinations and extract information to the blocks
            for (bool dirc : direction_vector) {
                for (int angle : angle_vector) {
                    current_block.flipped = dirc;
                    current_block.angle = angle;
                    current_block.row_t = i;
                    current_block.col_t = j;
                    current_block.matrix = domain_block;
                    transformed_blocks.push_back(current_block);
                }
            }
        }
    }
    return transformed_blocks;
}

vector<vector<pixel> > compress_image(Mat output_image, int domain_size,
                                      int range_size, int step) {
    cout << "compress called" << endl;
    int transformed_row = output_image.rows / range_size;
    int transformed_col = output_image.cols / range_size;
    double contrast;
    double brightness;
    double min_square = INFINITY;
    double mat_square;
    
    // Initialize the 2D array of pixels vector with defined size
    vector<vector<pixel> > transformation_pixels(transformed_row);
    for (int i = 0; i < transformed_row; i++) {
        transformation_pixels[i] = vector<pixel>(transformed_col);
    }
    
    vector<block> transformation_blocks
                    = generate_transformed_blocks(output_image, domain_size,
                                                  range_size, step);
    
    Mat squared_matrix;
    
    for (int i = 0; i < transformed_row; i++) {
        for (int j = 0; j < transformed_col; j++) {
            // Extract range matrix
            Mat range_image(output_image, cv::Rect(i * range_size, j * range_size,
                                                   range_size, range_size));
            
            // Loop through the vector of all the generated blocks and get the best
            // optimized block for each range square
            for (block b : transformation_blocks) {
                // Find the optimized contrast and brightness with
                // the find_contrast_brightness function
//                contrast = find_contrast_brightness(b.matrix, range_image).at<double>(1, 0);
//                brightness = find_contrast_brightness(b.matrix, range_image).at<double>(0, 0);
                contrast = 1.0;
                brightness = 0.0;
                // Modify the matrix in the block with the best contrast and brightness
                b.matrix = contrast * b.matrix + brightness;
                
                // Find the deviation between a region in the real image and the modified block
                Mat diff = range_image - b.matrix;
                diff = diff.mul(diff);
                squared_matrix = diff.clone();
                cv::Scalar s = sum(squared_matrix);
                
                // Save the matrix with the least deviation and call it the best
                // optimization of the range square
                if (s[0] < min_square) {
                    min_square = s[0];
                    pixel p;
                    p.row_p = b.row_t;
                    p.col_p = b.col_t;
                    p.angle = b.angle;
                    p.flipped = b.flipped;
                    p.brightness = brightness;
                    p.contrast = contrast;
                    transformation_pixels[i][j] = p;
                }
            }
        }
    }
    return transformation_pixels;
}

Mat find_contrast_brightness(Mat domain_image, Mat range_image) {
    // Construct a liner regression equation of y = ai + b, where a = contrast,
    // b = brightness, and i = image matrix, by constructing least square solution
    // Ax = b, where A = merged_image, b = reshaped_range_image,
    // and solve for x = [brightness, contrast].
    // [ 1      x1 ] [  brightness  ]     [ y1 ]
    // [ 1      x2 ] [              ]     [ y2 ]
    // [ .      .  ] [              ]  =  [ .  ]
    // [ .      .  ] [              ]     [ .  ]
    // [ .      .  ] [              ]     [ .  ]
    // [ 1      xn ] [  contrast    ]     [ yn ]
    Mat pixel_weighed = Mat::ones(domain_image.total(), 1, domain_image.type());
    Mat reshaped_domain_image = domain_image.reshape(0, domain_image.total());

    uchar GRAY_color; // pixel color value for grayscale image
    // Copy the data because reshape is a O(1) operation that doesn't copy the data
    for (int i = 0; i < domain_image.rows; i++) {
        for (int j = 0; j < domain_image.cols; j++) {
            GRAY_color = domain_image.at<int>(i, j);
            reshaped_domain_image.at<int>(i * j + i, 0) = GRAY_color;
        }
    }

    // Merge the two image with axis = 1 (horizontally), and merged_image is the matrix of X
    Mat merged_image;
    cv::hconcat(pixel_weighed, reshaped_domain_image, merged_image);

    Mat reshaped_range_image = Mat::zeros(range_image.total(), 1, CV_64F);
    for (int i = 0; i < range_image.rows; i++) {
        for (int j = 0; j < range_image.cols; j++) {
            GRAY_color = range_image.at<int>(i, j);
            reshaped_range_image.at<int>(i * j + i, 0) = GRAY_color;
        }
    }

    // Get the least square matrix if is able to generate least square solution,
    // else return default contrast = 1.0, and brightness = 0.0
    Mat least_square_image = Mat::zeros(2, 1, CV_64F);
    assert(least_square_image.type() == reshaped_range_image.type());
    assert(reshaped_range_image.type() == CV_64F);
    bool least_squared = solve(merged_image, reshaped_range_image,
                               least_square_image, CV_64F);
    if (!least_squared) {
        double default_contrast_brightness[2][1] = {{1.0}, {0.0}};
        least_square_image = Mat(2, 1 , CV_64F, default_contrast_brightness).inv();
        assert(least_square_image.rows == 2 && least_square_image.cols == 1);
    }
    return least_square_image;
}

vector<vector<vector<pixel>>> compress_image_BGR(Mat output_image, int domain_size,
                                                 int range_size, int step) {
    vector<Mat> extracted_matrix = extract_BGR(output_image);
    return {compress_image(extracted_matrix[0], domain_size, range_size, step),
        compress_image(extracted_matrix[1], domain_size, range_size, step),
        compress_image(extracted_matrix[2], domain_size, range_size, step)};
}

vector<Mat> decompress(vector<vector<pixel>> transformations, int domain_size,
                       int range_size, int step, int nb_iter) {
    cout << "decompress called" << endl;
    int factor = domain_size / range_size;
    int height = transformations.size() * range_size;
    int width = transformations[0].size() * range_size;
    int min = 0;
    int max = 256;
    
    Mat iter_matrix = Mat::zeros(height, width, CV_8UC1);
    // assert that the algorithm is only dealing with one channel everytime
    assert(iter_matrix.channels() == 1);
    // Generate random value of grayness in each pixel for the
    // first compressed image (when iteration = 0)
    for (int i = 0; i < iter_matrix.rows; i++) {
        for (int j = 0; j < iter_matrix.cols; j++) {
            iter_matrix.at<uchar>(i, j) = rand() % 255;
        }
    }
    
    // A vector of all the output compressed images,
    // the size of the vector = the number of iterations + 1
    // because we take in consideration of the random image generated when iteration = 0
    vector<Mat> iter_vec;
    iter_vec.push_back(iter_matrix);
    
    // Current image is generated by applying information stored in all the
    // cur_pixel to the last output image in the iter_vec
    Mat cur_image = Mat::zeros(height, width, CV_8UC1);
    pixel cur_pixel;

    for (int iter = 0; iter < nb_iter; iter++) {
        for (int i = 0; i < transformations.size(); i++) {
            for (int j = 0; j < transformations[0].size(); j++) {
                cur_pixel = transformations[i][j];
                int row = cur_pixel.row_p;
                int col = cur_pixel.col_p;
                Mat reduced_image(iter_vec[iter_vec.size() - 1],
                                  cv::Rect(row * step, col * step, domain_size, domain_size));
                Mat domain_image(reduce_image(reduced_image, factor));
                Mat range_image(apply_transformation(domain_image,
                                                     cur_pixel.flipped,
                                                     cur_pixel.angle,
                                                     cur_pixel.contrast,
                                                     cur_pixel.brightness));
                
                // Update current image with information in the best optimized pixel
                for (int cur_i = 0; cur_i < range_size; cur_i++) {
                    for (int cur_j = 0; cur_j < range_size; cur_j++) {
                        cur_image.at<uchar>(i * range_size + cur_i,
                                            j * range_size + cur_j)
                        = range_image.at<uchar>(cur_i, cur_j);
                    }
                }
            }
        }
        iter_vec.push_back(cur_image);
        // Clear the current image to get ready for the next increment
        cur_image = Mat::zeros(height, width, CV_8UC1);
    }
    return iter_vec;
}
