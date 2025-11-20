#ifndef EVENT_LOG_H
#define EVENT_LOG_H

#define EVENT_LOG_MAX_COUNT 50

typedef struct EventLog {
    char* data[EVENT_LOG_MAX_COUNT];
} EventLog;

void EventLog_Init(EventLog* log);
void EventLog_Push(EventLog* log, char* entry);
char* EventLog_Get(EventLog* log, int index);

#endif