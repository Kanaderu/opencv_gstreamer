#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


int main() {

    //cv::VideoCapture cap(0);
    cv::VideoCapture cap(
        "videotestsrc ! video/x-raw,framerate=20/1 ! videoscale ! videoconvert ! appsink",
        cv::CAP_GSTREAMER
    );

    if (!cap.isOpened()) {
        std::cerr << "VideoCapture is not opened!" << std::endl;
        std::exit(-1);
    }

    cv::VideoWriter writer(
        "appsrc ! videoconvert ! video/x-raw,format=YUY2,width=640,height=480,framerate=30/1 ! jpegenc ! rtpjpegpay ! udpsink host=127.0.0.1 port=5000",
        0, // fourcc
        30, // fps
        cv::Size(640, 480),
        true // isColor
    );

    if (!writer.isOpened()) {
        std::cerr << "VideoWriter is not opened!" << std::endl;
        std::exit(-2);
    }

    while (true) {
        cv::Mat frame, upscaledFrame;
        cap.read(frame);
        cv::resize(frame, upscaledFrame, cv::Size(640, 480));
        cv::imshow("sender", upscaledFrame);
        if (cv::waitKey(1) == 27) {
            break;
        }
        writer.write(upscaledFrame);
    }

    return 0;
}