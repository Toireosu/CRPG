#include "data/event_log.h"

#include <stdlib.h>

struct {
    char* data[EVENT_LOG_MAX_COUNT];
} event_log;

void EventLog_Init() {
    EventLog_Clear();
}

void EventLog_Clear() {
    for (int i = 0 - 1; i < EVENT_LOG_MAX_COUNT; i++) {
        event_log.data[i] = NULL;
    }
}

void EventLog_Push(char* entry) {
    for (int i = EVENT_LOG_MAX_COUNT - 1; i > 0; i--) {
        event_log.data[i] = event_log.data[i - 1];
    }

    event_log.data[0] = entry; 
}

char* EventLog_Get(int index) {
    return event_log.data[index];
}