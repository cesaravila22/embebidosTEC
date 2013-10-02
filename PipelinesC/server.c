#include <gst/gst.h>
#include <glib.h>

static gboolean bus_call (GstBus *bus, GstMessage *msg, gpointer data) {
	GMainLoop *loop = (GMainLoop *) data;
	switch (GST_MESSAGE_TYPE (msg)) {
		case GST_MESSAGE_EOS:
			g_print ("End of stream\n");
			g_main_loop_quit (loop);
			break;
		case GST_MESSAGE_ERROR: {
			gchar *debug;
			GError *error;
			gst_message_parse_error (msg, &error, &debug);
			g_free (debug);
			g_printerr ("Error: %s\n", error->message);
			g_error_free (error);
			g_main_loop_quit (loop);
			break;
		}
		default:
			break;
	}
	return TRUE;
}

int main (int   argc, char *argv[]) {
  GMainLoop *loop;

  GstElement *pipeline, *source, *madmp3, *audioconv, *params, *rtp, *udp;
  GstBus *bus;
  GstCaps *filter_caps;
  guint bus_watch_id;

  /* Initialisation */
  gst_init (&argc, &argv);

  loop = g_main_loop_new (NULL, FALSE);


  /* Check input arguments */
  if (argc != 3) {
    g_printerr ("Usage: %s <MP3 filename> <IP_PC>\n", argv[0]);
    return -1;
  }

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
  g_object_set (G_OBJECT (source), "location", argv[1], NULL);
  filter_caps = gst_caps_from_string("audio/x-raw-int,channels=1,depth=16,width=16,rate=44100");
  g_object_set (G_OBJECT (params), "caps", filter_caps, NULL);
  g_object_set (G_OBJECT (udp), "host", argv[2], NULL);
  g_object_set (G_OBJECT (udp), "port", 5000 , NULL);

  /* we add a message handler */
  bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
  gst_object_unref (bus);

  /* we add all elements into the pipeline */
  gst_bin_add_many (GST_BIN (pipeline), source, madmp3, audioconv, params, rtp, udp, NULL);

  /* we link the elements together */
  gst_element_link_many (source, madmp3, audioconv, params, rtp, udp, NULL);

  /* Set the pipeline to "playing" state*/
  g_print ("Now playing: %s\n", argv[1]);
  gst_element_set_state (pipeline, GST_STATE_PLAYING);

  /* Iterate */
  g_print ("Running...\n");
  g_main_loop_run (loop);

  /* Out of the main loop, clean up nicely */
  g_print ("Returned, stopping playback\n");
  gst_element_set_state (pipeline, GST_STATE_NULL);

  g_print ("Deleting pipeline\n");
  gst_object_unref (GST_OBJECT (pipeline));
  g_source_remove (bus_watch_id);
  g_main_loop_unref (loop);

  return 0;
}
