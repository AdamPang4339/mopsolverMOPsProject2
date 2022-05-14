///
/// File: QueueADT.h
/// Description: QueueADT is the interface file for the QueueADT.c file for enqueueing and
/// dequeueing
///
/// @author Adam Pang (akp4339@rit.edu)
/// @date 04/14/2022
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef _QUEUEADT_H_
#define _QUEUEADT_H_

#include <stdbool.h>
#include "structs.h"

#ifndef _QUEUE_IMPL_

/// QueueADT is a pointer to coordinates

typedef struct queueStruct * QueueADT;

#endif

/**
 * @brief Create a simple queue data structure that takes in coordinates
 * of points on a particular maze in a mopsolver simulation
 * 
 * @return a QueueADT instance, or NULL if the allocation fails
 */
QueueADT que_create();

/**
 * @brief Deallocate and destroy provided queue
 * 
 * @param queue: the QueueADT to be destroyed
 */
void que_destroy( QueueADT queue );


/**
 * @brief Remove all contents found within a particular given queue
 * 
 * @param queue: Queue to be cleared
 */
void que_clear( QueueADT queue );


/// Insert the specified data into the back of the queue
///
/// @param queue the QueueADT into which the value is to be inserted
/// @param data the data to be inserted

/**
 * @brief Insert the specified data into the back of the queue
 * 
 * @param queue: the QueueADT into which the value is to be inserted
 * @param data: the data to be inserted
 */
void que_insert( QueueADT queue, void * data );


/// Remove and return the first element from the QueueADT.
///
/// @param queue the QueueADT to be manipulated
/// @return the value that was removed from the queue
/// @exception If the queue is empty, the program should terminate
///     with an error message.  This can be done by printing an
///     appropriate message to the standard error output and then
///     exiting with EXIT_FAILURE, or by having an assert() fail.

/**
 * @brief Remove and return the first element of the queue
 * 
 * @param queue: Queue being analyzed
 * @return Coords: Coord pair being returned
 */
void * que_remove( QueueADT queue );

/// Indicate whether or not the supplied Queue is empty
///
/// @param the QueueADT to be tested
/// @return true if the queue is empty, otherwise false

bool que_empty( QueueADT queue );


#endif

