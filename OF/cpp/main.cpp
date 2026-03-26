#include"OpticalFlowProcessor.h"
#include<opencv2/core.hpp>

std::string CAMSET = "udpsrc port=5601 auto-multicast=0 ! application/x-rtp,media=video,encoding-name=H264 ! \
            rtpjitterbuffer latency=0 ! rtph264depay ! avdec_h264 ! videoconvert !\
            video/x-raw, format=BGR ! appsink drop=1";



int main() {
    CAMSET = "udpsrc port=42000 ! application/x-rtp,media=video,encoding-name=H264 !  rtph264depay ! avdec_h264 ! videoconvert ! appsink";
    
    
    // OpticalFlowProcessor ("/dev/video0", cv::CAP_ANY, 30, 640, 360, "H264");
    
    // OpticalFlowProcessor ("/dev/video2", cv::CAP_GSTREAMER, 30, 640, 360, "H264");

    // OpticalFlowProcessor ("udp://192.168.2.106:5601", cv::CAP_GSTREAMER, 30, 640, 360, "H264");
    
    // OpticalFlowProcessor (CAMSET, cv::CAP_GSTREAMER);

    OpticalFlowProcessor("test_video.mp4");

	return 0;
}
