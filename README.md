### Sudoku Solver ###

## Motivation ##

This is my first attempt at creating a computer program that is designed to solve traditional 3x3 Sudoku puzzles.
I was inspired by my lack of ability to solve sudoku while on a train. The only entertainment that I really had was 
my laptop as well as a newspaper article provided by the train. The train had a sudoku puzzle at the back that I saw as
a potential problem-solving exercise, not by pen-and-paper, but through C++.

## Approach ##

The current approach is still quite simple, meaning that the performance is reliable, but slow. It is able to find the solution, but can sometimes take extremely long amounts of time. The current approach is a recursive brute force strategy with heavy pruning to try and reduce the runtime. 

The goal is for every square, to find all the different possible combinations that could work for each square, and then 
recursively generate different combinations of each one of those squares, pruning any invalid permutations away. Each 
potentially valid sudoku solution is then checked until we find a valid solution.

## Usage ##

To use the sudoku solver, the only thing that needs to be done is to input in the starting sudoku grid in `input_sudoku`.
Go through row by row in the sudoku grid and type in the numbers. For any blanks, use the '-' character to represent it.

For example, a sudoku grid like this:

```cpp
+-----+-----+-----+
| --- | --8 | --9 | 
| 2-- | 97- | 5-- | 
| -7- | 64- | -28 | 
+-----+-----+-----+
| -9- | --- | -5- | 
| 85- | -1- | -34 | 
| -4- | --- | -1- | 
+-----+-----+-----+
| 91- | 386 | -7- | 
| --6 | -54 | --3 | 
| 3-- | 1-- | --- | 
+-----+-----+-----+
```

Should be inputted into `input_sudoku` as:

```cpp
-----8--9
2--97-5--
-7-64--28
-9-----5-
85--1--34
-4-----1-
91-386-7-
--6-54--3
3--1-----
```

Once that is done, just execute `main` in order to run the script.

```bash
./main
```

Running the command above generates the following solution:

```cpp
+-----+-----+-----+
| 431 | 528 | 769 | 
| 268 | 973 | 541 | 
| 579 | 641 | 328 | 
+-----+-----+-----+
| 193 | 462 | 857 | 
| 852 | 719 | 634 | 
| 647 | 835 | 912 | 
+-----+-----+-----+
| 914 | 386 | 275 | 
| 786 | 254 | 193 | 
| 325 | 197 | 486 | 
+-----+-----+-----+
```