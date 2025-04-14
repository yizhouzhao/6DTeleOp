#include <iostream>
#include <filesystem>
#include <Imath/ImathVec.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "aruco.h"

namespace fs = std::filesystem;

int main() {
    std::cout << "Hello from 6DTeleop!" << std::endl;
    Imath::V3f a (1.0f, 2.0f, 3.0f);
    std::cout << "Imath vector: " << a << std::endl;

    // Print the current working directory
    fs::path executablePath = fs::current_path();
    std::cout << "Current working directory: " << executablePath << std::endl;

    // // ArUco marker generation
    // cv::Mat markerImage = genereteMaker(23);
    // cv::imshow("Marker 23", markerImage);
    // cv::waitKey(0);

    // // ArUco marker generation
    // cv::Mat markerImage2 = genereteMaker(14);
    // cv::imshow("Marker 14", markerImage2);
    // cv::waitKey(0);

    // Navigate up one level to the project root (from the build directory)
    fs::path rootPath = executablePath.parent_path();
    fs::path imagePath = rootPath / "example" / "singlemarkersoriginal.jpg";

    cv::Mat inputImage = cv::imread(imagePath.string(), cv::IMREAD_COLOR);
    
    std::vector<int> markerIds;
    std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
    cv::aruco::DetectorParameters detectorParams = cv::aruco::DetectorParameters();
    cv::aruco::Dictionary dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    cv::aruco::ArucoDetector detector(dictionary, detectorParams);
    detector.detectMarkers(inputImage, markerCorners, markerIds, rejectedCandidates);

    //print detected markers
    std::cout << "Detected markers: " << std::endl;
    for (size_t i = 0; i < markerIds.size(); ++i) {
        std::cout << "Marker ID: " << markerIds[i] << std::endl;
        std::cout << "Corners: ";
        for (const auto& corner : markerCorners[i]) {
            std::cout << "(" << corner.x << ", " << corner.y << ") ";
        }
        std::cout << std::endl;
    }
    
    cv::Mat outputImage = inputImage.clone();
    cv::aruco::drawDetectedMarkers(outputImage, markerCorners, markerIds);
    cv::imshow("Detected Markers", outputImage);
    cv::waitKey(0);

    cv::Mat camMatrix = cv::Mat::eye(3, 3, CV_64F);
    cv::Mat distCoeffs = cv::Mat::zeros(5, 1, CV_64F);
    // set coordinate system
    cv::Mat objPoints(4, 1, CV_32FC3);
    float markerLength = 0.1f; // 10 cm
    objPoints.ptr<cv::Vec3f>(0)[0] = cv::Vec3f(-markerLength/2.f, markerLength/2.f, 0);
    objPoints.ptr<cv::Vec3f>(0)[1] = cv::Vec3f(markerLength/2.f, markerLength/2.f, 0);
    objPoints.ptr<cv::Vec3f>(0)[2] = cv::Vec3f(markerLength/2.f, -markerLength/2.f, 0);
    objPoints.ptr<cv::Vec3f>(0)[3] = cv::Vec3f(-markerLength/2.f, -markerLength/2.f, 0);

    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f> > corners, rejected;

    // detect markers and estimate pose
    detector.detectMarkers(inputImage, corners, ids, rejected);
    size_t nMarkers = corners.size();
    std::vector<cv::Vec3d> rvecs(nMarkers), tvecs(nMarkers);

    if (nMarkers == 0) {
        std::cout << "No markers detected." << std::endl;
        cv::imshow("No Markers", inputImage);
        cv::waitKey(0);
        return 0;
    }

    // Calculate pose for each marker
    for (size_t i = 0; i < nMarkers; i++) {
        solvePnP(objPoints, corners.at(i), camMatrix, distCoeffs, rvecs.at(i), tvecs.at(i));
    }

    return 0;

    // draw results
    cv::Mat imageCopy = inputImage.clone();
    if(!ids.empty()) {
        std::cout << "Detected markers: " << ids.size() << std::endl;

        cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);

        for(unsigned int i = 0; i < ids.size(); i++)
            cv::drawFrameAxes(imageCopy, camMatrix, distCoeffs, rvecs[i], tvecs[i], 1, 2);
    }
    cv::imshow("Pose Estimation", imageCopy);
    cv::waitKey(0);
 

 

    return 0;

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
