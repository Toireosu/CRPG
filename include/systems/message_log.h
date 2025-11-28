#ifndef MESSAGE_LOG_H
#define MESSAGE_LOG_H

#define MESSAGE_LOG_MAX_COUNT 50

/**
 * @brief Intializes the message log system.
 */
void MessageLog_Init();

/**
 * @brief Clears the message log.
 */
void MessageLog_Clear();

/**
 * @brief Pushes the given string as the first string in the message log.
 * 
 * @param entry The string to be added.
 * @note Pushes to front.
 */
void MessageLog_Push(const char* entry);

/**
 * @brief Gets the message entry at given index.
 * 
 * @param index The index at which the message to return resides.
 * @returns The message entry.
 */
const char* MessageLog_Get(int index);

#endif