#pragma once  // or use include guards

#include <opencv2/opencv.hpp>  // Include OpenCV header

// Function declarations
void processImage(cv::Mat& image);
cv::Mat createGradient(int width, int height);
// Add other function declarations