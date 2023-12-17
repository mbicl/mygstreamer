#include <gst/gst.h>
#include <stdio.h>

#ifdef __APPLE__ 
#include <TargetConditionals.h>
#endif

int tutorial_main(int argc, char* argv[]){
    GstElement* pipeline;
    GstBus* bus;
    GstMessage* msg;

    /* Initilize GStreamer */
    gst_init(&argc,&argv);

    /* Build the pipeline */
    char str[1<<9], buffer[1<<10];
    printf("Enter uri for video: ");
    scanf("%s",str);
    // Default video
    // str="https://gstreamer.freedesktop.org/data/media/sintel_trailer-480p.webm";
    sprintf(buffer,"playbin uri=%s",str);
    pipeline = gst_parse_launch(buffer,NULL);

    /* Start playing */
    gst_element_set_state(pipeline,GST_STATE_PLAYING);

    /* Wait until error or EOS (End of stream) */
    bus=gst_element_get_bus(pipeline);
    msg=gst_bus_timed_pop_filtered(
        bus,
        GST_CLOCK_TIME_NONE,
        GST_MESSAGE_ERROR | GST_MESSAGE_EOS
    );

    /* Error handling */
    if (GST_MESSAGE_TYPE(msg)==GST_MESSAGE_ERROR){
        g_error("An error occured! Re-run with GST_DEBUG=*:WARN environment "
        "variable set for more details");
    }

    /* Free resources */
    gst_message_unref(msg);
    gst_object_unref(bus);
    gst_element_set_state(pipeline,GST_STATE_NULL);
    gst_object_unref(pipeline);
    return 0;
}

int main(int argc, char* argv[]){

#if defined(__APPLE__) && TARGET_OS_MAC && !TARGET_OS_IPHONE
    return gst_macos_main(tutorial_main,argc,argv,NULL);
#else 
    return tutorial_main(argc,argv);
#endif
}