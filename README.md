# FDF

An over-engineered ray casting engine. 

![42](/.github/42.png)

### Maps

Maps are described in a 2D-grid format, one scalar for every vertex of the grid, describing its height.

For exemple, to do a flat square with the top right corner rising up, you would do 

```text
0 0 1 2 3 4 5 6 7 8 9
0 0 0 1 2 3 4 5 6 7 8
0 0 0 0 1 2 3 4 5 6 7
0 0 0 0 0 1 2 3 4 5 6
0 0 0 0 0 0 1 2 3 4 5
0 0 0 0 0 0 0 1 2 3 4
0 0 0 0 0 0 0 0 1 2 3
0 0 0 0 0 0 0 0 0 1 2
0 0 0 0 0 0 0 0 0 0 1
```

### Build

You will need to install [libmlx](https://projects.intra.42.fr/uploads/document/document/7/sources.tgz). After that:

* `make` to compile the whole project.
* `fdf ./my_map.txt` to run it.

### Controls

* `W` `A` `S` `D` to rotate around the origin.
* `I` `J` `K` `L` to shift the camera 1 unit to the the top/left/right/bottom, conserving the same angle.
* `U` `O` to move 1 unit toward/away the origin.

### Screenshot 

![france](/.github/france.png)

### Grade

FDF was originally a school project at 42. It was graded **125/100**.
