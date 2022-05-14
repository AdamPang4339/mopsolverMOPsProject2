/// 
/// File: maze.h
/// Description: maze.h is the header file for representing all the functions
/// provided by maze.c that allows functionality with maze data structures.
///
/// @author Adam Pang (akp4339@rit.edu)
/// @date 04/13/2022
// // // // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef MAZE_H
#define MAZE_H

#define _DEFAULT_SOURCE_
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

/**
 * pretty_print_maze accepts a MazeInstance and prints out a character equivalent of
 * the maze found within given instance. # represents wall characters, and . represents
 * open characters where the solution of the maze may pass through.
 * 
 * @param mazeInstance: MazeInstance being printed
 * @param stream: FILE* that indicates where data is outputted
 * @return None
 */
void pretty_print_maze(FILE *stream, MazeInstance maze);

/**
 * initialize_maze is the main function of the maze.c file that helps with
 * initializing the given maze. Closes input file after data is read.
 * 
 * @param infile: FILE pointer to the provided input file of where to initialize
 *          maze from.
 * @return MazeInstance: Completed maze instance in MazeInstance data structure
 */
MazeInstance initialize_maze(FILE *infile);

/**
 * @brief copy_maze copies a given maze into a new MazeInstance and returns the
 * duplicate. 
 * 
 * @param old_maze: Maze to be replicated
 * @return MazeInstance: Maze that has been duplicated from original
 */
MazeInstance copy_maze(MazeInstance old_maze);

/**
 * @brief maze_destroy destroys a MazeInstance instance when given a 
 * pointer to the specific MazeInstance. 
 * 
 * @param instance: Pointer to MazeInstance
 */
void destroy_maze(MazeInstance instance);

/**
 * @brief Get the number of rows of a particular maze instance
 * 
 * @param maze: Instance
 * @return int 
 */
int get_row_count(MazeInstance maze);

/**
 * @brief Get the number of columns of a particular maze instance
 * 
 * @param maze: Instance
 * @return int 
 */
int get_col_count(MazeInstance maze);

/**
 * @brief Get the integer found within the maze grid at the given coordinates
 * of row and column
 * 
 * @param row
 * @param col 
 * @return int 
 */
int get_position(MazeInstance maze, int row, int col);

#endif // MAZE_H