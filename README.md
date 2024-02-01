# Graph Algorithms

In this project implemented several basic algorithms on graphs. Graphs are one of the basic data structures in programming that are used everywhere. Graphs can be used, for example, to interpret road maps, electrical circuits, geographic maps, for communication between people in social networks, and many other things.


## Table of Contents

+ [Description](#description)
    + [Graph.h library](#implementation-of-the-s21_graphh-library)
    + [Graph_algorithms.h library](#implementation-of-the-s21_graph_algorithmsh-library)
    + [Ant Colony Algorithm](#ant-colony-algorithm)
    + [Comparison of methods for solving the traveling salesman problem](#comparison-of-methods-for-solving-the-traveling-salesman-problem)
    + [Console Interface](#console-interface)
+ [Getting Started](#getting-started)
    + [Dependenses](#dependencies)
    + [Installing](#installing)
    + [Usage](#usage)
+ [Authors](#authors)
+ [License](#license)

## Description

### Graph.h library:

- The library developed in C++ language of C++17 standard
- The code is written following Google style
- The library must be represented as a `Graph` class that stores information about the graph using an *adjacency matrix**. The dimensionality of the adjacency matrix should be set dynamically when initializing the graph (when loading it from a file)
- The program built with Makefile which contains standard set of targets for GNU-programs: all, clean, test, s21_graph.a
- Full coverage of the `Graph` class methods with unit-tests
- The class `Graph` contains the following public methods:
    - `LoadGraphFromFile(string filename)` - loading a graph from a file in the adjacency matrix format
    - `ExportGraphToDot(string filename)`- exporting a graph to a dot file

### Graph_algorithms.h library:

- The library developed in C++ language of C++17 standard
- The code is written following Google style
- The library represented as a ` GraphAlgorithms ` class that stores the implementation of algorithms on                                                                      
- Full coverage of the `GraphAlgorithms` class methods with unit-tests
- s21_graph_algorithms contains the following public methods:
    - `DepthFirstSearch(Graph &graph, int start_vertex)` - a *non-recursive* depth-first search in the graph from a given vertex. The function return an array that contains the traversed vertices in the order they were traversed.
    - `BreadthFirstSearch(Graph &graph, int start_vertex)` - breadth-first search in the graph from a given vertex. TYhe function should return an array that contains the traversed vertices in the order they were traversed.
    - `GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2)` - searching for the shortest path between two vertices in a graph using *Dijkstra's algorithm*. The function accepts as input the numbers of two vertices and returns a numerical result equal to the smallest distance between them.
    - `GetShortestPathsBetweenAllVertices(Graph &graph)` - searching for the shortest paths between all pairs of vertices in a graph using the *Floyd-Warshall algorithm*. As a result, the function returns the matrix of the shortest paths between all vertices of the graph.
    - `GetLeastSpanningTree(Graph &graph)` - searching for the minimal spanning tree in a graph using *Prim's algorithm*. As a result, the function return the adjacency matrix for the minimal spanning tree.

### Ant Colony Algorithm

- `SolveTravelingSalesmanProblem(Graph &graph)` - solving the traveling salesman's problem using the *ant colony algorithm*. This algorithm find the shortest path that goes through all vertices of the graph at least once, followed by a return to the original vertex. As a result, the function return the `TsmResult` structure described below:
    ```cpp
    struct TsmResult {
        std::vector<int> vertices;  // an array with the route you are looking for (with the vertex traverse order).
        double distance;  // the length of this route
    }
    ```
    >*If it is impossible to solve the problem with a given graph, output an error.*


### Comparison of methods for solving the traveling salesman problem

- It is necessary to choose two additional algorithms to solve the traveling salesman problem and implement them as methods of the `GraphAlgorithms` class
- To perform a comparison of speed of the three algorithms
    - Ant Colony Algorithm
    - Monte Carlo Method
    - Dynamic Programming Method
- The study starts for a graph that was previously loaded from a file.
- As part of the study to keep track of the time it took to solve the salesman's problem `N` times in a row, by each of the algorithms. Where `N` is set from the keyboard.
- The results of the time measurement displayed in the console.
    >*Example:* For `N = 100` it will measure how long it will take to solve the traveling salesman problem 100 times for the current given graph.

### Console interface

* The main program - is a console application for testing the functionality of the implemented graph.h and graph_algorithms.h libraries 
* The console interface provide the following functionality:
    1. loading the original graph from a file
    2. graph traversal in breadth with output of the result to the console   
    3. graph traversal in depth with output of the result to the console
    4. searching for the shortest path between any two vertices and displaying the result to the console
    5. searching for the shortest paths between all pairs of vertices in the graph with the output of the resulting matrix to the console
    6. searching for the minimal spanning tree in the graph with the output of the resulting adjacency matrix to the console
    7. solving the salesman problem with the output of the resulting route and its length to the console
    8. exporting graph to *.dot file
    9. comparison of methods for solving *traveling salesman problem*
    10. exit the program



## Getting Started

### Dependencies

- MacOS or Linux
- C++17 compiler

### Installing

To build and install this project, please follow the instructions below:
1. Clone this repository to your local machine.
2. Open a terminal and navigate to the project directory.
3. Run: `make install`.
4. This command will compile the source code and create an executable file named "consoleapp".
### Usage

- Run the `consoleapp` application

## Authors

- [Sergey Sinitsyn](https://github.com/SergSinitsyn) (aka Bernarda Verla): Ant Colony Algorithm, Monte Carlo Method
- [Sergey Gorbatenko](https://github.com/sg41) (aka Joelle Bonza):
- [Aleksandr Didenko](https://github.com/quincshe) (aka Quinc Sherley):

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details.

© 2023 SergSinitsyn