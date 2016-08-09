#include "game.h"
#include "defs.h"
#include "board.h"
#include <cstring>
#include <chrono>
#include <thread>




void timer(bool *trigger, float search_time){
    const float slack = 0.1; // set trigger 100ms before search_time
    std::cout << "Starting timer! " << std::endl;
    int count = 0;
    auto start_time = std::chrono::high_resolution_clock::now();
    while(!(*trigger)){
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        auto end_time = std::chrono::high_resolution_clock::now();
        auto diff_time = 1e-3 * std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        if( diff_time > (search_time - slack)){
            *trigger = true;
            std::cout << "timer expired!" << std::endl;
        }
        count = count +1;
    }
}

void print_move(move m){
    for(int i = 0; i <= m.move_count; i++){
        std::cout << (char)(m.path[i][0] + 'A') << (m.path[i][1] + 1);
        if(i != m.move_count)
            std::cout << " ->";
    }
    std::cout << std::endl;

}

void Game::AI_turn(){
    std::vector<move> movelist;
    move best_move;
    game_board->get_moves(current_player,&movelist);
    std::cout<< "Got moves" << std::endl;
    if(movelist.size() == 1){
        std::cout << "Only one move to be made." << std::endl;
        best_move = movelist.front();
    }
    else if(movelist.size() == 0){
        std::cout << "No moves available." << std::endl;
        int black_pieces = game_board->get_black_pieces();
        int red_pieces = game_board->get_red_pieces();
        if( black_pieces == 0){
            std::cout << "Red player wins!" << std::endl;
            exit(0);
        }
        if ( red_pieces == 0){
            std::cout << "Black player wins!" << std::endl;
            exit(0);
        }
    }
    else {
        //std::cout << "Movelist size: " << movelist.size() << std::endl;
        bool timer_trigger = false;
        std::thread timer_thread(timer, &timer_trigger, max_time);
        auto start_time = std::chrono::high_resolution_clock::now();
        
        int depth = game_board->iterative_deepening(current_player,&movelist,best_move,timer_trigger);
        
        auto end_time = std::chrono::high_resolution_clock::now();
        auto diff = 1e-3 * std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        timer_thread.join();

        if (depth == 0 ){
            std::cout << "AI wasn't able to search the root depth in the allocated time" << std::endl;
            best_move = movelist.at(rand() % movelist.size());
        }
        else {
            std::cout << "Searched to depth " << depth << "in " << diff << " seconds" <<std::endl;
        }
    }
    std::cout << "found best move" << std::endl;
    print_move(best_move);
    game_board = best_move.b;
    std::cout << "Press enter to continue" << std::endl;
    std::cin.get();
}

