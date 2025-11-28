#ifndef NAV_PATH_H
#define NAV_PATH_H

#include "kvec.h"
#include "data/coordinates.h"

/** 
 * @struct NavPath
 * @brief A struct that contains either a path from start to end-node or a string containing a reason for not finding a path.
 */
typedef struct NavPath {
    bool success;
    union {
        kvec_t(Coordinates) path;
        const char* reason;
    } data;
} NavPath;

#endif