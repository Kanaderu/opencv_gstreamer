#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


int main() {

    cv::VideoCapture cap(
        "udpsrc port=5000 ! application/x-rtp,media=video,payload=26,clock-rate=90000,encoding-name=JPEG,framerate=30/1 ! rtpjpegdepay ! jpegdec ! videoconvert ! appsink",
        cv::CAP_GSTREAMER
    );
    /*
    cv::VideoCapture cap(
        "videotestsrc ! video/x-raw,framerate=20/1 ! videoscale ! videoconvert ! appsink",
        cv::CAP_GSTREAMER
    );
    */

    if (!cap.isOpened()) {
        std::cerr << "VideoCapture is not opened!" << std::endl;
        std::exit(-1);
    }

    while (true) {
        cv::Mat frame;
        cap.read(frame);
        cv::imshow("receiver", frame);
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    return 0;
}