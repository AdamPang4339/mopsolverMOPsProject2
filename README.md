# mopsolverMOPsProject2
A Breadth First Search algorithm maze solver simulation that uses the ncurses C library to display solutions and information.

## Project Files
- **MopSolver:** Main driver file that simulates the solving mechanics of a given maze and displays information related to mazes given an entrance at the top left of the maze (0, 0), and with an exit at the bottom right of the maze (N - 1, M - 1).
- Coordinates: Defines coordinate pair data structure with functions with getter and setter functions. Contains vital getNeighbors function specific to mopsolver for retrieving open pathed neighbor coordinates.
- Solver: Implements a Breadth First Search algorithm to find the shortest path within a given maze configuration. 
- QueueADT: Abstract Data Structure that allows use of a regular queue structure in C.
- Maze: Implements functions and main maze struct that holds information on all coordinates within a particular maze grid.
- Structs.h: Header file to export all main typedef structs being used in mopsolver simulations

## Command Line Usage
`Usage:\nmopsolver [-hdsp] [-i INFILE] [-o OUTFILE]`
```
Options:
  -h          Print usage and options list to stdout only.    (Default: off)
  -d          Pretty-print (display) the maze after reading.  (Default: off)
  -s          Print length of shortest path or 'No solution'. (Default: off)
  -p          Pretty-print maze with the path, if one exists. (Default: off)
  -i infile   Read maze from infile.                          (Default: stdin)
  -o outfile  Write all output to outfile.                    (Default: stdout)
```
