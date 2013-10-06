#ifndef GSTSERVER_H
#define GSTSERVER_H
#include <QDebug>
#include <gst/gst.h>
#include <glib.h>

class gstserver
{
public:
    gstserver();
    int reproducir(QString direcc,QString ip)
    int detener();
private:
    GMainLoop *loop;
  	GstElement *pipeline, *source, *madmp3, *audioconv, *params, *rtp, *udp;
  	GstBus *bus;
  	GstCaps *filter_caps;
};

#endif // GSTSERVER_H
