#include "aruco.h"

void processImage(cv::Mat& image) {
    // Implementation
    cv::GaussianBlur(image, image, cv::Size(5, 5), 0);
    // More processing...
}

cv::Mat createGradient(int width, int height) {
    cv::Mat gradient(height, width, CV_8UC1);
    for (int i = 0; i < gradient.rows; i++) {
        for (int j = 0; j < gradient.cols; j++) {
            gradient.at<uchar>(i, j) = (i + j) / 2;
        }
    }
    return gradient;
}

cv::Mat genereteMaker(int index = 23) {
    cv::Mat makerImage;
    cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    cv::aruco::generateImageMarker(dictionary, index, 200, makerImage, 1);
    return makerImage;
}