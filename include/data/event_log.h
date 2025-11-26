#ifndef EVENT_LOG_H
#define EVENT_LOG_H

#define EVENT_LOG_MAX_COUNT 50

void EventLog_Init();
void EventLog_Clear();
void EventLog_Push(char* entry);
char* EventLog_Get(int index);

#endif