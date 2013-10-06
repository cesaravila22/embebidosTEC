#ifndef GSTMP3_H
#define GSTMP3_H
#include <QDebug>
#include <gst/gst.h>
#include <glib.h>

class gstmp3
{
public:
    gstmp3();
    int reproducir(QString direcc);
    int detener();
private:
    GMainLoop *loop;
    GstElement *pipeline, *source, *madmp3, *sink;
    GstBus *bus;
};

#endif // GSTMP3_H
