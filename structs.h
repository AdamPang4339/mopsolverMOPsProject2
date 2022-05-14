/// 
/// File: structs.h
/// Description: structs.h is the header file to export main typedef structs
/// being used for a mopsolver simulation
///
/// @author Adam Pang (akp4339@rit.edu)
/// @date 04/13/2022
// // // // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef STRUCTS_H
#define STRUCTS_H

/**
 * @brief Structure to represent maze instances
 */
struct mazeStruct {
    // Integer grid representing the maze provided
    int **maze;
    // Integers representing row and column count of maze
    int row_count;
    int col_count;
};
typedef struct mazeStruct *MazeInstance;

/**
 * @brief Structure that holds design for coordinates of each cell in MazeInstances
 */
typedef struct coordsStruct *Coords;
struct coordsStruct {
    int row;
    int col;
    Coords previousCoords;
};

#endif // STRUCTS_H