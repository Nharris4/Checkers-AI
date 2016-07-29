#ifndef GAME_H_
#define GAME_H_

#include "../inc/board.h"
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>


class Game{
    private:
    int max_depth;
    int max_time;
    int current_depth;
    bool gameOver;

    int player_1;           // AI flag
    int player_2;           // AI flag
    int current_player;

    time_t start_time;
    time_t end_time;

    public:

    Board *game_board;

    Game(int player_1, int player_2){
    	this->player_1 = player_1;
    	this->player_2 = player_2;
        this->current_player = 1;
    }
    
    int alpha_beta(int current_player, int alpha, int beta, int depth, bool &max_depth);

    int get_max_depth() { return max_depth;}

    void set_max_depth(int new_depth) { max_depth = new_depth;}

    int get_max_time() { return max_time;}

    void set_max_time(int new_time) { max_time = new_time; }

    bool create_board(const char* savefile_name = nullptr){
    	int new_board[8][8] = { {0} };
        if (savefile_name == nullptr) {
    		std::cerr << "No filename given.using default board" << std::endl;
    		game_board = new Board();
    		return true;
    		
    	}
        else {
            std::ifstream savefile(savefile_name);
            if (savefile.is_open()){
                std::cerr << "Opened file." << std::endl;
                // read file and import game
                int offset = 0;
                for(int i = 0; i < 8; i++){
                    for(int j = 0; j < 8; j+=2){
                        savefile >> new_board[i][j+offset];
                    }
                    offset = (offset + 1) % 2;
                }

                savefile >> this->current_player;
                savefile >> this->max_time;
            }
            else {
                std::cout << "Unable to open file!" << std::endl;
            }
            game_board = new Board(new_board);
            return true;
        }
    	return false;
    }

    Board* get_game_board(){ return game_board; }
};



#endif
