#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <stdbool.h>

/** 
 * @brief Initialize the window manager and the window. 
 */
void WindowManager_Init();

/**
 * @brief Checks if window should be closed.
 * 
 * @param True if window should close, false otherwise.
 */
bool WindowManager_WindowShouldClose();


#endif