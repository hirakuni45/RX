/**
 * @file os_port_chibios.c
 * @brief RTOS abstraction layer (ChibiOS/RT)
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

//Switch to the appropriate trace level
#define TRACE_LEVEL TRACE_LEVEL_OFF

//Dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "os_port.h"
#include "os_port_chibios.h"
#include "debug.h"

//Variables
static OsTask taskTable[OS_PORT_MAX_TASKS];
static uint_t *waTable[OS_PORT_MAX_TASKS];


/**
 * @brief Kernel initialization
 **/

void osInitKernel(void)
{
   //Initialize tables
   memset(taskTable, 0, sizeof(taskTable));
   memset(waTable, 0, sizeof(waTable));

   //Kernel initialization
   chSysInit();
}


/**
 * @brief Start kernel
 **/

void osStartKernel(void)
{
   //Terminate the main thread
   chThdExit(MSG_OK);
}


/**
 * @brief Create a static task
 * @param[out] task Pointer to the task structure
 * @param[in] name A name identifying the task
 * @param[in] taskCode Pointer to the task entry function
 * @param[in] params A pointer to a variable to be passed to the task
 * @param[in] stack Pointer to the stack
 * @param[in] stackSize The initial size of the stack, in words
 * @param[in] priority The priority at which the task should run
 * @return The function returns TRUE if the task was successfully
 *   created. Otherwise, FALSE is returned
 **/

bool_t osCreateStaticTask(OsTask *task, const char_t *name, OsTaskCode taskCode,
   void *params, void *stack, size_t stackSize, int_t priority)
{
   //Compute the size of the working area in bytes
   stackSize *= sizeof(uint_t);

   //Create a new task
   task->tp = chThdCreateStatic(stack, stackSize,
      priority, (tfunc_t) taskCode, params);

   //Check whether the task was successfully created
   if(task->tp != NULL)
      return TRUE;
   else
      return FALSE;
}


/**
 * @brief Create a new task
 * @param[in] name A name identifying the task
 * @param[in] taskCode Pointer to the task entry function
 * @param[in] params A pointer to a variable to be passed to the task
 * @param[in] stackSize The initial size of the stack, in words
 * @param[in] priority The priority at which the task should run
 * @return If the function succeeds, the return value is a pointer to the
 *   new task. If the function fails, the return value is NULL
 **/

OsTask *osCreateTask(const char_t *name, OsTaskCode taskCode,
   void *params, size_t stackSize, int_t priority)
{
   uint_t i;
   void *wa;
   OsTask *task = NULL;

   //Compute the size of the stack in bytes
   stackSize *= sizeof(uint_t);

   //Allocate a memory block to hold the working area
   wa = osAllocMem(THD_WORKING_AREA_SIZE(stackSize));

   //Successful memory allocation?
   if(wa != NULL)
   {
      //Enter critical section
      chSysLock();

      //Loop through task table
      for(i = 0; i < OS_PORT_MAX_TASKS; i++)
      {
         //Check whether the current entry is free
         if(taskTable[i].tp == NULL)
            break;
      }

      //Any entry available in the table?
      if(i < OS_PORT_MAX_TASKS)
      {
         //Create a new task
         taskTable[i].tp = chThdCreateI(wa, THD_WORKING_AREA_SIZE(stackSize),
            priority, (tfunc_t) taskCode, params);

         //Check whether the task was successfully created
         if(taskTable[i].tp != NULL)
         {
            //Insert the newly created task in the ready list
            chSchWakeupS(taskTable[i].tp, MSG_OK);

            //Save task pointer
            task = &taskTable[i];
            //Save working area base address
            waTable[i] = wa;

            //Leave critical section
            chSysUnlock();
         }
         else
         {
            //Leave critical section
            chSysUnlock();
            //Clean up side effects
            osFreeMem(wa);
         }
      }
      else
      {
         //Leave critical section
         chSysUnlock();
         //No entry available in the table
         osFreeMem(wa);
      }
   }

   //Return a pointer to the newly created task
   return task;
}


/**
 * @brief Delete a task
 * @param[in] task Pointer to the task to be deleted
 **/

void osDeleteTask(OsTask *task)
{
   //Delete the specified task
   if(task == NULL)
      chThdExit(MSG_OK);
   else
      chThdTerminate(task->tp);
}


/**
 * @brief Delay routine
 * @param[in] delay Amount of time for which the calling task should block
 **/

void osDelayTask(systime_t delay)
{
   //Delay the task for the specified duration
   chThdSleep(OS_MS_TO_SYSTICKS(delay));
}


/**
 * @brief Yield control to the next task
 **/

void osSwitchTask(void)
{
   //Force a context switch
   chThdYield();
}


/**
 * @brief Suspend scheduler activity
 **/

void osSuspendAllTasks(void)
{
   //Suspend scheduler activity
   chSysLock();
}


/**
 * @brief Resume scheduler activity
 **/

void osResumeAllTasks(void)
{
   //Resume scheduler activity
   chSysUnlock();
}


/**
 * @brief Create an event object
 * @param[in] event Pointer to the event object
 * @return The function returns TRUE if the event object was successfully
 *   created. Otherwise, FALSE is returned
 **/

bool_t osCreateEvent(OsEvent *event)
{
   //Initialize the binary semaphore object
   chBSemObjectInit(event, TRUE);

   //Event successfully created
   return TRUE;
}


/**
 * @brief Delete an event object
 * @param[in] event Pointer to the event object
 **/

void osDeleteEvent(OsEvent *event)
{
   //No resource to release
}


/**
 * @brief Set the specified event object to the signaled state
 * @param[in] event Pointer to the event object
 **/

void osSetEvent(OsEvent *event)
{
   //Set the specified event to the signaled state
   chBSemSignal(event);
}


/**
 * @brief Set the specified event object to the nonsignaled state
 * @param[in] event Pointer to the event object
 **/

void osResetEvent(OsEvent *event)
{
   //Force the specified event to the nonsignaled state
   chBSemReset(event, TRUE);
}


/**
 * @brief Wait until the specified event is in the signaled state
 * @param[in] event Pointer to the event object
 * @param[in] timeout Timeout interval
 * @return The function returns TRUE if the state of the specified object is
 *   signaled. FALSE is returned if the timeout interval elapsed
 **/

bool_t osWaitForEvent(OsEvent *event, systime_t timeout)
{
   msg_t msg;

   //Wait until the specified event is in the signaled
   //state or the timeout interval elapses
   if(timeout == 0)
   {
      //Non-blocking call
      msg = chBSemWaitTimeout(event, TIME_IMMEDIATE);
   }
   else if(timeout == INFINITE_DELAY)
   {
      //Infinite timeout period
      msg = chBSemWaitTimeout(event, TIME_INFINITE);
   }
   else
   {
      //Wait until the specified event becomes set
      msg = chBSemWaitTimeout(event, OS_MS_TO_SYSTICKS(timeout));
   }

   //Check whether the specified event is set
   if(msg == MSG_OK)
      return TRUE;
   else
      return FALSE;
}


/**
 * @brief Set an event object to the signaled state from an interrupt service routine
 * @param[in] event Pointer to the event object
 * @return TRUE if setting the event to signaled state caused a task to unblock
 *   and the unblocked task has a priority higher than the currently running task
 **/

bool_t osSetEventFromIsr(OsEvent *event)
{
   //Set the specified event to the signaled state
   chBSemSignalI(event);

   //The return value is not relevant
   return FALSE;
}


/**
 * @brief Create a semaphore object
 * @param[in] semaphore Pointer to the semaphore object
 * @param[in] count The maximum count for the semaphore object. This value
 *   must be greater than zero
 * @return The function returns TRUE if the semaphore was successfully
 *   created. Otherwise, FALSE is returned
 **/

bool_t osCreateSemaphore(OsSemaphore *semaphore, uint_t count)
{
   //Initialize the semaphore object
   chSemObjectInit(semaphore, count);

   //Semaphore successfully created
   return TRUE;
}


/**
 * @brief Delete a semaphore object
 * @param[in] semaphore Pointer to the semaphore object
 **/

void osDeleteSemaphore(OsSemaphore *semaphore)
{
   //No resource to release
}


/**
 * @brief Wait for the specified semaphore to be available
 * @param[in] semaphore Pointer to the semaphore object
 * @param[in] timeout Timeout interval
 * @return The function returns TRUE if the semaphore is available. FALSE is
 *   returned if the timeout interval elapsed
 **/

bool_t osWaitForSemaphore(OsSemaphore *semaphore, systime_t timeout)
{
   msg_t msg;

   //Wait until the semaphore is available or the timeout interval elapses
   if(timeout == 0)
   {
      //Non-blocking call
      msg = chSemWaitTimeout(semaphore, TIME_IMMEDIATE);
   }
   else if(timeout == INFINITE_DELAY)
   {
      //Infinite timeout period
      msg = chSemWaitTimeout(semaphore, TIME_INFINITE);
   }
   else
   {
      //Wait until the specified semaphore becomes available
      msg = chSemWaitTimeout(semaphore, OS_MS_TO_SYSTICKS(timeout));
   }

   //Check whether the specified semaphore is available
   if(msg == MSG_OK)
      return TRUE;
   else
      return FALSE;
}


/**
 * @brief Release the specified semaphore object
 * @param[in] semaphore Pointer to the semaphore object
 **/

void osReleaseSemaphore(OsSemaphore *semaphore)
{
   //Release the semaphore
   chSemSignal(semaphore);
}


/**
 * @brief Create a mutex object
 * @param[in] mutex Pointer to the mutex object
 * @return The function returns TRUE if the mutex was successfully
 *   created. Otherwise, FALSE is returned
 **/

bool_t osCreateMutex(OsMutex *mutex)
{
   //Initialize the mutex object
   chMtxObjectInit(mutex);

   //Mutex successfully created
   return TRUE;
}


/**
 * @brief Delete a mutex object
 * @param[in] mutex Pointer to the mutex object
 **/

void osDeleteMutex(OsMutex *mutex)
{
   //No resource to release
}


/**
 * @brief Acquire ownership of the specified mutex object
 * @param[in] mutex Pointer to the mutex object
 **/

void osAcquireMutex(OsMutex *mutex)
{
   //Obtain ownership of the mutex object
   chMtxLock(mutex);
}


/**
 * @brief Release ownership of the specified mutex object
 * @param[in] mutex Pointer to the mutex object
 **/

void osReleaseMutex(OsMutex *mutex)
{
   //Release ownership of the mutex object
#if (CH_KERNEL_MAJOR < 3)
   chMtxUnlock();
#else
   chMtxUnlock(mutex);
#endif
}


/**
 * @brief Retrieve system time
 * @return Number of milliseconds elapsed since the system was last started
 **/

systime_t osGetSystemTime(void)
{
   systime_t time;

   //Get current tick count
   time = chVTGetSystemTime();

   //Convert system ticks to milliseconds
   return OS_SYSTICKS_TO_MS(time);
}


/**
 * @brief Allocate a memory block
 * @param[in] size Bytes to allocate
 * @return A pointer to the allocated memory block or NULL if
 *   there is insufficient memory available
 **/

void *osAllocMem(size_t size)
{
   void *p;

   //Allocate a memory block
   p = chHeapAlloc(NULL, size);

   //Debug message
   TRACE_DEBUG("Allocating %" PRIuSIZE " bytes at 0x%08" PRIXPTR "\r\n", size, (uintptr_t) p);

   //Return a pointer to the newly allocated memory block
   return p;
}


/**
 * @brief Release a previously allocated memory block
 * @param[in] p Previously allocated memory block to be freed
 **/

void osFreeMem(void *p)
{
   //Make sure the pointer is valid
   if(p != NULL)
   {
      //Debug message
      TRACE_DEBUG("Freeing memory at 0x%08" PRIXPTR "\r\n", (uintptr_t) p);

      //Free memory block
      chHeapFree(p);
   }
}


/**
 * @brief Idle loop hook
 **/

void osIdleLoopHook(void)
{
   uint_t i;

   //Loop through task table
   for(i = 0; i < OS_PORT_MAX_TASKS; i++)
   {
      //Check whether current entry is used
      if(taskTable[i].tp != NULL)
      {
         //Wait for task termination
         if(chThdTerminatedX(taskTable[i].tp))
         {
            //Free working area
            osFreeMem(waTable[i]);

            //Mark the entry as free
            waTable[i] = NULL;
            taskTable[i].tp = NULL;
         }
      }
   }
}
