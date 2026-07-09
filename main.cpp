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
    std::vector<std::vector<std::vector<char>>> sudoku_map = read_in_sudoku();

    // fill_possible_sudoku_table_values(0, sudoku_map);

    // std::unordered_set<char> col_values = get_col_values(1, sudoku_map);

    // for(auto &x : col_values){
    //     std::cout << x << std::endl;
    // }
    
    // std::cout << std::endl;
    // std::unordered_set<char> row_values = get_row_values(1, sudoku_map);

    // for(auto &x : row_values){
    //     std::cout << x << std::endl;
    // }

    // if(valid_prune(sudoku_map)){
    //     std::cout << "No dupes!\n";
    // }
    // else{
    //     std::cout << "Dupes!\n";
    // }

    // original_tbl0_values = sudoku_map[0];
    // original_tbl1_values = sudoku_map[1];
    // original_tbl2_values = sudoku_map[2];
    // original_tbl3_values = sudoku_map[3];
    // original_tbl4_values = sudoku_map[4];
    // original_tbl5_values = sudoku_map[5];
    // original_tbl6_values = sudoku_map[6];
    // original_tbl7_values = sudoku_map[7];
    // original_tbl8_values = sudoku_map[8];

    for(int i = 0; i < sudoku_map.size(); ++i){
        fill_possible_sudoku_table_values(i, sudoku_map);
    }

    // fill_possible_sudoku_table_values(0, sudoku_map);

    std::cout << possible_tbl0_values.size() << std::endl;
    std::cout << possible_tbl1_values.size() << std::endl;
    std::cout << possible_tbl2_values.size() << std::endl;
    std::cout << possible_tbl3_values.size() << std::endl;
    std::cout << possible_tbl4_values.size() << std::endl;
    std::cout << possible_tbl5_values.size() << std::endl;
    std::cout << possible_tbl6_values.size() << std::endl;
    std::cout << possible_tbl7_values.size() << std::endl;
    std::cout << possible_tbl8_values.size() << std::endl;

    std::cout << "Solving...\n";
    find_sudoku_solution(sudoku_map);
}   