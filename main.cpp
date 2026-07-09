#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <filesystem>
#include <fstream>
#include <cctype>
#include <bitset>
#include <unordered_set>
#include <unordered_map>

#include "sudoku.h"

// compile cmd: g++ -g -std=c++20 sudoku.cpp main.cpp -o main

int main(){

    // Read in the input sudoku grid from the file
    std::vector<std::vector<std::vector<char>>> sudoku_map = read_in_sudoku();

    // Recursively find all the different possible ways to rearrage each "table" in sudoku
    for(int i = 0; i < sudoku_map.size(); ++i){
        fill_possible_sudoku_table_values(i, sudoku_map);
    }

    // Print out the number of different possible permutations
    std::cout << "Sifting through " << possible_tbl0_values.size() * 
                                        possible_tbl1_values.size() * 
                                        possible_tbl2_values.size() * 
                                        possible_tbl3_values.size() *
                                        possible_tbl4_values.size() *
                                        possible_tbl5_values.size() *
                                        possible_tbl6_values.size() *
                                        possible_tbl7_values.size() *
                                        possible_tbl8_values.size() << " permutations\n";

    // Print out the expected time to take, using the reference that a solution for 15,000,000 permutations took 1 minute to solve                               
    std::cout << "Expected to take " << (possible_tbl0_values.size() * 
                                        possible_tbl1_values.size() * 
                                        possible_tbl2_values.size() * 
                                        possible_tbl3_values.size() *
                                        possible_tbl4_values.size() *
                                        possible_tbl5_values.size() *
                                        possible_tbl6_values.size() *
                                        possible_tbl7_values.size() *
                                        possible_tbl8_values.size()) / 15000000 << " minutes\n";
    std::cout << "Solving...\n";

    // Recursively match the different tables to find the solution
    find_sudoku_solution(sudoku_map);
}   