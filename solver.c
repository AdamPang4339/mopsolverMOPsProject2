/// 
/// File: solver.c
/// Description: solver.c is the file that solves a mopsolver simulation using
/// a Breadth First Search algorithm for shortest path possible.
///
/// @author Adam Pang (akp4339@rit.edu)
/// @date 04/15/2022
// // // // // // // // // // // // // // // // // // // // // // // // // // //

#include <stdbool.h>
#include "solver.h"
#include "QueueADT.h"
#include "coordinates.h"
#include "maze.h"
#include "structs.h"

/**
 * @brief Helper method that returns whether or not a particular
 * coords is the exit of the maze.
 * 
 * @param coords: Coords being checked
 * @param row: Row value of solution
 * @param col: Column value of solution
 * @return bool: True if coords is solution, false otherwise
 */
static bool isSolutionCoords(Coords coords, int row, int col) {
    if ((get_col(coords) == col) && (get_row(coords) == row)) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief Helper method that outputs information to a FILE *stream
 * 
 * @param stream: Where to output
 * @param MazeInstance: Maze being printed data from
 * @param path_size: Data being outputted
 * @param display_solution: Boolean value pertaining to particular data
 * @param display_shortest: Boolean value pertaining to particular data
 * @return void
 */
static void printData(FILE* stream, MazeInstance maze, int path_size, bool display_solution, bool display_shortest) {
    if (display_shortest) {
        if (path_size != 0) {
            fprintf(stream, "Solution in %d steps.\n", path_size);
        }
        else {
            if (stream == stdout) {
                fprintf(stdout, "No solution.\n");
            }
            else {
                fprintf(stream, "No solution.\n");
            }
        }
    }
    if (display_solution) {
        pretty_print_maze(stream, maze);
    }
}

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
void solve(MazeInstance maze, FILE *stream, bool display_solution, bool display_shortest) {
    QueueADT queue = que_create();
    QueueADT visited = que_create();
    const int SOLUTION_COL = maze -> col_count - 1;
    const int SOLUTION_ROW = maze -> row_count - 1;
    int path_size = 0;

    // Check if entrance is valid
    if (maze -> maze[0][0] == 0) {
        Coords entrance = create_coords(0, 0, NULL);
        // Insert initial start coordinate of maze into queue and visited
        que_insert(queue, entrance);
        que_insert(visited, entrance);
    }

    // If queue is not empty, then keep parsing coordinates for neighbors
    while (!que_empty(queue)) {
        // Pop and grab first coordinate available
        Coords curr_coords = que_remove(queue);

        if (isSolutionCoords(curr_coords, SOLUTION_ROW, SOLUTION_COL)) {
            // Get path of solution
            while (curr_coords != NULL) {
                // Mark solution path with 3s (2 = visited)
                maze -> maze[curr_coords -> row][curr_coords -> col] = 3;
                path_size++;

                curr_coords = curr_coords -> previousCoords;
            }

            break;
        }

        // Continue to populate queue with possible neighbor coords and 
        // mark visited neighbors within visited for future free
        get_neighbors(curr_coords, maze, queue, visited);
    }

    // Print data to specified stream
    printData(stream, maze, path_size, display_solution, display_shortest);
    if (stream != stdout) {
        fclose(stream);
    }

    // Free all neighbor coordinates that were malloc'ed space
    while (!que_empty(visited)) {
        free(que_remove(visited));
    }
    // Free actual queueADT's
    que_destroy(visited);
    que_destroy(queue);
}