/// 
/// File: solver.h
/// Description: solver.c is the interface file that represents all functions
/// being implemented by the BFS algorithm solver file, solver.c
///
/// @author Adam Pang (akp4339@rit.edu)
/// @date 04/15/2022
// // // // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef SOLVER_H
#define SOLVER_H

#define _DEFAULT_SOURCE_
#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "coordinates.h"
#include "structs.h"
#include "QueueADT.h"

/**
 * @brief Solves an instance of a maze when passed a MazeInstance.
 * 
 * @pre Entrance will always be the top left of the maze, at coordinates
 * (0, 0).
 * @pre Exit will always be the bottom right of the maze, at coordinates 
 * (row - 1, col - 1).
 * 
 * @param maze: MazeInstance that is being solved
 * @param stream: FILE * stream where information is being displayed
 * @param display_solution: Boolean representing specific data being checked
 * @param display_shortest: Boolean representing specific data being checked
 * @return void
 */
void solve(MazeInstance maze, FILE *stream, bool display_solution, bool display_shortest);

#endif // SOLVER_H