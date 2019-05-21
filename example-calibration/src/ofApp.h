//  Copyright 2019 Yingan Wang


#pragma once

#include <vector>
#include <string>

#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

#include "Preprocess.hpp"
#include "Transformation.hpp"
#include "Compression.hpp"


using std::string;
using cv::Mat;
using ofxCv::toCv;
using ofxCv::toOf;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        ofxPanel gui;
        ofxIntSlider iteration_slider; // set how many times of compression the user wants
        ofxIntSlider domain_size_slider; // set the width of domain square in the mapping
        ofxIntSlider range_size_slider; // set the width of range square in the mapping
        ofxIntSlider step_slider; // set the step to skip when generating transformed blocks
    
    ofImage loaded_image;
    ofImage processed_image;
    string original_file_extension;
    string compression_notification;
};
