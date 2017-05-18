/**
 * @file os_port_rtx.h
 * @brief RTOS abstraction layer (Keil RTX)
 *
 * @section License
 *
 * Copyright (C) 2010-2017 Oryx Embedded SARL. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.7.6
 **/

#ifndef _OS_PORT_RTX_H
#define _OS_PORT_RTX_H

//Dependencies
#ifdef RTX_CUSTOM_HEADER
   #include RTX_CUSTOM_HEADER
#else
   #include "rtl.h"
#endif

//Maximum number of tasks that can be dynamically created
#ifndef OS_PORT_MAX_TASKS
   #define OS_PORT_MAX_TASKS 16
#elif (OS_PORT_MAX_TASKS < 1)
   #error OS_PORT_MAX_TASKS parameter is not valid
#endif

//Task priority (normal)
#ifndef OS_TASK_PRIORITY_NORMAL
   #define OS_TASK_PRIORITY_NORMAL 1
#endif

//Task priority (high)
#ifndef OS_TASK_PRIORITY_HIGH
   #define OS_TASK_PRIORITY_HIGH 2
#endif

//Milliseconds to system ticks
#ifndef OS_MS_TO_SYSTICKS
   #define OS_MS_TO_SYSTICKS(n) (n)
#endif

//System ticks to milliseconds
#ifndef OS_SYSTICKS_TO_MS
   #define OS_SYSTICKS_TO_MS(n) (n)
#endif

//Enter interrupt service routine
#define osEnterIsr()

//Leave interrupt service routine
#define osExitIsr(flag)


/**
 * @brief Task object
 **/

typedef struct
{
   OS_TID tid;
} OsTask;


/**
 * @brief Event object
 **/

typedef OS_SEM OsEvent;


/**
 * @brief Semaphore object
 **/

typedef OS_SEM OsSemaphore;


/**
 * @brief Mutex object
 **/

typedef OS_MUT OsMutex;


/**
 * @brief Task routine
 **/

typedef void (*OsTaskCode)(void *params);


/**
 * @brief Initialization task
 **/

typedef void (*OsInitTaskCode)(void);


//Kernel management
void osInitKernel(void);
void osStartKernel(OsInitTaskCode task);

//Task management
bool_t osCreateStaticTask(OsTask *task, const char_t *name, OsTaskCode taskCode,
   void *params, void *stack, size_t stackSize, int_t priority);

OsTask *osCreateTask(const char_t *name, OsTaskCode taskCode,
   void *params, size_t stackSize, int_t priority);

void osDeleteTask(OsTask *task);
void osDelayTask(systime_t delay);
void osSwitchTask(void);
void osSuspendAllTasks(void);
void osResumeAllTasks(void);

//Event management
bool_t osCreateEvent(OsEvent *event);
void osDeleteEvent(OsEvent *event);
void osSetEvent(OsEvent *event);
void osResetEvent(OsEvent *event);
bool_t osWaitForEvent(OsEvent *event, systime_t timeout);
bool_t osSetEventFromIsr(OsEvent *event);

//Semaphore management
bool_t osCreateSemaphore(OsSemaphore *semaphore, uint_t count);
void osDeleteSemaphore(OsSemaphore *semaphore);
bool_t osWaitForSemaphore(OsSemaphore *semaphore, systime_t timeout);
void osReleaseSemaphore(OsSemaphore *semaphore);

//Mutex management
bool_t osCreateMutex(OsMutex *mutex);
void osDeleteMutex(OsMutex *mutex);
void osAcquireMutex(OsMutex *mutex);
void osReleaseMutex(OsMutex *mutex);

//System time
systime_t osGetSystemTime(void);

//Memory management
void *osAllocMem(size_t size);
void osFreeMem(void *p);

//Undefine conflicting definitions
#undef htons
#undef htonl
#undef ntohs
#undef ntohl
#undef TCP_STATE_CLOSED
#undef TCP_STATE_LISTEN
#undef TCP_STATE_SYN_SENT
#undef TCP_STATE_CLOSING
#undef TCP_STATE_LAST_ACK

#endif
