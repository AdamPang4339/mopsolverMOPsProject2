/// 
/// File: maze.c
/// Description: maze.c is a support file that implements functions related to 
/// creating and initializing the maze for mopsolver simulations.
///
/// @author Adam Pang (akp4339@rit.edu)
/// @date 04/12/2022
// // // // // // // // // // // // // // // // // // // // // // // // // // //

#define _DEFAULT_SOURCE_
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maze.h"
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
void pretty_print_maze(FILE *stream, MazeInstance mazeInstance) {
    // Default variables
    const char WALL_CHAR = '#';
    const char OPEN_CHAR = '.';
    const char PATH_CHAR = '+';
    int row_count = mazeInstance -> row_count;
    int col_count = mazeInstance -> col_count;

    // Print top border of maze first
    fprintf(stream, "|");
    for (int i = 0; i < col_count; i++) {
        fprintf(stream, "--");
    }
    fprintf(stream, "-|\n");

    // Print entrance opening in wall
    fprintf(stream, " ");

    // Print maze details
    for (int i = 0; i < row_count; i++) {
        if (i != 0) {
            fprintf(stream, "|");
        }

        for (int j = 0; j < col_count; j++) {
            if (mazeInstance -> maze[i][j] == 0 || mazeInstance -> maze[i][j] == 2) {
                fprintf(stream, " %c", OPEN_CHAR);
            }
            else if (mazeInstance -> maze[i][j] == 3) {
                fprintf(stream, " %c", PATH_CHAR);
            }
            else {
                fprintf(stream, " %c", WALL_CHAR);
            }
        }
        // Finish last space and right wall of each row
        if (i != row_count - 1) {
            fprintf(stream, " |\n"); 
        }
        else if (i == row_count - 1) {
            // Consider exit gap in bottom right of maze
            fprintf(stream, "  \n");
        }
    }

    // Print bottom border of maze
    fprintf(stream, "|");
    for (int i = 0; i< col_count; i++) {
        fprintf(stream, "--");
    }
    fprintf(stream, "-|\n");
}

/**
 * initialize_maze is the main function of the maze.c file that helps with
 * initializing the given maze. Closes input file after data is read.
 * 
 * @param infile: FILE pointer to the provided input file of where to initialize
 *          maze from.
 * @return MazeInstance: Completed maze instance in MazeInstance data structure
 */
MazeInstance initialize_maze(FILE *infile) {
    // Maze structure being returned
    MazeInstance init_maze;

    // Allocate proper space for Maze Instances
    init_maze = (MazeInstance) malloc( sizeof(struct mazeStruct) );

    // Initialize maze instance space
    if (init_maze != 0) {
        // Default int** maze size to be realloced later
        init_maze -> maze = (int **) malloc( 1 * sizeof(int) );
        init_maze -> row_count = 0;
        init_maze -> col_count = 0;
    }

    // Initialize necessary variables for parsing file for initial maze
    char *line = NULL;
    size_t line_length = 0;
    int readin = 0;

    // Get each line from input file to populate initial maze
    while ((readin = getline(&line, &line_length, infile)) >= 0) {
        // Start/Increment row counter
        init_maze -> row_count++;

        // If column counter has not been initialized before, assign
        // correct column count.
        if (init_maze -> col_count < 1) {
            init_maze -> col_count = readin / 2;
        }

        // Resize maze to encompass space for new row count
        init_maze -> maze = (int **) realloc(init_maze -> maze, (init_maze -> row_count * sizeof(int*)));
        // Resize each new row to have valid size
        init_maze -> maze[init_maze -> row_count - 1] = (int*) malloc(init_maze -> col_count * sizeof(int));

        // Cycle through each line of characters to get columns
        for (int i = 0; i < init_maze -> col_count; i++) {
            // Populate maze with each odd positioned character, 
            // going row by row ignoring spaces
            if (line[i * 2] == '1') {
                init_maze -> maze[init_maze -> row_count - 1][i] = 1;
            }
            else if (line[i * 2] == '0'){
                init_maze -> maze[init_maze -> row_count - 1][i] = 0;
            }
        }
    }

    // Close file after reading
    fclose(infile);

    if (line) {
        free(line);
    }

    return init_maze;
}

/**
 * @brief maze_destroy destroys a MazeInstance instance when given a 
 * pointer to the specific MazeInstance. 
 * 
 * @param instance: Pointer to MazeInstance
 */
void destroy_maze(MazeInstance instance) {
    // Free all rows that were allocated
    for (int i = 0; i < instance -> row_count; i++) {
        free(instance -> maze[i]);
    }
    // Free the 2d array maze that was malloc'ed
    free(instance -> maze);
    // Free the entire structure instance
    free(instance);
}

/**
 * @brief Get the number of rows of a particular maze instance
 * 
 * @param maze: Instance
 * @return int 
 */
int get_row_count(MazeInstance maze) {
    return maze -> row_count;
}

/**
 * @brief Get the number of columns of a particular maze instance
 * 
 * @param maze: Instance
 * @return int 
 */
int get_col_count(MazeInstance maze) {
    return maze -> col_count;
}

/**
 * @brief Get the integer found within the maze grid at the given coordinates
 * of row and column
 * 
 * @param maze: MazeInstance being checked
 * @param row
 * @param col 
 * @return int 
 */
int get_position(MazeInstance maze, int row, int col) {
    return maze -> maze[row][col];
}
