#ifndef GAME_H_
#define GAME_H_


#ifndef RED_PLAYER
#define RED_PLAYER 1
#endif

#ifndef BLK_PLAYER
#define BLK_PLAYER 1
#endif

#include <ctime>

class Game{
    Board current_board;
    int max_depth;
    int max_time;
    int current_depth;
    bool gameOver;

    time_t start_time;
    time_t end_time;

    void display();
    int alpha_beta(int current_player, int alpha, int beta, int depth, bool &max_depth);

    
}


#endif
