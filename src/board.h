#ifndef BOARD_H_
#define BOARD_H_

//#include <cctype>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include "main.h"

class board{
    char board_array[8][4];
    
    char current_player;

    board();
    ~board();
    
    void end_turn(){
        if(current_player == RED)
            current_player = BLK;
        else if (current_player == BLK)
            current_player= RED;
        else{
            cerr << "board.h: Invalid player state! current_player: "<< current_player << endl;
            exit(1);
        }
    }
    // returns true if the position (i,j) is within the board
    bool is_valid_pos(int i, int j){
    if(i >=0 && i < 8 && j >=0 && j < 4)
        return true;
    else return false;
    }

    void set_board(int[][] new_board){
        board_array = new_board;
    }

    void display();
}

#endif
