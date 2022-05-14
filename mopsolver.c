/// 
/// File: mopsolver.c
/// Description: mopsolver.c is the main driving file that simulates the solving
/// mechanics and displays information related to mazes given an entrance at the
/// top left of the maze, and exit at the bottom right of the maze (N-1, M-1).
///
/// @author Adam Pang (akp4339@rit.edu)
/// @date 04/11/2022
// // // // // // // // // // // // // // // // // // // // // // // // // // //

#define _DEFAULT_SOURCE
#include <stdio.h>         // For macros and standard input/output
#include <stdlib.h>        // For other macros and standard library functions
#include <getopt.h>        // Required to process for "-flag" command 
                           // line arguments
#include <stdbool.h>
#include "maze.h"          // Include maze header file for maze data structures
#include "solver.h"
#include "coordinates.h"
#include "QueueADT.h"
#include "structs.h"

/**
 * Helper method usage_help() displays the proper usage command example for
 * calling the mopsolver simulation to solve mazes.
 * 
 * @param isValid: Boolean that represents if output is stdout or stderr
 * @return void: Returns nothing
 */
void usage_help(bool isValid) {
    if (isValid) {
        fprintf(stdout, "Usage:\nmopsolver [-hdsp] [-i INFILE] [-o OUTFILE]\n");
    }
    else {
        fprintf(stderr, "Usage:\nmopsolver [-hdsp] [-i INFILE] [-o OUTFILE]\n");
    }
}

/**
 * Helper method usage_options() displays the list of example flags for
 * calling the mopsolver simulation to solve mazes.
 * 
 * Prints the following:
 * Options:
 *   -h          Print usage and options list to stdout only.    (Default: off)
 *   -d          Pretty-print (display) the maze after reading.  (Default: off)
 *   -s          Print length of shortest path or 'No solution'. (Default: off)
 *   -p          Pretty-print maze with the path, if one exists. (Default: off)
 *   -i infile   Read maze from infile.                          (Default: stdin)
 *   -o outfile  Write all output to outfile.                    (Default: stdout)
 * 
 * @param isValid: Boolean that represents if output is stdout or stderr
 * @return void: Returns nothing
 */
void usage_options(bool isValid) {
    if (isValid) {
        fprintf(stdout, "Options:\n  -h          Print usage and options list to \
        stdout only.    (Default: off)\n  -d          Pretty-print (display) the \
        maze after reading.  (Default: off)\n  -s          Print length of shorte\
        st path or \'No solution\'. (Default: off)\n  -p          Pretty-print maze\
         with the path, if one exists. (Default: off)\n  -i infile   Read maze fr\
         om infile.                          (Default: stdin)\n  -o outfile  Writ\
         e all output to outfile.                    (Default: stdout)\n");
    }
    else {
        fprintf(stderr, "Usage:\nmopsolver [-hdsp] [-i INFILE] [-o OUTFILE]\n");
    }
}

/**
 * Main function to be called when a mopsolver simulation is run.
 *
 * @param argc: Number of arguments provided in command line (Including file name)
 * @param argv: Array of individual arguments separated by spaces (Including file name)
 * @return int: Returns error code; 0 if EXIT_SUCCESS, 1 if EXIT_FAILURE, or 2
 */
int main(int argc, char *argv[]) {
    // Initialize and default maze information
    char* input_file = NULL;
    char* output_file = NULL;
    FILE *input_file_handle;
    FILE *output_file_handle;

    // Flag information
    bool usage_stdout = false;
    bool pretty_print = false;
    bool print_shortest = false;
    bool pretty_with_path = false;
    
    // Parse command line arguments provided with mopsolver call
    int opt;
    while ((opt = getopt(argc, argv, "hdspi:o:")) != -1) {
        switch (opt) {
            case 'h':
                // Display help commands
                usage_stdout = true;
                usage_help(usage_stdout);
                usage_options(usage_stdout);

                return EXIT_SUCCESS;
                break;
            case 'd':
                // Pretty display mode on
                pretty_print = true;

                break;
            case 's':
                // Print shortest path mode on
                print_shortest = true;

                break;
            case 'p':
                // Pretty print with path mode on
                pretty_with_path = true;

                break;
            case 'i':
                // Take given argument as input file
                input_file = optarg;

                break;
            case 'o':
                // Take given argument as output file
                output_file = optarg;

                break;
        }
    }

    // Create initial MazeInstance
    MazeInstance initial_maze;

    // Check for given input file of maze
    if (input_file != NULL) {
        // Open given input file
        input_file_handle = fopen(input_file, "r");
    }
    else {
        // No valid maze provided, read from standard input and do NOTHING
        input_file_handle = stdin;
    }

    // Initialize maze data given input file FILE
    initial_maze = initialize_maze(input_file_handle);

    // Display information in output file or stdout
    if (output_file != NULL) {
        output_file_handle = fopen(output_file, "w+");
    }
    else {
        output_file_handle = stdout;
    }

    if (pretty_print) {
        pretty_print_maze(output_file_handle, initial_maze);
    }

    // Begin BFS Solving steps

    // 1. Call the solve function from the Solver file to solve
    // Solve function will also handle all displays
    solve(initial_maze, output_file_handle, pretty_with_path, print_shortest);
    
    // Free and destroy maze instance after use
    destroy_maze(initial_maze);
}


