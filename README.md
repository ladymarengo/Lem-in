# Lem-in

Team project with [jheiskan](https://github.com/jmtuulos) in Hive Helsinki school. During working on this project we explored graph theory, learned about maximum flow problem, implemented breadth-first-search, merge sort, binary search, dynamically reallocating arrays and, most importantly, practiced pair-programming and improved our team-working soft skills.

The main goal of this project is to transfer given number of ants through the complex graph (simulating an ant farm) in the least amount of turns. You can read all requirements [here](https://github.com/ladymarengo/Lem-in/blob/main/Subject.pdf).

For the main part of the solution we used Edmonds–Karp algorithm with our modifications for handling nodes capacity. For more detailed explanations you can check comments in the source files.

As a bonus we created [Beautymapper](https://github.com/jmtuulos/Lem-in-beautymapper) tool for updating maps coordinates and Visualizer for demonstration (and mostly for fun!). Both tools are written in Rust.

https://user-images.githubusercontent.com/43127337/184603307-5ecb78e7-dfaa-4c25-abc2-99792cb77ea8.mov

## Usage
```make``` to compile.

```./lem-in < map_name``` or ```./lem-in -file map_name``` to run with given map.

```./test.sh --generator-option``` to run a script that will use a generator with given option (ex. ```--big-superposition```), run lem-in executable with result map and print required and final amount of lines. The script will repeat the process 10 times. Green OK indicates no difference or better than required result, yellow is for 1-2 extra lines and red KO for 3+ extra lines.

```./lem-in -help``` to see the list of available flags.

```./visualize.sh number-of-iterations(optional)``` to run the visualizer. It will create a map, update it with the beautymapper (with given number of iterations or 150 as default), run lem-in executable with '-paths' flag and run the visualizer with final result.
