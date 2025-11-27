#ifndef NAV_PATH_H
#define NAV_PATH_H

#include "kvec.h"
#include "data/coordinates.h"

typedef struct NavPath {
    bool success;
    union {
        kvec_t(Coordinates) path;
        const char* reason;
    } data;
} NavPath;

#endif