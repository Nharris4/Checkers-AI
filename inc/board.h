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

    bool can_king(int prev_x, int prev_y, int new_x, int new_y);

    void king_me(int x, int y);

    public:

    int board_array[8][8];

    Board(int new_board[8][8]){
        std::copy(&new_board[0][0], &new_board[0][0] + 8*8, &(this->board_array[0][0]));
    }

    Board(Board *brd){
        for(int x = 0; x < 8; x++){
            for(int y = 0; y < 8; y++){
                this->board_array[x][y] = brd->board_array[x][y];
            }
        }

    }

    Board() : Board(clean_board) {}

    ~Board();
    
    // returns true if the position (i,j) is within the board
    static bool is_valid_pos(int i, int j){
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

    void move_piece(int orig_x, int orig_y, int new_x, int new_y){
        int piece = board_array[orig_x][orig_y];
        board_array[orig_x][orig_y] = 0;
        board_array[new_x][new_y] = piece;
    }

    void remove_piece(int x, int y){
        board_array[x][y] = 0;
    }
};

#endif
