#pragma once  // or use include guards

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/aruco_detector.hpp>

// Function declarations
void processImage(cv::Mat& image);
cv::Mat createGradient(int width, int height);
// Add other function declarations
cv::Mat genereteMaker(int index);