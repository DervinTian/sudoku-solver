#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <cassert>
#include <fstream>
#include <cctype>
#include <bitset>
#include <unordered_set>
#include <unordered_map>

std::string SUDOKU_MAP = "input_sudoku";
int NUM_ROWS = 9;
int NUM_COLS = 9;
int global_counter = 0;

std::vector<std::vector<std::vector<char>>> possible_tbl0_values;
std::vector<std::vector<std::vector<char>>> possible_tbl1_values;
std::vector<std::vector<std::vector<char>>> possible_tbl2_values;
std::vector<std::vector<std::vector<char>>> possible_tbl3_values;
std::vector<std::vector<std::vector<char>>> possible_tbl4_values;
std::vector<std::vector<std::vector<char>>> possible_tbl5_values;
std::vector<std::vector<std::vector<char>>> possible_tbl6_values;
std::vector<std::vector<std::vector<char>>> possible_tbl7_values;
std::vector<std::vector<std::vector<char>>> possible_tbl8_values;

std::vector<std::vector<char>> original_tbl0_values;
std::vector<std::vector<char>> original_tbl1_values;
std::vector<std::vector<char>> original_tbl2_values;
std::vector<std::vector<char>> original_tbl3_values;
std::vector<std::vector<char>> original_tbl4_values;
std::vector<std::vector<char>> original_tbl5_values;
std::vector<std::vector<char>> original_tbl6_values;
std::vector<std::vector<char>> original_tbl7_values;
std::vector<std::vector<char>> original_tbl8_values;

std::vector<std::vector<std::vector<char>>> sudoku_solution;

std::vector<std::vector<std::vector<char>>> read_in_sudoku(){
    std::ifstream in_memory_sudoku(SUDOKU_MAP);

    std::vector<std::vector<std::vector<char>>> result;
    bool new_square = true;
    int base_square_idx = 0;
    int ticker = 0;
    std::string sudoku_line;
    while(std::getline(in_memory_sudoku, sudoku_line)){
        if(new_square){
            std::vector<std::vector<char>> empty_inner_square;
            empty_inner_square.push_back(std::vector<char>{});
            empty_inner_square.push_back(std::vector<char>{});
            empty_inner_square.push_back(std::vector<char>{});
            result.push_back(empty_inner_square);
            result.push_back(empty_inner_square);
            result.push_back(empty_inner_square);
            new_square = false;
        }

        result[base_square_idx + 0][ticker].push_back(sudoku_line[0]);
        result[base_square_idx + 0][ticker].push_back(sudoku_line[1]);
        result[base_square_idx + 0][ticker].push_back(sudoku_line[2]);

        result[base_square_idx + 1][ticker].push_back(sudoku_line[3]);
        result[base_square_idx + 1][ticker].push_back(sudoku_line[4]);
        result[base_square_idx + 1][ticker].push_back(sudoku_line[5]);

        result[base_square_idx + 2][ticker].push_back(sudoku_line[6]);
        result[base_square_idx + 2][ticker].push_back(sudoku_line[7]);
        result[base_square_idx + 2][ticker].push_back(sudoku_line[8]);
        
        ticker = (ticker + 1) % 3;

        if(ticker == 0){
            base_square_idx += 3;
            new_square = true;
        }
    }

    return result;
}

bool check_sudoku_map(const std::vector<std::vector<std::vector<char>>>& sudoku_map){
    bool result = true;

    for(int i = 0; i < sudoku_map.size(); ++i){
        std::unordered_set<char> table_values;
        for(int j = 0; j < sudoku_map[i].size(); ++j){
            for(int k = 0; k < sudoku_map[i][j].size(); ++k){
                table_values.insert(sudoku_map[i][j][k]);
            }
        }

        if(table_values.size() != 9){
            return false;
        }
    }

    int base_table_index = 0;
    for(int i = 0; i < NUM_ROWS; ++i){
        std::unordered_set<char> table_values;
        if(i >= 0 && i < 3){
            base_table_index = 0;
        }
        else if(i >= 3 && i < 6){
            base_table_index = 3;
        }
        else if(i >= 6 && i < 9){
            base_table_index = 6;
        }
        else{
            std::cout << "Too many stuffs\n";
        }

        table_values.insert(sudoku_map[base_table_index + 0][i % 3][0]);
        table_values.insert(sudoku_map[base_table_index + 0][i % 3][1]);
        table_values.insert(sudoku_map[base_table_index + 0][i % 3][2]);

        table_values.insert(sudoku_map[base_table_index + 1][i % 3][0]);
        table_values.insert(sudoku_map[base_table_index + 1][i % 3][1]);
        table_values.insert(sudoku_map[base_table_index + 1][i % 3][2]);

        table_values.insert(sudoku_map[base_table_index + 2][i % 3][0]);
        table_values.insert(sudoku_map[base_table_index + 2][i % 3][1]);
        table_values.insert(sudoku_map[base_table_index + 2][i % 3][2]);

        if(table_values.size() != 9){
            return false;
        }
    }

    for(int i = 0; i < NUM_COLS; ++i){
        std::unordered_set<char> table_values;
        if(i >= 0 && i < 3){
            base_table_index = 0;
        }
        else if(i >= 3 && i < 6){
            base_table_index = 1;
        }
        else if(i >= 6 && i < 9){
            base_table_index = 2;
        }
        else{
            std::cout << "Too many stuffs\n";
        }

        table_values.insert(sudoku_map[base_table_index + 0][0][i % 3]);
        table_values.insert(sudoku_map[base_table_index + 0][1][i % 3]);
        table_values.insert(sudoku_map[base_table_index + 0][2][i % 3]);

        table_values.insert(sudoku_map[base_table_index + 3][0][i % 3]);
        table_values.insert(sudoku_map[base_table_index + 3][1][i % 3]);
        table_values.insert(sudoku_map[base_table_index + 3][2][i % 3]);

        table_values.insert(sudoku_map[base_table_index + 6][0][i % 3]);
        table_values.insert(sudoku_map[base_table_index + 6][1][i % 3]);
        table_values.insert(sudoku_map[base_table_index + 6][2][i % 3]);

        if(table_values.size() != 9){
            return false;
        }
    }


    return true;
}

std::unordered_set<char> get_row_values(int rownum, const std::vector<std::vector<std::vector<char>>>& sudoku_grid){
    std::unordered_set<char> table_values;

    int base_table_index = 0;
    if(rownum >= 0 && rownum < 3){
        base_table_index = 0;
    }
    else if(rownum >= 3 && rownum < 6){
        base_table_index = 3;
    }
    else if(rownum >= 6 && rownum < 9){
        base_table_index = 6;
    }
    else{
        std::cout << "Too many stuffs\n";
    }

    table_values.insert(sudoku_grid[base_table_index + 0][rownum % 3][0]);
    table_values.insert(sudoku_grid[base_table_index + 0][rownum % 3][1]);
    table_values.insert(sudoku_grid[base_table_index + 0][rownum % 3][2]);

    table_values.insert(sudoku_grid[base_table_index + 1][rownum % 3][0]);
    table_values.insert(sudoku_grid[base_table_index + 1][rownum % 3][1]);
    table_values.insert(sudoku_grid[base_table_index + 1][rownum % 3][2]);

    table_values.insert(sudoku_grid[base_table_index + 2][rownum % 3][0]);
    table_values.insert(sudoku_grid[base_table_index + 2][rownum % 3][1]);
    table_values.insert(sudoku_grid[base_table_index + 2][rownum % 3][2]);

    return table_values;
}

std::unordered_set<char> get_col_values(int colnum, const std::vector<std::vector<std::vector<char>>>& sudoku_grid){
    std::unordered_set<char> table_values;
    int base_table_index = 0;

    if(colnum >= 0 && colnum < 3){
        base_table_index = 0;
    }
    else if(colnum >= 3 && colnum < 6){
        base_table_index = 1;
    }
    else if(colnum >= 6 && colnum < 9){
        base_table_index = 2;
    }
    else{
        std::cout << "Too many stuffs\n";
    }

    table_values.insert(sudoku_grid[base_table_index + 0][0][colnum % 3]);
    table_values.insert(sudoku_grid[base_table_index + 0][1][colnum % 3]);
    table_values.insert(sudoku_grid[base_table_index + 0][2][colnum % 3]);

    table_values.insert(sudoku_grid[base_table_index + 3][0][colnum % 3]);
    table_values.insert(sudoku_grid[base_table_index + 3][1][colnum % 3]);
    table_values.insert(sudoku_grid[base_table_index + 3][2][colnum % 3]);

    table_values.insert(sudoku_grid[base_table_index + 6][0][colnum % 3]);
    table_values.insert(sudoku_grid[base_table_index + 6][1][colnum % 3]);
    table_values.insert(sudoku_grid[base_table_index + 6][2][colnum % 3]);

    return table_values;
}

void fill_in_table(std::vector<std::vector<char>>& base_table, std::unordered_map<std::string, std::vector<char>> &tile_values_to_fill_in, int empty_values, int table_num){
    if(empty_values == 1){
        int empty_i = 0;
        int empty_j = 0;
        for(int i = 0; i < base_table.size(); ++i){
            for(int j = 0; j < base_table[i].size(); ++j){
                if(base_table[i][j] == '-'){
                    empty_i = i;
                    empty_j = j;
                }
            }
        }

        int base_row_index = 0;
        int base_col_index = 0;
        if(table_num == 1){
            base_col_index = 3;
        }
        else if(table_num == 2){
            base_col_index = 6;
        }
        else if(table_num == 3){
            base_row_index = 3;
        }
        else if(table_num == 4){
            base_row_index = 3;
            base_col_index = 3;
        }
        else if(table_num == 5){
            base_row_index = 3;
            base_col_index = 6;
        }
        else if(table_num == 6){
            base_row_index = 6;
        }
        else if(table_num == 7){
            base_row_index = 6;
            base_col_index = 3;
        }
        else if(table_num == 8){
            base_row_index = 6;
            base_col_index = 6;
        }
        std::string hash_key = std::to_string(base_row_index + empty_i) + "-" + std::to_string(base_col_index + empty_j);

        std::vector<std::vector<char>> base_table_copy = base_table;

        for(size_t i = 0; i < tile_values_to_fill_in[hash_key].size(); ++i){
            base_table_copy[empty_i][empty_j] = tile_values_to_fill_in[hash_key][i];

            if(table_num == 0){
                possible_tbl0_values.push_back(base_table_copy);
            }
            else if(table_num == 1){
                possible_tbl1_values.push_back(base_table_copy);
            }
            else if(table_num == 2){
                possible_tbl2_values.push_back(base_table_copy);
            }
            else if(table_num == 3){
                possible_tbl3_values.push_back(base_table_copy);
            }
            else if(table_num == 4){
                possible_tbl4_values.push_back(base_table_copy);
            }
            else if(table_num == 5){
                possible_tbl5_values.push_back(base_table_copy);
            }
            else if(table_num == 6){
                possible_tbl6_values.push_back(base_table_copy);
            }
            else if(table_num == 7){
                possible_tbl7_values.push_back(base_table_copy);
            }
            else if(table_num == 8){
                possible_tbl8_values.push_back(base_table_copy);
            }
            else{
                std::cout << "AFDSKJFAOHEUSKJBFZDVZ\n";
            }
        }
    }
    else{
        int empty_i = 0;
        int empty_j = 0;
        for(int i = 0; i < base_table.size(); ++i){
            for(int j = 0; j < base_table[i].size(); ++j){
                if(base_table[i][j] == '-'){
                    empty_i = i;
                    empty_j = j;
                    break;
                }
            }
        }

        int base_row_index = 0;
        int base_col_index = 0;
        if(table_num == 1){
            base_col_index = 3;
        }
        else if(table_num == 2){
            base_col_index = 6;
        }
        else if(table_num == 3){
            base_row_index = 3;
        }
        else if(table_num == 4){
            base_row_index = 3;
            base_col_index = 3;
        }
        else if(table_num == 5){
            base_row_index = 3;
            base_col_index = 6;
        }
        else if(table_num == 6){
            base_row_index = 6;
        }
        else if(table_num == 7){
            base_row_index = 6;
            base_col_index = 3;
        }
        else if(table_num == 8){
            base_row_index = 6;
            base_col_index = 6;
        }

        std::string hash_key = std::to_string(base_row_index + empty_i) + "-" + std::to_string(base_col_index + empty_j);
        for(int x = 0; x < tile_values_to_fill_in[hash_key].size(); ++x){
            std::vector<std::vector<char>> base_table_next = base_table;
            std::unordered_map<std::string, std::vector<char>> tile_values_to_fill_in_next;

            int empty_values_next = empty_values - 1;

            char value_to_fill_in_with = tile_values_to_fill_in[hash_key][x];
            for(auto &pair : tile_values_to_fill_in){
                std::string location = pair.first;

                for(int y = 0; y < tile_values_to_fill_in[location].size(); ++y){
                    if(tile_values_to_fill_in[location][y] != value_to_fill_in_with){
                        tile_values_to_fill_in_next[location].push_back(tile_values_to_fill_in[location][y]);
                    }
                }
            }

            base_table_next[empty_i][empty_j] = value_to_fill_in_with;

            fill_in_table(base_table_next, tile_values_to_fill_in_next, empty_values_next, table_num);
        }
    }
}   

void fill_possible_sudoku_table_values(int table_num, std::vector<std::vector<std::vector<char>>>& sudoku_map){
    std::unordered_set<char> filled_in_values;
    int starting_empty_values = 0;
    std::unordered_map<std::string, std::vector<char>> fill_in_possible_values_per_tile;
    std::unordered_set<char> numbers_1_9;

    std::vector<std::vector<char>> &sudoku_table = sudoku_map[table_num];

    int base_row_index = 0;
    int base_col_index = 0;
    if(table_num == 1){
        base_col_index = 3;
    }
    else if(table_num == 2){
        base_col_index = 6;
    }
    else if(table_num == 3){
        base_row_index = 3;
    }
    else if(table_num == 4){
        base_row_index = 3;
        base_col_index = 3;
    }
    else if(table_num == 5){
        base_row_index = 3;
        base_col_index = 6;
    }
    else if(table_num == 6){
        base_row_index = 6;
    }
    else if(table_num == 7){
        base_row_index = 6;
        base_col_index = 3;
    }
    else if(table_num == 8){
        base_row_index = 6;
        base_col_index = 6;
    }

    
    for(int i = 1; i < 10; ++i){
        numbers_1_9.insert(std::to_string(i)[0]);
    }

    for(int i = 0; i < sudoku_table.size(); ++i){
        for(int j = 0; j < sudoku_table[i].size(); ++j){
            if(sudoku_table[i][j] != '-'){
                filled_in_values.insert(sudoku_table[i][j]);
            }
            else{
                starting_empty_values++;
            }
        }
    }

    for(int i = 0; i < sudoku_table.size(); ++i){
        for(int j = 0; j < sudoku_table[i].size(); ++j){
            if(sudoku_table[i][j] == '-'){
                std::string hash_key;
                hash_key = std::to_string(base_row_index + i) + "-" + std::to_string(base_col_index + j);
                std::vector<char> values_fill_in_for_tile;

                std::unordered_set<char> col_values = get_col_values(base_col_index + j, sudoku_map);
                std::unordered_set<char> row_values = get_row_values(base_row_index + i, sudoku_map);

                for(auto &val : numbers_1_9){
                    if(col_values.find(val) == col_values.end()){
                        if(row_values.find(val) == row_values.end()){
                            if(filled_in_values.find(val) == filled_in_values.end()){
                                values_fill_in_for_tile.push_back(val);
                            }
                        }
                    }
                }

                fill_in_possible_values_per_tile[hash_key] = values_fill_in_for_tile;
            }
        }
    }

    fill_in_table(sudoku_table, fill_in_possible_values_per_tile, starting_empty_values, table_num);

}

void print_out_sudoku_grid(const std::vector<std::vector<std::vector<char>>>& sudoku_grid){
    int base_table_index = 0;
    for(int i = 0; i < NUM_ROWS; ++i){

        if (i % 3 == 0) {
            std::cout << "+-----+-----+-----+\n";
        }
        
        if(i >= 0 && i < 3){
            base_table_index = 0;
        }
        else if(i >= 3 && i < 6){
            base_table_index = 3;
        }
        else if(i >= 6 && i < 9){
            base_table_index = 6;
        }
        else{
            std::cout << "Too many stuffs\n";
        }

        std::cout << "| ";

        std::cout << (sudoku_grid[base_table_index + 0][i % 3][0]);
        std::cout << (sudoku_grid[base_table_index + 0][i % 3][1]);
        std::cout << (sudoku_grid[base_table_index + 0][i % 3][2]);

        std::cout << " | ";

        std::cout << (sudoku_grid[base_table_index + 1][i % 3][0]);
        std::cout << (sudoku_grid[base_table_index + 1][i % 3][1]);
        std::cout << (sudoku_grid[base_table_index + 1][i % 3][2]);

        std::cout << " | ";

        std::cout << (sudoku_grid[base_table_index + 2][i % 3][0]);
        std::cout << (sudoku_grid[base_table_index + 2][i % 3][1]);
        std::cout << (sudoku_grid[base_table_index + 2][i % 3][2]);

        std::cout << " | ";

        std::cout << std::endl;
    }
    std::cout << "+-----+-----+-----+\n";
}

bool insert_and_check_for_dupes(std::unordered_set<char>& table_values, char value_to_insert){
    if(value_to_insert == '-'){
        return false;
    }

    if(table_values.find(value_to_insert) == table_values.end()){
        table_values.insert(value_to_insert);
        return false;
    }
    else{
        return true;
    }
}   

bool valid_prune(const std::vector<std::vector<std::vector<char>>>& sudoku_grid){
    int base_table_index = 0;
    for(int i = 0; i < NUM_ROWS; ++i){
        std::unordered_set<char> table_values;
        if(i >= 0 && i < 3){
            base_table_index = 0;
        }
        else if(i >= 3 && i < 6){
            base_table_index = 3;
        }
        else if(i >= 6 && i < 9){
            base_table_index = 6;
        }
        else{
            std::cout << "Too many stuffs\n";
        }

        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 0][i % 3][0])){
            return false;
        }
        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 0][i % 3][1])){
            return false;
        }
        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 0][i % 3][2])){
            return false;
        }

        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 1][i % 3][0])){
            return false;
        }
        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 1][i % 3][1])){
            return false;
        }
        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 1][i % 3][2])){
            return false;
        }

        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 2][i % 3][0])){
            return false;
        }
        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 2][i % 3][1])){
            return false;
        }
        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 2][i % 3][2])){
            return false;
        }

    }

    for(int i = 0; i < NUM_COLS; ++i){
        std::unordered_set<char> table_values;
        if(i >= 0 && i < 3){
            base_table_index = 0;
        }
        else if(i >= 3 && i < 6){
            base_table_index = 1;
        }
        else if(i >= 6 && i < 9){
            base_table_index = 2;
        }
        else{
            std::cout << "Too many stuffs\n";
        }

        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 0][0][i % 3])){
            return false;
        }
        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 0][1][i % 3])){
            return false;
        }
        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 0][2][i % 3])){
            return false;
        }

        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 3][0][i % 3])){
            return false;
        }
        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 3][1][i % 3])){
            return false;
        }
        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 3][2][i % 3])){
            return false;
        }

        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 6][0][i % 3])){
            return false;
        }
        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 6][1][i % 3])){
            return false;
        }
        if(insert_and_check_for_dupes(table_values, sudoku_grid[base_table_index + 6][2][i % 3])){
            return false;
        }

    }

    return true;
}


void recursively_solve_sudoku(std::vector<std::vector<std::vector<char>>>& base_table, std::vector<int>& tables_to_be_filled_in, int empty_values){
    if(empty_values == 1){
        std::unordered_map<int, std::vector<std::vector<std::vector<char>>>> potential_tables;
        potential_tables[0] = possible_tbl0_values;
        potential_tables[1] = possible_tbl1_values;
        potential_tables[2] = possible_tbl2_values;
        potential_tables[3] = possible_tbl3_values;
        potential_tables[4] = possible_tbl4_values;
        potential_tables[5] = possible_tbl5_values;
        potential_tables[6] = possible_tbl6_values;
        potential_tables[7] = possible_tbl7_values;
        potential_tables[8] = possible_tbl8_values;

        int big_num = 1;
        for(int i = 0; i < potential_tables.size(); ++i){
            big_num = big_num * potential_tables[i].size();
        }

        assert(tables_to_be_filled_in.size() == 1);

        int table_left_to_fill = tables_to_be_filled_in[0];

        for(int i = 0; i < potential_tables[table_left_to_fill].size(); ++i){
            std::vector<std::vector<std::vector<char>>> base_table_copy = base_table;
            std::vector<std::vector<char>> pot_table = potential_tables[table_left_to_fill][i];

            base_table_copy[table_left_to_fill] = pot_table;

            if(check_sudoku_map(base_table_copy)){
                sudoku_solution = base_table_copy;
                std::cout << "Solved!\n";
                print_out_sudoku_grid(base_table_copy);
                exit(0);
            }
        }
    }
    else{

        std::unordered_map<int, std::vector<std::vector<std::vector<char>>>> potential_tables;
        potential_tables[0] = possible_tbl0_values;
        potential_tables[1] = possible_tbl1_values;
        potential_tables[2] = possible_tbl2_values;
        potential_tables[3] = possible_tbl3_values;
        potential_tables[4] = possible_tbl4_values;
        potential_tables[5] = possible_tbl5_values;
        potential_tables[6] = possible_tbl6_values;
        potential_tables[7] = possible_tbl7_values;
        potential_tables[8] = possible_tbl8_values;

        for(int i = 0; i < tables_to_be_filled_in.size(); ++i){
            int next_table_to_fill_in = tables_to_be_filled_in[i];
            int next_empty_values = empty_values - 1;
            std::vector<int> tables_to_be_filled_in_next;
            for(int x = 0; x < tables_to_be_filled_in.size(); ++x){
                if(tables_to_be_filled_in[x] != next_table_to_fill_in){
                    tables_to_be_filled_in_next.push_back(tables_to_be_filled_in[x]);
                }
            }

            for(int j = 0; j < potential_tables[next_table_to_fill_in].size(); ++j){
                std::vector<std::vector<std::vector<char>>> base_table_copy = base_table;
                std::vector<std::vector<char>> pot_table = potential_tables[next_table_to_fill_in][j];

                base_table_copy[next_table_to_fill_in] = pot_table;

                if(valid_prune(base_table_copy)){
                    recursively_solve_sudoku(base_table_copy, tables_to_be_filled_in_next, next_empty_values);
                }

            }
        }
    }
}

void find_sudoku_solution(std::vector<std::vector<std::vector<char>>> &base_sudoku_table){
    std::vector<int> tables_still_needed_to_fill_in;
    std::vector<std::vector<std::vector<char>>> base_table;
    int initl_empty_values = 0;

    std::unordered_map<int, std::vector<std::vector<std::vector<char>>>> potential_tables;
    potential_tables[0] = possible_tbl0_values;
    potential_tables[1] = possible_tbl1_values;
    potential_tables[2] = possible_tbl2_values;
    potential_tables[3] = possible_tbl3_values;
    potential_tables[4] = possible_tbl4_values;
    potential_tables[5] = possible_tbl5_values;
    potential_tables[6] = possible_tbl6_values;
    potential_tables[7] = possible_tbl7_values;
    potential_tables[8] = possible_tbl8_values;

    std::unordered_map<int, std::vector<std::vector<char>>> original_tables;
    original_tables[0] = original_tbl0_values;
    original_tables[1] = original_tbl1_values;
    original_tables[2] = original_tbl2_values;
    original_tables[3] = original_tbl3_values;
    original_tables[4] = original_tbl4_values;
    original_tables[5] = original_tbl5_values;
    original_tables[6] = original_tbl6_values;
    original_tables[7] = original_tbl7_values;
    original_tables[8] = original_tbl8_values;

    for(int i = 0; i < NUM_ROWS; ++i){
        if(potential_tables[i].size() != 0){
            tables_still_needed_to_fill_in.push_back(i);
            initl_empty_values++;
        }
    }

    recursively_solve_sudoku(base_sudoku_table, tables_still_needed_to_fill_in, initl_empty_values);

}

