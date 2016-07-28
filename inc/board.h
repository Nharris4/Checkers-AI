#ifndef BOARD_H_
#define BOARD_H_

//#include <cctype>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

class Board{
    private:
    static int clean_board[8][8]; 
    public:

    int board_array[][8];

    Board(int new_board[8][8]){
        std::copy(&new_board[0][0], &new_board[0][0] + 8*8, &board_array[0][0]);
    }
    Board() : Board(clean_board) {}

    ~Board();
    
    // returns true if the position (i,j) is within the board
    bool is_valid_pos(int i, int j){
        if(i >=0 && i < 8 && j >=0 && j < 8)
            if(i % 2){
                if(j % 2)
                    return true;
            }
            else{
                if(!(j % 2))
                    return true;
            }
        else
            return false;
        return false;
    }

    void display(void);

    bool contains_piece(int x, int y);

    bool is_king(int x, int y);

    bool is_red(int x, int y);
};

#endif
