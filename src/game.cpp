#include "game.h"
#include "defs.h"
#include "board.h"
#include <cstring>
#include <chrono>
#include <thread>


bool Game::check_jump(Board *brd, int player,  std::vector<move> *jumplist, int index) {
	move *m = &(jumplist->at(index));
    //std::vector<move>::iterator m = jumplist->begin()+index =1;
    //std::cout << m->move_count ;
	int x = m->path[m->move_count][0];
	int y = m->path[m->move_count][1];
	bool check_jump_ret = false; 
    bool jump_found = false;
    //std::cout << "Piece at "<<  x << " " << y <<  std::endl;
    //std::cout << "in check_jump" << std::endl;
    //check north west
    int nw[] = {x-1, y-1};
    if (can_jump(m->path[m->move_count],nw,brd) && (!(brd->is_red(x,y)) || brd->is_king(x,y))) {
        jump_found = true;
    	move *new_move = new move;
    	std::memcpy(new_move,m ,sizeof(move));    
    	new_move->move_count++;
    	new_move->path[new_move->move_count][0] = x-2;
    	new_move->path[new_move->move_count][1] = y-2;
    	new_move->pieces_taken++;
    	new_move->b = new Board(brd);
    	bool cnt = new_move->b->move_piece(x,y,x-2,y-2);
    	new_move->b->remove_piece(x-1,y-1);

        jumplist->push_back(*new_move);

    	if(!cnt)
            check_jump_ret = check_jump(new_move->b,player,jumplist,jumplist->size()-1);
    }

    int ne[] = {x-1, y+1};
    if (can_jump(m->path[m->move_count],ne,brd) && (!(brd->is_red(x,y)) || brd->is_king(x,y))) {
        jump_found = true;
        //std::cerr << "northeast, ";
    	move *new_move = new move;
    	std::memcpy(new_move,m ,sizeof(move));
    	new_move->move_count++;
    	new_move->path[new_move->move_count][0] = x-2;
    	new_move->path[new_move->move_count][1] = y+2;
    	new_move->pieces_taken++;
    	new_move->b = new Board(brd);
    	bool cnt = new_move->b->move_piece(x,y,x-2,y+2);
    	new_move->b->remove_piece(x-1,y+1);
        jumplist->push_back(*new_move);

    	if(!cnt)
            check_jump_ret = check_jump(new_move->b,player,jumplist,jumplist->size()-1);
    }

    int se[] = {x+1, y+1};
    if (can_jump(m->path[m->move_count], se,brd) && ((brd->is_red(x,y)) || brd->is_king(x,y))){
        jump_found = true;
        //std::cerr << "southeast, ";
    	move *new_move = new move;
    	std::memcpy(new_move,m,sizeof(move));
    	new_move->move_count++;
    	new_move->path[new_move->move_count][0] = x+2;
    	new_move->path[new_move->move_count][1] = y+2;
    	new_move->pieces_taken++;
    	new_move->b= new Board(brd);
    	bool cnt = new_move->b->move_piece(x,y,x+2,y+2);
    	new_move->b->remove_piece(x+1,y+1);
        jumplist->push_back(*new_move);

        if(!cnt)
    	   check_jump_ret = check_jump(new_move->b,player,jumplist,jumplist->size()-1);
    }

    int sw[] = {x+1, y-1};
    if (can_jump(m->path[m->move_count],sw,brd) && ((brd->is_red(x,y)) || brd->is_king(x,y))){
        //std::cerr << "southwest";
        jump_found = true;
    	move *new_move = new move;
    	std::memcpy(new_move,m,sizeof(move));
    	new_move->move_count++;
    	new_move->path[new_move->move_count][0] = x+2;
    	new_move->path[new_move->move_count][1] = y-2;
    	new_move->pieces_taken++;
    	new_move->b = new Board(brd);
    	bool cnt = new_move->b->move_piece(x,y,x+2,y-2);
    	new_move->b->remove_piece(x+1,y-1);
    	if(!cnt)
            check_jump_ret = check_jump(new_move->b,player,jumplist,jumplist->size()-1);
    }
    //std::cerr << std::endl;

    if(jumplist->at(index).move_count == 0 || jump_found){
        //std::cout << "Deleting move with move_count " <<jumplist->at(index).move_count << std::endl; 
    	jumplist->erase(jumplist->begin()+index);
        //std::cout << "No jumps exist from " << x << ", " << y << std::endl;
    }

    if(jump_found)
        return true;
    return false;
}

bool Game::can_jump(int jumper[2], int jumpee[2], Board *brd){
	int x_dir = jumpee[0] - jumper[0];
	int y_dir = jumpee[1] - jumper[1];
	if(!(brd->contains_piece(jumper[0] + (2*x_dir), jumper[1]+ (2*y_dir)))) {
		if(brd->is_red(jumper[0],jumper[1]) != brd->is_red(jumpee[0],jumpee[1]) && brd->contains_piece(jumpee[0],jumpee[1]))
			if(Board::is_valid_pos(jumper[0],jumper[1]) && Board::is_valid_pos(jumpee[0],jumpee[1]) && Board::is_valid_pos(jumper[0] + (2*x_dir), jumper[1]+ (2*y_dir)))
                return true;
	}
	return false;
} 

void Game::possible_jumps(Board *brd, int player, std::vector<move> *jumplist) {
    //std::cout << "in possible_jumps" << std::endl;
    bool redflag = (player == RED) ? true : false;

    for(int x =0; x<8; x++) {
        int y = x%2;
        for(;y <8; y+=2) {
        	if(brd->contains_piece(x,y) && (redflag == brd->is_red(x,y))){
                //std::cout << "found " << ((player == RED) ? "red " : "black ") << "piece at " << x << ", " << y << std::endl;
        		move m;
                for(int i = 0; i < 10; i ++){
                    m.path[i][0] = 0;
                    m.path[i][1] = 0;
                }
        		m.path[0][0] = x;
        		m.path[0][1] = y;
        		m.pieces_taken = 0;
        		m.move_count = 0;
        		jumplist->push_back(m);
        		check_jump(brd,player,jumplist,jumplist->size()-1);
        	}
        }
    }
    //std::cout << "Possible jumps: movelist size: " << jumplist->size() << std::endl;
    int count =0 ;
    for(std::vector<move>::iterator it = jumplist->begin(); it != jumplist->end(); it++){
        if(it->move_count <= 0){
            jumplist->erase(it);
            it--;
            count++;
        }
        else{
            //std::cout << it->move_count << std::endl;
        }
    }
    //std::cout << "Possible jumps: movelist size after removing empty moves: " << jumplist->size() << std::endl;
    //std::cout << "count : " << count << std::endl;
}

void Game::possible_moves(Board *brd, int player, std::vector<move> *movelist){
    //std::cout << "in possible_moves" << std::endl;
    bool redflag = (player ==RED)? true:false;
    for(int x = 0; x < 8; x++){
        int y = x%2;
        for(; y < 8; y+=2){
            //if there is a piece at (x,y) and it belongs to current player
            if((redflag == brd->is_red(x,y)) && brd->contains_piece(x,y)){
                //if position is valid and (piece is black or king)
                if(Board::is_valid_pos(x,y) && (!(brd->is_red(x,y)) || brd->is_king(x,y))){
                	//check ne
                	if(!(brd->contains_piece(x-1,y-1)) && Board::is_valid_pos(x-1,y-1)){
                		move *m = new move;
                		m->move_count = 1;
                		m->path[0][0] = x;
                		m->path[0][1] = y;
                		m->path[1][0] = x-1;
                		m->path[1][1] = y-1;
                		m->pieces_taken = 0;
                        m->b = new Board(brd);
                        m->b->move_piece(x,y,m->path[1][0],m->path[1][1]);
                		movelist->push_back(*m);
                        //std::cout << "found move: " << x <<  " " << y << std::endl;
                	}

                	//check nw
                	if(!(brd->contains_piece(x-1,y+1)) && Board::is_valid_pos(x-1,y+1)){
                		move *m = new move;
                		m->move_count = 1;
                		m->path[0][0] = x;
                		m->path[0][1] = y;
                		m->path[1][0] = x-1;
                		m->path[1][1] = y+1;
                		m->pieces_taken = 0;
                        m->b = new Board(brd);
                        m->b->move_piece(x,y,m->path[1][0],m->path[1][1]);
                        movelist->push_back(*m);
                        //std::cout << "found move: " << x <<  " " << y << std::endl;

                	}
                }
                // if current position is valid and (piece is red or king)
                if (Board::is_valid_pos(x,y) && ( (brd->is_red(x,y)) || brd->is_king(x,y) ) ){
                	if(!(brd->contains_piece(x+1,y-1)) && Board::is_valid_pos(x+1,y-1)){
                		move *m = new move;
                		m->move_count = 1;
                		m->path[0][0] = x;
                		m->path[0][1] = y;
                		m->path[1][0] = x+1;
                		m->path[1][1] = y-1;
                		m->pieces_taken = 0;
                        m->b = new Board(brd);
                        m->b->move_piece(x,y,m->path[1][0],m->path[1][1]);
                        movelist->push_back(*m);
                        //std::cout << "found move: " << x <<  " " << y << std::endl;
                	}
                	if(!(brd->contains_piece(x+1,y+1)) && Board::is_valid_pos(x+1,y+1)){
                		move *m = new move;
                		m->move_count = 1;
                		m->path[0][0] = x;
                		m->path[0][1] = y;
                		m->path[1][0] = x+1;
                		m->path[1][1] = y+1;
                		m->pieces_taken = 0;
                        m->b = new Board(brd);
                        m->b->move_piece(x,y,m->path[1][0],m->path[1][1]);
                        movelist->push_back(*m);
                        //std::cout << "found move: " << x <<  " " << y << std::endl;            	
                    }
                }
            }
        }
    }
}

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
        std::cout << "Movelist size: " << movelist.size() << std::endl;
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
            std::cout << "Searched to depth " << depth << "in " << diff << "seconds" <<std::endl;
        }
    }
    std::cout << "found best move" << std::endl;
    game_board = best_move.b;
    std::cout << "Press enter to continue" << std::endl;
    std::cin.get();
}

