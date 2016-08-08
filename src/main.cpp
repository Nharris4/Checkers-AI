/*
* main.cpp
* Venkat Kuruturi
* ECE469 Artificial Intelligence
*/

#include "main.h"
#include "defs.h"
void display_moves(std::vector<move> *movelist){
    int count = 0;
    for(std::vector<move>::iterator it = movelist->begin(); it!= movelist->end(); it++){
        count++;
        std::cout << "(" << count << ") ";
        for(int i = 0; i <= it->move_count; i++){
            std::cout << (char)(it->path[i][0] + 'A') << (it->path[i][1]+1);
            if(i != it->move_count)
                std::cout << " -> ";
        }
        std::cout << std::endl;
    }
}

int getnum(void){
    int x = 0;
    bool loop = true;

    while(loop){
        std::string s;
        std::getline(std::cin, s);
        std::stringstream stream(s);
        
        if(stream >> x){
            loop = false;
            continue; 
        }

        std::cout << "Invalid input! Please input a number!" << std::endl;
    }

    return x;
}

void make_move(int move_choice, std::vector<move> *movelist){
    move m = movelist->at(move_choice -1);
    if (m.pieces_taken > 0){
        for(int i = 0; i < m.pieces_taken; i++){
            current_game->get_game_board()->move_piece(m.path[i][0],m.path[i][1],m.path[i+1][0],m.path[i+1][1]);
            current_game->get_game_board()->remove_piece( (m.path[i][0] + m.path[i+1][0])/2, (m.path[i][1] + m.path[i+1][1])/2);
        }
    }
    else {
        current_game->get_game_board()->move_piece(m.path[0][0],m.path[0][1],m.path[1][0],m.path[1][1]);
    }
}

void start_game(int red_player, int black_player){
    while(!current_game->check_game_over()){
        int current_player = current_game->get_current_player();
        (current_game->get_game_board())->display();
        std::cout << "Current player : "  << ((current_player == RED) ? " Red." : " Black.") << std::endl;
        if(((current_player == RED) ? red_player : black_player) != AI ){
            // HUMAN PLAYER
            
            std::vector<move> movelist;
            current_game->get_moves(current_player,&movelist);
            bool loop = true;
            int move_choice;
            if (movelist.size() == 0){
                loop = false;
                int red_pieces = current_game->get_game_board()->get_red_pieces();
                int black_pieces = current_game->get_game_board()->get_black_pieces();
                if(red_pieces == 0){
                    std::cout << "Black player wins!" << std::endl;
                    current_game->gameOver = true;
                    exit(0);
                }
                if(black_pieces == 0){
                    std::cout << "Red player wins!" << std::endl;
                    current_game->gameOver = true;
                    exit(0);
                }
            }
            if(!loop){
                std::cout << "No moves can be made! Skipping turn." << std::endl;
                current_game->switch_players();
            }
            while(loop){
                display_moves(&movelist);
                std::cout << "Select move: ";
                move_choice = getnum();
                if(move_choice <1 || move_choice > movelist.size()){
                    std::cout << "Invalid input! Try again." << std::endl;
                    loop = true;
                }
                else loop = false;
            }

            make_move(move_choice, &movelist);
            current_game->switch_players();
        }
        else {
            // AI PLAYER
            std::cout << "AI is thinking..." << std::endl;
            current_game->AI_turn();
            current_game->switch_players();
        }

    }
}

int main(int argc, char** argv){
    std::cout << "Checkers" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    
    int red_player,black_player,time;
    int game_mode,load;
    
    // Select game mode
    while(1){
        std::cout << "Please select an option (1-3):" << std::endl;
        std::cout << "1. Play as Red" << std::endl;
        std::cout << "2. Play as Black" << std::endl;
        std::cout << "3. AI vs AI" << std::endl;
        game_mode = 0;
        game_mode = getnum();
        if(game_mode < 1 || game_mode > 3)
            std::cout << "Invalid input!  Please select again!" << std::endl;
        else break;
    }
    if (game_mode == 1){
        red_player = HUMAN;
        black_player = AI;
    }
    else if (game_mode == 2){
        red_player = AI;
        black_player = HUMAN;
    }
    else{
        red_player = AI;
        black_player = AI;
    }
    std::cout << std::endl << std::endl;
    

    while(1){
        std::cout << "Please select an option (1-2):" << std::endl;
        std::cout << "1. Load a new game" << std::endl;
        std::cout << "2. Load game from file" << std::endl;
        load = getnum();
        if(load <1 || load > 2)
            std::cout << "Invalid input! Please select again!" << std::endl;
        else break;
    }
    
    current_game = new Game(red_player,black_player);
    std::cout << std::endl << std::endl;

    // load save file
    if (load == 1){
        std::cout << "Loading new game\n";
        current_game->set_current_player(RED);
        if(current_game->create_board())
            std::cerr << "No savefile specified. Loaded new game." << std::endl;
        else {
            std::cerr << "Error creating new game! Exiting." << std::endl;
            exit(1);
        }
    }

    while(load == 2){
        std::cout << "Enter the location of the board file: ";
        std::string filename;
        std::cin >> filename;
        std::cout << std::endl;        
        
        if (current_game->create_board(filename.c_str())){
            std::cout << "File loaded." << std::endl;
            break;
        }
        else{
            std::cout << "Unable to open file! Please make sure the file is valid" << std::endl;
        }
    }

    while(load == 1){
        std::cout << "Enter time for AI (3-60 in seconds): ";
        time = getnum();
        if(time <3 || time > 60)
            std::cout << "Invalid input! Please try again!" << std::endl << std::endl;
        else{
            current_game->set_max_time(time);
            break;
        }
    }



    start_game(red_player, black_player);
}
