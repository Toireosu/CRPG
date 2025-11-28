#include "systems/message_log.h"

#include <stdlib.h>

struct {
    const char* data[MESSAGE_LOG_MAX_COUNT];
} message_log;

void MessageLog_Init() {
    MessageLog_Clear();
}

void MessageLog_Clear() {
    for (int i = 0; i < MESSAGE_LOG_MAX_COUNT; i++) {
        message_log.data[i] = NULL;
    }
}

void MessageLog_Push(const char* entry) {
    for (int i = MESSAGE_LOG_MAX_COUNT - 1; i > 0; i--) {
        message_log.data[i] = message_log.data[i - 1];
    }

    message_log.data[0] = entry; 
}

const char* MessageLog_Get(int index) {
    return message_log.data[index];
}