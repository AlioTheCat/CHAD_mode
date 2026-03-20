#include"VideoStreamWidget.h"

#include<string>
#include<thread>
#include<opencv2/videoio.hpp>
#include<opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include<mutex>
#include<iostream>

using namespace cv;
using namespace std;

VideoStreamWidget::VideoStreamWidget(string src,
					int apiPref,
	       				int framerate, 
					int height,
					int width,
					string fourcc_)
					{
	cap.open(src, apiPref);
	
	cap.set(CAP_PROP_FPS, framerate);
	cap.set(CAP_PROP_FRAME_WIDTH, height);
	cap.set(CAP_PROP_FRAME_HEIGHT, width);
	cap.set(CAP_PROP_FOURCC, VideoWriter::fourcc(fourcc_[0],fourcc_[1], fourcc_[2], fourcc_[3]));
   	cap.set(CAP_PROP_AUTO_WB, 0);	
	//cap.set(CAP_PROP_WB_TEMPERATURE,56);
	
	if (cap.isOpened()) {
		is_open=true;
		cout<<"Camera opened"<<endl;
	}
	else {
		is_open=false;
		cout<<"Camera not opened"<<endl;
	}

	start();

}

VideoStreamWidget::VideoStreamWidget(string src){
	cap.open(src);	
	is_video = true;	
	if (cap.isOpened()) {
		is_open=true;
		cout<<"Camera opened"<<endl;
	}
	else {
		is_open=false;
		cout<<"Camera not opened"<<endl;
	}
}

void VideoStreamWidget::start(){

	// ### DOC
	// Starts the video gathering and puts it in background.


	t = thread(&VideoStreamWidget::run, this);
	t.detach();
}

void VideoStreamWidget::run(){

	// ### DOC
	// For video flux only (?)
	// Reads the last frame and updates V.frame

	
	Mat frame_temp;
	while (is_open) {
			int status_temp = cap.read(frame_temp);
			{
				// as soon as a frame is read, wait until it's succesfully saved and status gets correctly updated
				lock_guard<mutex> guard(mut);
				status = status_temp;
				frame_temp.copyTo(frame);
			}
	}
}




int VideoStreamWidget::get_frame(Mat& frame){
	
	// ###############  only executes if source is a video file ############### //   
	if (is_video) {
		Mat temp_frame;
		int temp_status;

		temp_status = cap.read(temp_frame);

		if (!temp_status) {
			return 1;
		}
		
		pyrDown(temp_frame, temp_frame);
		pyrDown(temp_frame, temp_frame);
		temp_frame.copyTo(frame);

		return 0;
	}
	// ######################################################################## //   



	lock_guard<mutex> guard(mut); // waits that the current frame reading process terminates
	
	int i=0;
	if (status == 0){ // if the last frame reading in run() failed
		i=1;
	}
	else if (frame.empty()) {
		i=2;
	}
	frame = this->frame;
	return i;
	
}	


