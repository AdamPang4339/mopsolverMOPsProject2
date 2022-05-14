///
/// File: QueueADT.c
/// Description: QueueADT is the library source module file for implementing a queue 
/// data structure that allows queueing of different primitive types. 
///
/// @author Adam Pang (akp4339@rit.edu)
/// @date 03/22/2022
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>

#define _QUEUE_IMPL_
#define QUEUE_ALLOC_UNIT 64

/**
 * @brief Structure that holds design for the queue data structure
 * 
 */
struct queueStruct {
    // Number of items left in queue
    size_t num_items;
    // Capacity of space queue can hold
    size_t capacity;
    // Index/position of first valid item in queue
    size_t first_item;
    // Array of void pointers that point to contents in queue
    void **contents;
};

typedef struct queueStruct *QueueADT;

#include "QueueADT.h"
#include "structs.h"

/**
 * @brief Create a queue from a QueueADT structure that takes 
 * in a compare function
 * 
 * @param cmp Compare function for self-ordering queue
 * @return QueueADT 
 */
QueueADT que_create() {
    // Create new queueADT with malloc'ed size
    QueueADT new;
    new = (QueueADT) malloc( sizeof(struct queueStruct) );
    
    // If new queue is valid, default values to 0
    if (new != 0) {
        new -> capacity = 0;
        new -> contents = 0;
        new -> num_items = 0;
        new -> first_item = 1;
    }

    // Return new queue
    return(new);
}

/**
 * @brief Deallocate all contents used in queue
 * 
 * @param queue: Queue that needs to be freed
 */
void que_destroy(QueueADT queue) {
    assert(queue != 0);

    if (queue -> contents != 0) {
        free(queue -> contents);
    }

    free(queue);
}

/**
 * @brief Remove/Clear all contents and default back to 0
 * 
 * @param queue: Queue to be cleared
 */
void que_clear(QueueADT queue) {
    if (queue -> contents != 0) {
        free(queue -> contents);
        queue -> contents = 0;
    }
    queue -> capacity = 0;
    queue -> num_items = 0;
    queue -> first_item = 0;
}

/**
 * @brief Insert data into a queue based on compare function, 
 * or defaults to FIFO organization
 * 
 * @param queue: Queue to be added to
 * @param data: Data being inserted
 */
void que_insert(QueueADT queue, void *data) {
    // If queue is empty, add data directly into contents
    if (queue -> contents == 0) {
        queue -> contents = malloc(sizeof(void *) * QUEUE_ALLOC_UNIT);
        // Assert that contents address is grabbed
        // assert(queue -> contents != 0);
        if (queue -> contents == 0) {
            return;
        }
        queue -> capacity = QUEUE_ALLOC_UNIT;
        queue -> first_item = 0;
    }
    // If number of items exceeds capacity, reallocate space
    if ((queue -> num_items + queue -> first_item) >= queue -> capacity) {
        void **insertContents;
        insertContents = realloc(queue -> contents, sizeof(void *) * (queue -> capacity + QUEUE_ALLOC_UNIT));

        // Assert that contents exist
        // assert(insertContents != 0);
        if (insertContents == 0) {
            return;
        }

        // Increase capacity and update contents
        queue -> contents = insertContents;
        queue -> capacity += QUEUE_ALLOC_UNIT;
    }

    size_t index = queue -> first_item;
    // Assign index variable to last position for FIFO
    index = queue -> first_item + queue -> num_items;

    // Shift all elements over to free space for new data
    for (size_t i = (queue -> num_items + queue -> first_item); i > index; i -= 1) {
        queue -> contents[i] = queue -> contents[i - 1];
    }

    // Add data in proper position
    queue -> contents[index] = data;

    // Increment relevant counters
    queue -> num_items += 1;
}

/**
 * @brief Remove and return the first element of the queue
 * 
 * @param queue: Queue data is being removed from
 * @return void*: Pointer to data that was in first position
 */
void * que_remove(QueueADT queue) {
    void *data;

    // Assert that there is something to remove
    // assert(queue -> num_items > 0);
    if (queue -> num_items == 0) {
        return NULL;
    }
    
    // Track data being removed
    data = (void *) queue -> contents[queue -> first_item];
    queue -> first_item += 1;
    queue -> num_items -= 1;

    return(data);
}

/**
 * @brief Indicate whether the queue is empty 
 * 
 * @param queue: Queue being checked
 * @return true: Returns true if queue is empty
 * @return false: Returns false if queue is not empty
 */
bool que_empty(QueueADT queue) {
    return (queue -> num_items == 0);
}
