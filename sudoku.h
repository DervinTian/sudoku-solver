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

// Delcare some globals that we will be using 
extern std::string SUDOKU_MAP;
extern int NUM_ROWS;
extern int NUM_COLS;

// Below holds a vector of all the possible different combinations for each of the different "tables", a 3x3 subset of the sudoku grid
extern std::vector<std::vector<std::vector<char>>> possible_tbl0_values;
extern std::vector<std::vector<std::vector<char>>> possible_tbl1_values;
extern std::vector<std::vector<std::vector<char>>> possible_tbl2_values;
extern std::vector<std::vector<std::vector<char>>> possible_tbl3_values;
extern std::vector<std::vector<std::vector<char>>> possible_tbl4_values;
extern std::vector<std::vector<std::vector<char>>> possible_tbl5_values;
extern std::vector<std::vector<std::vector<char>>> possible_tbl6_values;
extern std::vector<std::vector<std::vector<char>>> possible_tbl7_values;
extern std::vector<std::vector<std::vector<char>>> possible_tbl8_values;
extern std::vector<std::vector<std::vector<char>>> sudoku_solution;

// Global variable used for debugging
extern int global_counter;

// Functions to be used later
std::vector<std::vector<std::vector<char>>> read_in_sudoku();
std::unordered_set<char> get_row_values(int rownum, const std::vector<std::vector<std::vector<char>>>& sudoku_grid);
std::unordered_set<char> get_col_values(int colnum, const std::vector<std::vector<std::vector<char>>>& sudoku_grid);
void print_out_sudoku_grid(const std::vector<std::vector<std::vector<char>>>& sudoku_grid);
bool check_sudoku_map(const std::vector<std::vector<std::vector<char>>>& sudoku_map);
void fill_possible_sudoku_table_values(int table_num, std::vector<std::vector<std::vector<char>>>& sudoku_map);
bool valid_prune(const std::vector<std::vector<std::vector<char>>>& sudoku_grid);
void find_sudoku_solution(std::vector<std::vector<std::vector<char>>> &base_sudoku_table);
