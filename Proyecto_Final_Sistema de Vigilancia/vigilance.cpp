#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <time.h>
#include <gst/gst.h>
#include <glib.h>

using namespace std;
using namespace cv;

/* Function used to start the pipeline */
int play_alarm(GstElement *pipeline){
    gst_element_set_state (pipeline, GST_STATE_PLAYING);
    return 0;
}

/* Function used to stop the pipeline */
int stop_alarm(GstElement *pipeline){
    gst_element_set_state (pipeline, GST_STATE_NULL);
    return 0;
}

/* Main function of the program */
int main (int argc, char * const argv[]){

	/* Initialize the pipeline with all its arguments */
	GstElement *pipeline, *source, *madmp3, *sink;
    GstBus *bus;
    guint bus_watch_id;

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
    /* Set the input filename to the source element */
    g_object_set (G_OBJECT (source), "location", "Sirena-Policia.mp3", NULL);

    /* Add all elements into the pipeline */
    gst_bin_add_many (GST_BIN (pipeline), source, madmp3, sink, NULL);

    /* Link the elements together */
    gst_element_link_many (source, madmp3, sink, NULL);
	
	/* Delay in ms */
    const int DELAY = 100;
	
	/* Variable used to check alarm on or off */	
	bool alarm_activated = false;
    
    /* Initialize all necesary instances for opencv */
	/* Get capture from camera */
    CvCapture * camera = cvCaptureFromCAM(1);
	/* Initialize 2 matrixes for comparition purposes */
    Mat next_frame_color = cvQueryFrame(camera);
    Mat current_frame_color = cvQueryFrame(camera);
	
    Mat current_frame, next_frame;
    
	/* Convert the matrixes from color to gray scale */
    cvtColor(current_frame_color, current_frame, CV_RGB2GRAY);
    cvtColor(next_frame_color, next_frame, CV_RGB2GRAY);  
	
	/* Initialize the window */
    imshow("Motion1", current_frame);	  

	/* Initialize the loop to start detecting movement */
    Mat d1, d2, result;
    int window = 200;
    bool movement;
    while (true)
    {        
        movement = false;
        imshow("Motion1", next_frame);
		/* Get difference between matrixes */
        absdiff(next_frame, current_frame, d1);  	
        absdiff(current_frame, current_frame, d2);
        bitwise_xor(d1, d2, result);
        
        int middle_y = result.rows/2;
        int middle_x = result.cols/2;
        
        /* Center window */
        threshold(result, result, 140, 255, CV_THRESH_BINARY);
        for(int i = middle_x-window; i < middle_x+window; i++)
            for(int j = middle_y-window; j < middle_y+window; j++)
                if(result.at<int>(j,i)>0)
                {
                    movement = true;
                    break;
                }
        
		/* Action taken when movement */
        if(movement==true){
			if (alarm_activated){
				cout<<"Movement!\n";
			} else{
				alarm_activated = true;
				cout<<"Movement!\n";
				play_alarm(pipeline);
			}
        }

		/* Copy the future matrix in the current matrix */        
        next_frame.copyTo(current_frame);

        /* Delay to wait for action: quit program when press Q/q, stop alarm when press S/s */
        int key = cvWaitKey (DELAY);
        if (key == 'q' || key == 'Q'){
            break;
		}
		if (key == 's' || key == 'S'){
            stop_alarm(pipeline);
			alarm_activated = false;
		}
        
        /* Get new image from webcam for comparison */
        next_frame_color = cvQueryFrame(camera);
        cvtColor(next_frame_color, next_frame, CV_RGB2GRAY);
    }
	return 0;
}
