//  Copyright 2019 Yingan Wang


#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup() {
    gui.setup();
    gui.add(domain_size_slider.setup("domain size", 8, 0, 16));
    gui.add(range_size_slider.setup("range size", 4, 0, 8));
    gui.add(step_slider.setup("step", 8, 8, 8));
    gui.add(iteration_slider.setup("iteration", 8, 0, 12));
    ofSetLogLevel(OF_LOG_VERBOSE);
}

void ofApp::update() {

}

void ofApp::draw() {
    gui.draw();
    ofDrawBitmapString("Press spacebar to open an image that you want to compress", 20, 15);
    loaded_image.draw(0, 50);
    ofDrawBitmapString(compression_notification, 20, 30);
}

void ofApp::keyPressed(int key) {

}

void ofApp::keyReleased(int key) {
    ofFileDialogResult openFileResult;
    
    if (key == ' ') {
        // Open the Open File Dialog
        openFileResult = ofSystemLoadDialog("Select a jpg or png");

        // Check if the user opened a file
        if (openFileResult.bSuccess) {
            ofLogVerbose("User selected a file");
        } else {
            ofLogVerbose("User hit cancel");
        }
        
        // Verify if the file is an image by checking the file extension
        ofFile file (openFileResult.getPath());
        if (file.getExtension() == "jpg" || file.getExtension() == "png"
            || file.getExtension() == "gif") {
            original_file_extension = file.getExtension();
        } else {
            ofLogVerbose("User selected a non-image file");
        }
        
        loaded_image.load(openFileResult.getPath());
        
        // Check if the user is trying to load empty image
        vector<ofImage> image_vec = {loaded_image};
        // User is trying to save without anything to output - bail
        if (image_vec.size() == 0) {
            return;
        }
        
        Mat initial_image = toCv(loaded_image);
        Mat tmp_image(initial_image);
        
        // Convert the image to grayscale if there are more than one channel in the initial image
        if (initial_image.channels() > 1) {
            cv::cvtColor(initial_image, tmp_image, cv::COLOR_BGR2GRAY);
        }
        
        // Operate the compression algorithm with data set by the integer sliders
        vector<vector<pixel>> compressed_image
            = compress_image(tmp_image, domain_size_slider,
                             range_size_slider, step_slider);
        vector<Mat> output_vec = decompress(compressed_image, domain_size_slider,
                                            range_size_slider, step_slider, iteration_slider);
        
        ofImage output_image;
        for (int i = 0; i < output_vec.size(); i++) {
            string file_path = "/Users/vivianfca/Desktop/output" + to_string(i)
            + "." + original_file_extension;
            toOf(output_vec[i], output_image);
            output_image.save(file_path);
            output_image.clear();
        }
        
        // Notify the user after compressing process is done
        compression_notification = "Compression is done!"
            " Please go to your desktop to see all the compressed images";
    }
}

void ofApp::mouseMoved(int x, int y ){

}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::mouseReleased(int x, int y, int button){

}

void ofApp::mouseEntered(int x, int y){

}

void ofApp::mouseExited(int x, int y){

}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
