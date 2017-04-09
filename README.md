# Graphs experiments
Some basic graph algorithms implemented in C++ 11.
Most of this algorithm can be find int the book of __Robert Sedgewick__.

## Compilation steps
Open a command prompt in the root of the project and type the following commnands

```
mkdir build
cd build
cmake ../
make
```
This assumes that you have *cmake* installed in your system and that you compiler support the C++11 standard.

### Graph types
#### UnweightedWraph
This data structure represent an unweighted directional graph with a simple API
 ```
 ulong V(); // number of vertex
 ulong E(); // number of edges
 AdjList adj(int v); //outer edges from vertex v
 void addEdge(int v, int w); // add an edge v -> w
 ```
### Contributors
* Miguel Carvajal: mcarvajal@inbox.ru
