#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <time.h>

using namespace std;
using namespace cv;

int main (int argc, char * const argv[]){
	
    const int DELAY = 100; // mseconds
    
    // create all necessary instances
    CvCapture * camera = cvCaptureFromCAM(0);
    Mat next_frame_color = cvQueryFrame(camera);
    Mat current_frame_color = cvQueryFrame(camera);
	
	Mat current_frame, next_frame;
    
    cvtColor(current_frame_color, current_frame, CV_RGB2GRAY);
    cvtColor(next_frame_color, next_frame, CV_RGB2GRAY);  
	
	imshow("Motion1", current_frame);	  

    Mat d1, d2, result;
    int window = 200;
    bool movement;
    while (true){
		//imshow("Motion1", current_frame);	
		//imshow("Motion2", next_frame);
        
        movement = false;
		imshow("Motion1", next_frame);
        absdiff(next_frame, current_frame, d1);  	
        absdiff(current_frame, current_frame, d2);
        bitwise_xor(d1, d2, result);
        
        int middle_y = result.rows/2;
        int middle_x = result.cols/2;
        
        // Center window
        threshold(result, result, 140, 255, CV_THRESH_BINARY);
        for(int i = middle_x-window; i < middle_x+window; i++)
            for(int j = middle_y-window; j < middle_y+window; j++)
                if(result.at<int>(j,i)>0)
                {
                    movement = true;
                    break;
                }
        
        if(movement==true){
			cout<<"Movement!\n";	
        }

        //imshow("Motion", result);
        
        next_frame.copyTo(current_frame);

		// semi delay and quit when press Q/q
        int key = cvWaitKey (DELAY);
        if (key == 'q' || key == 'Q')
            break;

		//cvReleaseCapture(&camera);
		//camera = cvCaptureFromCAM(0);
        
        // get image from webcam
        next_frame_color = cvQueryFrame(camera);
        cvtColor(next_frame_color, next_frame, CV_RGB2GRAY);
    }
    
	return 0;
}
