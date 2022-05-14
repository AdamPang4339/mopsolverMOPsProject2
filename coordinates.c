/// 
/// File: coordinates.c
/// Description: coordinates.c is the source file that primarily focuses
/// on all coordinate pair data structure functions and information
///
/// @author Adam Pang (akp4339@rit.edu)
/// @date 04/15/2022
// // // // // // // // // // // // // // // // // // // // // // // // // // //

#define _DEFAULT_SOURCE_
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "coordinates.h"
#include "QueueADT.h"
#include "maze.h"

/**
 * @brief Create a coordinate pair instance that stores information on a particular
 * coordinate 
 * 
 * @param row: Row value of coordinate
 * @param col: Column value of coordinate
 * @param bp: Backpointer referring to predecessor in MazeInstance
 * @return Coords: Coordinates structure instance
 */
Coords create_coords(int row, int col, Coords bp) {
    Coords new_coords;

    // Allocate space for new coordinate instance
    new_coords = (Coords) malloc( sizeof(struct coordsStruct) );

    if (new_coords != 0) {
        new_coords -> row = row;
        new_coords -> col = col;
        new_coords -> previousCoords = bp;
    }

    return new_coords;
}

/**
 * @brief Get the row value of a particular coordinates instance
 * 
 * @param coords: Instance
 * @return int 
 */
int get_row(Coords coords) {
    return coords -> row;
}

/**
 * @brief Get the column value of a particular coordinates instance
 * 
 * @param coords: Instance
 * @return int 
 */
int get_col(Coords coords) {
    return coords -> col;
}

/**
 * @brief Get all valid open pathed neighbors next to a given Coords instance on a 
 * MazeInstance maze.
 * 
 * @param coords: Coordinates we're getting neighbors for
 * @param maze: MazeInstance being worked on
 * @param queue: QueueADT that stores neighbors
 * @param visited: QueueADT to store all coordinates malloc'ed for future free
 */
void get_neighbors(Coords coords, MazeInstance maze, QueueADT queue, QueueADT visited) {
    // Get main 4 directions
    int directions[4][2] = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };

    // Loop through all four directions
    for (int i = 0; i < 4; i++) {
        int neighbor_row = coords -> row + directions[i][0];
        int neighbor_col = coords -> col + directions[i][1];

        if (neighbor_row >= 0 && neighbor_row < maze -> row_count) {
            if (neighbor_col >= 0 && neighbor_col < maze -> col_count) {
                // If neighbor is empty path, then add to potential neighbors list
                if (maze -> maze[neighbor_row][neighbor_col] == 0) {
                    // Create new neighbor coords
                    Coords neighbor = create_coords(neighbor_row, neighbor_col, coords);

                    // Insert new unique neighbor to queue
                    que_insert(queue, neighbor);
                    que_insert(visited, neighbor);

                    // Mark neighbors as visited to prevent duplicate enqueues of same position
                    maze -> maze[neighbor_row][neighbor_col] = 2;
                }
            }
        }
    }
}

