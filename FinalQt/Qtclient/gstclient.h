#ifndef GSTCLIENT_H
#define GSTCLIENT_H
#include <QDebug>
#include <gst/gst.h>
#include <glib.h>

class gstclient
{
public:
    gstclient();
    int reproducir();
    int detener();
private:
    GMainLoop *loop;
    GstElement *pipeline, *source, *buffer, *rtp, *audioconv, *sink;
    GstBus *bus;
    GstCaps *filter_caps;
};

#endif // GSTCLIENT_H
