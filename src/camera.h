/*
 * Abstract camera interface. Glues the hacky camera driver code to the art code.
 * Assumes the camera driver runs in a separate thread. Handles raw data as it arrives
 * from USB, without any copying or post-processing.
 *
 * 2014, Micah Elizabeth Scott <micah@scanlime.org>
 *
 * This file is released into the public domain.
 */

#pragma once

#include <stdint.h>
#include "lib/tinythread.h"

namespace Camera {

    // Video format is UYVY, two bytes per pixel, 720 pixels per line. Assume NTSC video.
    // http://www.fourcc.org/yuv.php#UYVY

    static const unsigned kBytesPerPixel = 2;
    static const unsigned kPixelsPerLine = 720;
    static const unsigned kBytesPerLine = kBytesPerPixel * kPixelsPerLine;
    static const unsigned kFields = 2;
    static const unsigned kLinesPerField = 240;

    struct VideoChunk {
        const uint8_t *data;
        unsigned byteCount;
        unsigned byteOffset;
        unsigned line;
        unsigned field;
    };

    typedef void (*videoCallback_t)(const VideoChunk &video, void *context);

    // Start the camera on a new thread
    tthread::thread* start(videoCallback_t callback, void *context = 0);
};
