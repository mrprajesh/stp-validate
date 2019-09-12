# stp-validate
Steiner Tree Problem's validation module written in C++.

### STP and notations.
- **Input:** `G(V,E,W,L)` where $W:E → Z^+ $ and L is terminals.
- **Output:** `T(V',E',W)` such that V'⊇ L.

### Modules

- [ ] Check sum of edges cost = Steiner tree cost
- [ ] Is the edges printed is a valid edge in G
- [ ] Is all terminals present?
- [ ] is T connected?
- [ ] is T a tree?
- [ ] is the above 3 conditions for valid Steiner Tree.

### Input and output
This IO format follows the standard [DIMACS](http://dimacs11.zib.de/downloads.html#stpg) format / [PACE challenge](https://pacechallenge.org/2018/steiner-tree/#appendix-a-graph-format) format 
or even SteinLib's [format](http://steinlib.zib.de/format.php). 

The sample input as from PACE

```
SECTION Graph
Nodes 5
Edges 6
E 1 2 1
E 1 4 3
E 3 2 3
E 2 4 4
E 3 5 10
E 4 5 1
END

SECTION Terminals
Terminals 2
T 2
T 4
END

EOF
```

The Sample Output is follows:
```
VALUE 20
1 3
3 5
7 3
10 7
7 22
```

The `20` is the size/cost of the Steiner tree and followed by edges -- one edge per line. The order of edges, and order of vertex in an edge should not matter.

### Author
[Rajesh Pandian M](http://mrprajesh.github.io)

### Feedback
If you see any mistake/logical error in the code. Please feel free to raise an [issue](https://github.com/mrprajesh/stp-validate/issues/new).
