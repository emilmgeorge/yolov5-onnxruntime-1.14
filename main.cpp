#include <iostream>
#include <opencv2/opencv.hpp>

#include "utils.h"
#include "detector.h"


int main(int argc, char* argv[])
{
    std::cout << "args: " << argc << std::endl;
    const float confThreshold = 0.4f;
    const float iouThreshold = 0.4f;

    std::string modelPath = "yolov5m.onnx";
    std::string imagePath = "zidane.jpg";
    std::string classNamesPath = "coco.names";

    if (argc == 4)
    {
        modelPath = argv[1];
        classNamesPath = argv[2];
        imagePath = argv[3];
    }

    std::vector<std::string> classNames = utils::loadNames(classNamesPath);

    YOLODetector detector {nullptr};
    try
    {
        detector = YOLODetector(modelPath, true, cv::Size(640, 640));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    cv::Mat image = cv::imread(imagePath);
    std::vector<Detection> result = detector.detect(image, confThreshold, iouThreshold);

    utils::visualizeDetection(image, result, classNames);

    cv::imshow("result", image);

    // cv::imwrite("result.jpg", image);
    cv::waitKey(0);

    return 0;
}
