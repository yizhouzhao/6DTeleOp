#include <iostream>
#include <Imath/ImathVec.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "aruco.h"

int main() {
    std::cout << "Hello from 6DTeleop!" << std::endl;
    Imath::V3f a (1.0f, 2.0f, 3.0f);
    std::cout << "Imath vector: " << a << std::endl;

    std::cout << "\n=== Testing OpenCV functionality ===\n";
    
    // Print OpenCV version
    std::cout << "OpenCV version: " << CV_VERSION << std::endl;
    
    // Create a simple image
    cv::Mat image(500, 500, CV_8UC3, cv::Scalar(50, 50, 50));
    
    // Draw a circle and a rectangle
    cv::circle(image, cv::Point(250, 250), 100, cv::Scalar(0, 0, 255), 3);
    cv::rectangle(image, cv::Point(150, 150), cv::Point(350, 350), cv::Scalar(0, 255, 0), 2);
    
    // Add text
    cv::putText(image, "OpenCV Test", cv::Point(150, 100), 
                cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
    
    // Create a window and display the image
    std::string windowName = "OpenCV Test Window";
    cv::namedWindow(windowName);
    cv::imshow(windowName, image);
    
    // Create a test image with gradient
    cv::Mat gradientImage = createGradient(500, 500);
    
    // Apply Gaussian blur
    cv::Mat blurredImage;
    cv::GaussianBlur(gradientImage, blurredImage, cv::Size(15, 15), 0);
    
    // Display the gradient and blurred images
    cv::namedWindow("Gradient");
    cv::imshow("Gradient", gradientImage);
    
    cv::namedWindow("Blurred");
    cv::imshow("Blurred", blurredImage);
    
    // Try to load an image if available (not required for test)
    cv::Mat loadedImage = cv::imread("test.jpg", cv::IMREAD_COLOR);
    if (!loadedImage.empty()) {
        cv::namedWindow("Loaded Image");
        cv::imshow("Loaded Image", loadedImage);
        
        // Convert to grayscale
        cv::Mat grayImage;
        cv::cvtColor(loadedImage, grayImage, cv::COLOR_BGR2GRAY);
        
        // Apply Canny edge detection
        cv::Mat edges;
        cv::Canny(grayImage, edges, 100, 200);
        
        cv::namedWindow("Edges");
        cv::imshow("Edges", edges);
    } else {
        std::cout << "No test.jpg found - skipping image load test" << std::endl;
    }
    
    // Wait for a key press
    std::cout << "Press any key to exit..." << std::endl;
    cv::waitKey(0);
    
    // Destroy all windows
    cv::destroyAllWindows();


    return 0;
}
