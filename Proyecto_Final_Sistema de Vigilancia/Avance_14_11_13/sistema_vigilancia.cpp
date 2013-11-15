#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <time.h>
#include <gst/gst.h>
#include <glib.h>

using namespace std;
using namespace cv;

int reproducir_alarma(GstElement *pipeline){
    gst_element_set_state (pipeline, GST_STATE_PLAYING);
    return 0;
}

int detener_alarma(GstElement *pipeline){
    gst_element_set_state (pipeline, GST_STATE_NULL);
    return 0;
}

int main (int argc, char * const argv[]){

	GstElement *pipeline, *source, *madmp3, *sink;
    GstBus *bus;
    guint bus_watch_id;

    /* Initialisation */
    gst_init (NULL, NULL);

    /* Create gstreamer elements */
    pipeline = gst_pipeline_new ("audio-player");
    source = gst_element_factory_make ("filesrc", "file-source");
    madmp3  = gst_element_factory_make ("mad", "mp3-plugin");
    sink = gst_element_factory_make ("alsasink", "audio-output");

    if (!pipeline || !source || !madmp3 || !sink) {
          g_printerr ("One element could not be created. Exiting.\n");
      return -1;
    }

    /* Set up the pipeline */
    /* we set the input filename to the source element */
    g_object_set (G_OBJECT (source), "location", "Sirena-Policia.mp3", NULL);
    /* we add all elements into the pipeline */
    gst_bin_add_many (GST_BIN (pipeline), source, madmp3, sink, NULL);
    /* we link the elements together */
    gst_element_link_many (source, madmp3, sink, NULL);
	
    const int DELAY = 100; // mseconds
	
	bool alarm_activated = false;
    
    // create all necessary instances
    CvCapture * camera = cvCaptureFromCAM(1);
    Mat next_frame_color = cvQueryFrame(camera);
    Mat current_frame_color = cvQueryFrame(camera);
	
    Mat current_frame, next_frame;
    
    cvtColor(current_frame_color, current_frame, CV_RGB2GRAY);
    cvtColor(next_frame_color, next_frame, CV_RGB2GRAY);  
	
    imshow("Motion1", current_frame);	  

    Mat d1, d2, result;
    int window = 200;
    bool movement;
    while (true)
    {
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
			if (alarm_activated){
				cout<<"Movement!\n";
			} else{
				alarm_activated = true;
				cout<<"Movement!\n";
				reproducir_alarma(pipeline);
			}
        }

        //imshow("Motion", result);
        
        next_frame.copyTo(current_frame);

        // semi delay and quit when press Q/q
        int key = cvWaitKey (DELAY);
        if (key == 'q' || key == 'Q'){
            break;
		}
		if (key == 's' || key == 'S'){
            detener_alarma(pipeline);
			alarm_activated = false;
		}

        //cvReleaseCapture(&camera);
        //camera = cvCaptureFromCAM(0);
        
        // get image from webcam
        next_frame_color = cvQueryFrame(camera);
        cvtColor(next_frame_color, next_frame, CV_RGB2GRAY);
    }
	return 0;
}
