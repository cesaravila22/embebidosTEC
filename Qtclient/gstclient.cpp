#include "gstclient.h"

gstclient::gstclient(){

}

int gstclient::reproducir(){
      /* Initialisation */
      gst_init (NULL, NULL);

      loop = g_main_loop_new (NULL, FALSE);

      /* Create gstreamer elements */
      pipeline = gst_pipeline_new ("audio-player");
      source = gst_element_factory_make ("udpsrc", "file-source");
      buffer  = gst_element_factory_make ("gstrtpjitterbuffer", "gst-buffer");
      rtp = gst_element_factory_make ("rtpL16depay", "audio-rtp");
      audioconv = gst_element_factory_make ("audioconvert", "audio-output");
      sink = gst_element_factory_make ("alsasink", "audio-sink");

      if (!pipeline || !source || !buffer || !rtp || !audioconv || !sink) {
        g_printerr ("One element could not be created. Exiting.\n");
        return -1;
      }

      /* Set up the pipeline */

      /* we set the input filename to the source element */
      g_object_set (G_OBJECT (source), "port", 5000 , NULL);
      filter_caps = gst_caps_from_string("application/x-rtp, media=(string)audio, clock-rate=44100, width=16, height=16, encoding-name=(string)L16,encoding-params=(string)1, channels=(int)1, channel-position=(int)1, payload=(int)96");
      g_object_set (G_OBJECT (source), "caps", filter_caps, NULL);

      /* we add all elements into the pipeline */
      gst_bin_add_many (GST_BIN (pipeline), source, buffer, rtp, audioconv, sink, NULL);

      /* we link the elements together */
      gst_element_link_many (source, buffer, rtp, audioconv, sink, NULL);

      /* Set the pipeline to "playing" state*/
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

int gstclient::detener(){
        /* Out of the main loop, clean up nicely */
        g_print ("Returned, stopping playback\n");
        gst_element_set_state (pipeline, GST_STATE_NULL);

        g_print ("Deleting pipeline\n");
        gst_object_unref (GST_OBJECT (pipeline));
        g_main_loop_unref (loop);
        return 0;
}
