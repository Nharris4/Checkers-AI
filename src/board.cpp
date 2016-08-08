//board.cpp
//ECE 469 AI

#include "board.h"
#include "defs.h"
#include <limits>
#include <vector>
#include <cstdint>
#include <cstring>

//using namespace std;
int Board::clean_board [][8]= {
        {1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,2,0,2,0,2,0,2},
        {2,0,2,0,2,0,2,0},
        {0,2,0,2,0,2,0,2}
    };

 int get_other_player(int player){
 	return (player == RED) ? BLK : RED;
 }

bool Board::can_king(int prev_x, int prev_y, int new_x, int new_y){
	if (prev_x > 4 && contains_piece(prev_x,prev_y) && is_red(prev_x,prev_y) && new_x == 7)
		return true;
	if (prev_x < 4 && contains_piece(prev_x,prev_y) && !is_red(prev_x,prev_y) && new_x == 0)
		return true;
	return false;

}

void Board::king_me(int x, int y){
	board_array[x][y]+=2;
}

// return true if piece is true
bool Board::is_king(int loc_x, int loc_y){
	//cerr << this->board_array[loc_x][loc_y];
	if (is_valid_pos(loc_x,loc_y))
		return (this->board_array[loc_x][loc_y] > 2) ? true : false;
	else return false;
}


// return true if piece exists
bool Board::contains_piece(int loc_x,int loc_y){
	if (is_valid_pos(loc_x,loc_y))
		return (this->board_array[loc_x][loc_y] > 0) ? true : false;
	else return false;
}
// return true if piece exists and is red, else return false
bool Board::is_red(int loc_x, int loc_y){
	if (is_valid_pos(loc_x,loc_y))
		return (this->board_array[loc_x][loc_y] % 2) ? true : false;
	else return false;
}


// Print board to screen
void Board::display(void){
	int loc_x = 0;
	int loc_y = 0;

	// Row loop
	std::cout << cls << std::endl;
	std::cout << "         1         2         3          4         5         6         7         8" <<std::endl;
	for(loc_x = 0; loc_x < 8; loc_x++){
		bool even_row = ((loc_x % 2) & 0x01);
		bool red;
		if (even_row)
			red = true;
		else
			red = false;
		
		// Column Loop
		for(int i  = 0; i < 4; i++){
			if(i == 2){
				char a = 'A';
				std::cout << " " <<(char)(a+loc_x) <<  "  ";
			}
			else std::cout << "    ";
			for(loc_y = 0; loc_y < 8; loc_y++){		

			// Each square takes 10h x 4v characters on screen	
				switch(i){
					case 1:
					case 2:
						// Middle two rows
						if (this->contains_piece(loc_x,loc_y)){
							
							std::string current_piece;
							if (is_king(loc_x,loc_y))
								current_piece = piece_king;
							else
								current_piece = piece;
							if(this->is_red(loc_x,loc_y))
								std::cout << bg_white << square_half << bg_red << current_piece << bg_white << square_half;
							else 
								std::cout << bg_white << square_half << bg_black << current_piece << bg_white << square_half;								
						}
						// No piece at current location
						else{
							if (red)
								std::cout << bg_red << square_full;
							else
								std::cout << bg_white << square_full;	
						}

						break;

					case 0:
					case 3:
					default:
						// Outer two rows 
						if (red)
							std::cout << bg_red << square_full;
						else
							std::cout << bg_white << square_full;
						break;
				}
				red = !red;
			}
			std::cout << rst << std::endl;
		}
		
	}
}

int Board::iterative_deepening(int max_player, std::vector<move> *movelist, move &best_move, bool &trigger){
	int depth = 1;		// next depth, to be passed to alpha beta
	int finished = 0;	// depth finished, to be returned 
	move m;
	std::cout << "In iterative deepening" << std::endl;
	bool hit_max_depth;
	while(!trigger){
		hit_max_depth = start_alpha_beta(depth, max_player, movelist, m, trigger);
		if(!trigger){
			best_move = m;
			finished = depth;
		}

		if(!hit_max_depth)
			trigger = true;

		depth+=2;
	}
	return finished;

}

bool Board::start_alpha_beta(int depth, int max_player,std::vector<move> *movelist,move &best_move, bool &trigger){
	int64_t alpha = std::numeric_limits<int64_t>::min();
	int64_t beta  = std::numeric_limits<int64_t>::max();
	int64_t best  = std::numeric_limits<int64_t>::min();

	bool hit_max_depth = false;

	for(std::vector<move>::iterator it = movelist->begin(); it != movelist->end(); it++){
		//std::cout << "THIS(start_alpha_beta): " << it->b << std::endl;
		int64_t v = it->b->alpha_beta(depth-1, alpha, beta, max_player, (max_player == RED) ? BLK : RED, trigger, hit_max_depth);
		if( v > best){
			best = v;
			alpha = v;
			best_move = *(it);
		}
		if (beta <= alpha)
			break;
	}

	return hit_max_depth;
}

int64_t Board::alpha_beta(int depth, int64_t alpha, int64_t beta, int max_player, int curr_player, bool &trigger, bool &hit_max_depth){
	if(trigger)
		return 0;

	if(depth == 0){
		hit_max_depth =true;
		return evaluate(max_player);
	}

	std::vector<move> movelist_ab; 

	get_moves(curr_player, &movelist_ab);

	if(movelist_ab.size() == 0){
		if(curr_player == max_player)
			return std::numeric_limits<int64_t>::lowest();
		return std::numeric_limits<int64_t>::max();
	}

	if (curr_player == max_player){
		for( auto move : movelist_ab) {
			int64_t v = move.b->alpha_beta(depth-1,alpha,beta,max_player,get_other_player(curr_player),trigger,hit_max_depth);
			alpha = std::max(alpha,v);
			if(beta <= alpha)
				break;
		}
		return alpha;
	}
	else {
		for(auto move : movelist_ab) {
			int64_t v = move.b->alpha_beta(depth-1,alpha,beta,max_player,get_other_player(curr_player),trigger,hit_max_depth);
			beta = std::min(beta,v);
			if(beta<= alpha)
				break;
		}

		return beta;
	}

	return 0;
}

int64_t Board::evaluate(int max_player){
    int64_t value = 0;

    const int king_weight = 5;
    const int base_weight = 2;
    int red_base_pieces[8] = {0};
    int black_base_pieces[8] = {0};

    int red_kings = 0, black_kings = 0, red_pawns = 0, black_pawns = 0;
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            if(contains_piece(x,y)){
                if(is_red(x,y)){
                    if(is_king(x,y))
                        red_kings++;
                    else{
                     red_pawns++;
                     red_base_pieces[x]++;
                    }
                }
                else {
                    if(is_king(x,y))
                        black_kings++;
                    else{ 
                        black_pawns++;
                        black_base_pieces[x]++;
                    }
                }
            }
        }
    }
    // score based on piece count
    value += (king_weight * (red_kings - black_kings) + base_weight * (red_pawns - black_pawns)) * 1e6;
    
    // score based on how many pieces are close to being kinged 
    int64_t temp = 0;

    // weight home row heavily so the AI prefers not to move them
    temp += (red_base_pieces[0] - black_base_pieces[7]) * 30;
    temp += (red_base_pieces[1] - black_base_pieces[6]) * 5;
    
    for(int x = 2; x < 7; x++){
        temp += red_base_pieces[x] * x;
        temp -= black_base_pieces[7-x] * x;
    }

    value += temp * 1e2;

    //score based on # of pieces
    value += (red_kings + red_pawns - black_kings - black_pawns) * 1e4;

    value += rand() % 1000;
    return ((max_player == RED ) ? value : -value);
}

void Board::get_moves(int player, std::vector<move> *movelist){

	possible_jumps(player,movelist);
	if (movelist->size() == 0)
		possible_moves(player,movelist);
}


bool Board::check_jump(int player,  std::vector<move> *jumplist, int index) {
	move *m = &(jumplist->at(index));
	int x = m->path[m->move_count][0];
	int y = m->path[m->move_count][1];
	bool check_jump_ret = false; 
    bool jump_found = false;

    //check north west
    int nw[] = {x-1, y-1};
    if (can_jump(m->path[m->move_count],nw) && (!(is_red(x,y)) || is_king(x,y))) {
        jump_found = true;
    	move *new_move = new move;
    	std::memcpy(new_move,m ,sizeof(move));

    	new_move->move_count++;
    	new_move->path[new_move->move_count][0] = x-2;
    	new_move->path[new_move->move_count][1] = y-2;
    	new_move->pieces_taken++;
    	new_move->b = new Board(this);

    	bool cnt = new_move->b->move_piece(x,y,x-2,y-2);
    	new_move->b->remove_piece(x-1,y-1);
    	jumplist->push_back(*new_move);

    	if(!cnt)
            check_jump_ret = new_move->b->check_jump(player,jumplist,jumplist->size()-1);
    }

    int ne[] = {x-1, y+1};
    if (can_jump(m->path[m->move_count],ne) && (!(is_red(x,y)) || is_king(x,y))) {
        jump_found = true;
        //std::cerr << "northeast, ";
    	move *new_move = new move;
    	std::memcpy(new_move,m ,sizeof(move));
    	new_move->move_count++;
    	new_move->path[new_move->move_count][0] = x-2;
    	new_move->path[new_move->move_count][1] = y+2;
    	new_move->pieces_taken++;
    	new_move->b = new Board(this);
    	bool cnt = new_move->b->move_piece(x,y,x-2,y+2);
    	new_move->b->remove_piece(x-1,y+1);

    	jumplist->push_back(*new_move);

    	if(!cnt)
            check_jump_ret = new_move->b->check_jump(player,jumplist,jumplist->size()-1);
    }

    int se[] = {x+1, y+1};
    if (can_jump(m->path[m->move_count], se) && ((is_red(x,y)) || is_king(x,y))){
        jump_found = true;
        //std::cerr << "southeast, ";
    	move *new_move = new move;
    	std::memcpy(new_move,m,sizeof(move));
    	new_move->move_count++;
    	new_move->path[new_move->move_count][0] = x+2;
    	new_move->path[new_move->move_count][1] = y+2;
    	new_move->pieces_taken++;
    	new_move->b = new Board(this);
    	bool cnt = new_move->b->move_piece(x,y,x+2,y+2);
    	new_move->b->remove_piece(x+1,y+1);
    	jumplist->push_back(*new_move);
        if(!cnt)
    	   check_jump_ret = new_move->b->check_jump(player,jumplist,jumplist->size()-1);
    }

    int sw[] = {x+1, y-1};
    if (can_jump(m->path[m->move_count],sw) && ((is_red(x,y)) || is_king(x,y))){
        //std::cerr << "southwest";
        jump_found = true;
    	move *new_move = new move;
    	std::memcpy(new_move,m,sizeof(move));
    	new_move->move_count++;
    	new_move->path[new_move->move_count][0] = x+2;
    	new_move->path[new_move->move_count][1] = y-2;
    	new_move->pieces_taken++;
    	new_move->b = new Board(this);
    	bool cnt = new_move->b->move_piece(x,y,x+2,y-2);
    	new_move->b->remove_piece(x+1,y-1);
        jumplist->push_back(*new_move);

    	if(!cnt)
            check_jump_ret = new_move->b->check_jump(player,jumplist,jumplist->size()-1);
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

bool Board::can_jump(int jumper[2], int jumpee[2]){
	int x_dir = jumpee[0] - jumper[0];
	int y_dir = jumpee[1] - jumper[1];
	if(!(contains_piece(jumper[0] + (2*x_dir), jumper[1]+ (2*y_dir)))) {
		if(is_red(jumper[0],jumper[1]) != is_red(jumpee[0],jumpee[1]) && contains_piece(jumpee[0],jumpee[1]))
			if(is_valid_pos(jumper[0],jumper[1]) && is_valid_pos(jumpee[0],jumpee[1]) && is_valid_pos(jumper[0] + (2*x_dir), jumper[1]+ (2*y_dir)))
                return true;
	}
	return false;
} 

void Board::possible_jumps(int player, std::vector<move> *jumplist) {
    //std::cout << "in possible_jumps" << std::endl;
    bool redflag = (player == RED) ? true : false;

    for(int x =0; x<8; x++) {
        int y = x%2;
        for(;y <8; y+=2) {
        	if(contains_piece(x,y) && (redflag == is_red(x,y))){
                //std::cout << "found " << ((player == RED) ? "red " : "black ") << "piece at " << x << ", " << y << std::endl;
        		move *m = new move;
                for(int i = 0; i < 10; i ++){
                    m->path[i][0] = 0;
                    m->path[i][1] = 0;
                }
        		m->path[0][0] = x;
        		m->path[0][1] = y;
        		m->pieces_taken = 0;
        		m->move_count = 0;
                jumplist->push_back(*m);
                check_jump(player,jumplist,jumplist->size()-1);
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

void Board::possible_moves(int player, std::vector<move> *movelist){
    //std::cout << "in possible_moves" << std::endl;
    bool redflag = (player ==RED)? true:false;
    for(int x = 0; x < 8; x++){
        int y = x%2;
        for(; y < 8; y+=2){
            //if there is a piece at (x,y) and it belongs to current player
            if((redflag == is_red(x,y)) && contains_piece(x,y)){
                //if position is valid and (piece is black or king)
                if(is_valid_pos(x,y) && (!(is_red(x,y)) || is_king(x,y))){
                	//check ne
                	if(!(contains_piece(x-1,y-1)) && is_valid_pos(x-1,y-1)){
                		move *m = new move;
                		m->move_count = 1;
                		m->path[0][0] = x;
                		m->path[0][1] = y;
                		m->path[1][0] = x-1;
                		m->path[1][1] = y-1;
                		m->pieces_taken = 0;
                		m->b = new Board(this);
                		m->b->move_piece(x,y,x-1,y-1);
                		movelist->push_back(*m);
                        //std::cout << "found move: " << x <<  " " << y << std::endl;
                	}

                	//check nw
                	if(!(contains_piece(x-1,y+1)) && is_valid_pos(x-1,y+1)){
                		move *m = new move;
                		m->move_count = 1;
                		m->path[0][0] = x;
                		m->path[0][1] = y;
                		m->path[1][0] = x-1;
                		m->path[1][1] = y+1;
                		m->pieces_taken = 0;
                		m->b = new Board(this);
                		m->b->move_piece(x,y,x-1,y+1);
                        movelist->push_back(*m);
                        //std::cout << "found move: " << x <<  " " << y << std::endl;

                	}
                }
                // if current position is valid and (piece is red or king)
                if (is_valid_pos(x,y) && ( (is_red(x,y)) || is_king(x,y) ) ){
                	if(!(contains_piece(x+1,y-1)) && is_valid_pos(x+1,y-1)){
                		move *m = new move;
                		m->move_count = 1;
                		m->path[0][0] = x;
                		m->path[0][1] = y;
                		m->path[1][0] = x+1;
                		m->path[1][1] = y-1;
                		m->pieces_taken = 0;
                		m->b = new Board(this);
                		m->b->move_piece(x,y,x+1,y-1);
                        movelist->push_back(*m);

                        //std::cout << "found move: " << x <<  " " << y << std::endl;
                	}
                	if(!(contains_piece(x+1,y+1)) && is_valid_pos(x+1,y+1)){
                		move *m = new move;
                		m->move_count = 1;
                		m->path[0][0] = x;
                		m->path[0][1] = y;
                		m->path[1][0] = x+1;
                		m->path[1][1] = y+1;
                		m->pieces_taken = 0;
                		m->b = new Board(this);
                		m->b->move_piece(x,y,x+1,y+1);
                        movelist->push_back(*m);
                        //std::cout << "found move: " << x <<  " " << y << std::endl;            	
                    }
                }
            }
        }
    }
}
