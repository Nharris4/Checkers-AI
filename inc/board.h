#ifndef BOARD_H_
#define BOARD_H_

//#include <cctype>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <cstdint>

class Board{
    private:
    static const int clean_board[8][8]; 
    public:

    uint8_t board_array[8][8];

   Board() : Board(clean_board) {}

    ~Board();

    Board(int new_board[8][8]);
    
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
