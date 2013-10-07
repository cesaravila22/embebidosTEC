#include "gstserver.h"

gstserver::gstserver(){

}

int gstserver::reproducir(QString direcc,QString ip){
        /* Initialisation */
        gst_init (NULL, NULL);

        loop = g_main_loop_new (NULL, FALSE);

        /* Create gstreamer elements */
        pipeline = gst_pipeline_new ("audio-player");
        source = gst_element_factory_make ("filesrc", "file-source");
        madmp3  = gst_element_factory_make ("mad", "mp3-plugin");
        audioconv = gst_element_factory_make ("audioconvert", "audio-output");
        params = gst_element_factory_make ("capsfilter", "capsfilter");
        rtp = gst_element_factory_make ("rtpL16pay", "audio-rtp");
        udp = gst_element_factory_make ("udpsink", "udp-emisor");

        if (!pipeline || !source || !madmp3 || !audioconv || !params || !rtp || !udp) {
            g_printerr ("One element could not be created. Exiting.\n");
            return -1;
        }

        /* Set up the pipeline */

        /* we set the input filename to the source element */
        g_object_set (G_OBJECT (source), "location", direcc.toStdString().c_str(), NULL);
        filter_caps = gst_caps_from_string("audio/x-raw-int,channels=1,depth=16,width=16,rate=44100");
        g_object_set (G_OBJECT (params), "caps", filter_caps, NULL);
        g_object_set (G_OBJECT (udp), "host", ip.toStdString().c_str(), NULL);
        g_object_set (G_OBJECT (udp), "port", 5000 , NULL);

      /* we add all elements into the pipeline */
      gst_bin_add_many (GST_BIN (pipeline), source, madmp3, audioconv, params, rtp, udp, NULL);

      /* we link the elements together */
      gst_element_link_many (source, madmp3, audioconv, params, rtp, udp, NULL);

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

int gstserver::detener(){
        /* Out of the main loop, clean up nicely */
        g_print ("Returned, stopping playback\n");
        gst_element_set_state (pipeline, GST_STATE_NULL);

        g_print ("Deleting pipeline\n");
        gst_object_unref (GST_OBJECT (pipeline));
        g_main_loop_unref (loop);
        return 0;
}
