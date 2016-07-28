#ifndef GAME_H_
#define GAME_H_

#include "../inc/board.h"
#include <ctime>
#include <string>


class Game{
    private:
    Board *game_board = nullptr;
    int max_depth;
    int max_time;
    int current_depth;
    bool gameOver;

    int player_1;
    int player_2;

    time_t start_time;
    time_t end_time;

    public:
    Game(int player_1, int player_2){
    	this->player_1 = player_1;
    	this->player_2 = player_2;
    }
    int alpha_beta(int current_player, int alpha, int beta, int depth, bool &max_depth);

    int get_max_depth() { return max_depth;}

    void set_max_depth(int new_depth) { max_depth = new_depth;}

    int get_max_time() { return max_time;}

    void set_max_time(int new_time) {  max_time = new_time;}

    bool create_board(std::string savefile_name = ""){
    	if (savefile_name == "") {
    		std::ifstream boardfile(savefile_name);
    		if (boardfile.is_open()){
    			game_board = new Board();
    			return true;
    		}
    	}
    	return false;
    }

    Board* get_game_board(){ return game_board; }
};



#endif
