/// 
/// File: coordinates.h
/// Description: coordinates.h is the interface file that primarily focuses
/// on all coordinate pair data structure functions and information
///
/// @author Adam Pang (akp4339@rit.edu)
/// @date 04/15/2022
// // // // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef COORDS_H
#define COORDS_H

#define _DEFAULT_SOURCE_
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "QueueADT.h"

/**
 * @brief Create a coordinate pair instance that stores information on a particular
 * coordinate 
 * 
 * @param row: Row value of coordinate
 * @param col: Column value of coordinate
 * @param bp: Backpointer referring to predecessor in MazeInstance
 * @return Coords: Coordinates structure instance
 */
Coords create_coords(int row, int col, Coords bp);

/**
 * @brief Get all valid open pathed neighbors next to a given Coords instance on a 
 * MazeInstance maze.
 * 
 * @param coords: Coordinates we're getting neighbors for
 * @param maze: MazeInstance being worked on
 * @param queue: QueueADT that stores neighbors
 * @param visited: QueueADT to store all coordinates malloc'ed for future free
 */
void get_neighbors(Coords coords, MazeInstance maze, QueueADT queue, QueueADT visited);

/**
 * @brief Get the row value of a particular coordinates instance
 * 
 * @param coords: Instance
 * @return int 
 */
int get_row(Coords coords);

/**
 * @brief Get the column value of a particular coordinates instance
 * 
 * @param coords: Instance
 * @return int 
 */
int get_col(Coords coords);

#endif