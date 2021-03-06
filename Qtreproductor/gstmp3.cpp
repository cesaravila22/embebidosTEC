#include "gstmp3.h"

gstmp3::gstmp3(){

}

int gstmp3::reproducir(QString direcc){

        /* Initialisation */
        gst_init (NULL, NULL);

        loop = g_main_loop_new (NULL, FALSE);

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
        g_object_set (G_OBJECT (source), "location", direcc.toStdString().c_str(), NULL);

        /* we add a message handler */
        bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));

        /* we add all elements into the pipeline */
        gst_bin_add_many (GST_BIN (pipeline), source, madmp3, sink, NULL);

        /* we link the elements together */
        gst_element_link_many (source, madmp3, sink, NULL);

        /* Set the pipeline to "playing" state*/
        g_print ("Now playing: %s\n", direcc.toStdString().c_str());
        gst_element_set_state (pipeline, GST_STATE_PLAYING);

        /* Iterate */
        g_print ("Running...\n");
        g_main_loop_run (loop);

        /* Out of the main loop, clean up nicely */
        g_print ("Returned, stopping playback\n");
        gst_element_set_state (pipeline, GST_STATE_NULL);

        g_print ("Deleting pipeline\n");
        gst_object_unref (GST_OBJECT (pipeline));
        g_main_loop_unref (loop);
        return 0;
}

int gstmp3::detener(){
        /* Out of the main loop, clean up nicely */
        g_print ("Returned, stopping playback\n");
        gst_element_set_state (pipeline, GST_STATE_NULL);

        g_print ("Deleting pipeline\n");
        gst_object_unref (GST_OBJECT (pipeline));
        g_main_loop_unref (loop);
        return 0;
}

