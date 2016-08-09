#ifndef BOARD_H_
#define BOARD_H_

//#include <cctype>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include "defs.h"
#include <cstdint>

class Board;

typedef struct move {
    int path[10][2];
    int pieces_taken;
    int move_count;
    Board *b;
} move;


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

    ~Board(){}
    
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

    //moves piece from orig_x,orig_y to new_x,new_y.
    //if piece can be turned into king, it is kinged and move_piece returns true.  else returns false.
    bool move_piece(int orig_x, int orig_y, int new_x, int new_y){
        bool king;
        if(can_king(orig_x,orig_y,new_x,new_y))
            king = true;
        else king = false;
        int piece = board_array[orig_x][orig_y];
        board_array[orig_x][orig_y] = 0;
        board_array[new_x][new_y] = piece;
        if(king)
            king_me(new_x,new_y);
        return king;
    }

    void remove_piece(int x, int y){
        board_array[x][y] = 0;
    }

    int get_red_pieces(void) {
        int red_pieces = 0;
        for(int x = 0; x< 8; x++)
            for(int y = 0; y<8; y++)
                if(is_valid_pos(x,y) && contains_piece(x,y) && is_red(x,y))
                    red_pieces++;

        return red_pieces;
    }

    int get_black_pieces(void) {
        int black_pieces = 0;
        for(int x = 0; x< 8; x++)
            for(int y = 0; y<8; y++)
                if(is_valid_pos(x,y) && contains_piece(x,y) && (!is_red(x,y)))
                    black_pieces++;

        return black_pieces;
    }

    int iterative_deepening(int minmax_player, std::vector<move> *movelist, move &best_move, bool &trigger);
    bool start_alpha_beta(int depth, int max_player, std::vector<move> *movelist, move &best_move, bool &trigger);
    int64_t alpha_beta(int depth,int64_t alpha, int64_t beta, int max_player, int , bool &trigger, bool &hit_max_depth);
    int64_t evaluate(int max_player);

    void get_moves(int curr_player, std::vector<move> *movelist_ab);
    void possible_jumps(int player, std::vector<move> *jumplist);
    void possible_moves(int player, std::vector<move> *jumplist);
    bool check_jump(int player,  std::vector<move> *jumplist, int index);
    bool can_jump(int *a ,int *b);


};

#endif
