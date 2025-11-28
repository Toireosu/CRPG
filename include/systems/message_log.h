#ifndef MESSAGE_LOG_H
#define MESSAGE_LOG_H

#define MESSAGE_LOG_MAX_COUNT 50

void MessageLog_Init();
void MessageLog_Clear();
void MessageLog_Push(const char* entry);
char* MessageLog_Get(int index);

#endif