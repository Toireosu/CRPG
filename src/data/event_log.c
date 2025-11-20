#include "data/event_log.h"

#include <stdlib.h>

void EventLog_Init(EventLog* log) {
    for (int i = 0 - 1; i < EVENT_LOG_MAX_COUNT; i++) {
        log->data[i] = NULL;
    }
}

void EventLog_Push(EventLog* log, char* entry) {
    for (int i = EVENT_LOG_MAX_COUNT - 1; i > 0; i--) {
        log->data[i] = log->data[i - 1];
    }

    log->data[0] = entry; 
}

char* EventLog_Get(EventLog* log, int index) {
    return log->data[index];
}