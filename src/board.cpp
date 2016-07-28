//board.cpp
//ECE 469 AI

#include "../inc/board.h"
#include "../inc/colors.h"

using namespace std;

int Board::clean_board [][8]= {
        {1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1}
    };


bool Board::is_king(int loc_x, int loc_y){
	return (board_array[loc_x][loc_y] > 2) ? true : false;
}

bool Board::contains_piece(int loc_x,int loc_y){
	return (board_array[loc_x][loc_y] > 0)? true : false;
}

bool Board::is_red(int loc_x, int loc_y){
	return (board_array[loc_x][loc_y] % 2) ? true : false;
}



void Board::display(void){
	cerr << "BOARD.CPP: in Board::Display()" << endl;
	int loc_x = 0;
	int loc_y = 0;

	// Row loop
	for(loc_x = 0; loc_x < 8; loc_x++){
		//cerr << "BOARD.CPP: in x loop" << endl;
		bool even_row = !((loc_x % 2) & 0x01);
		bool red;
		if (even_row)
			red = true;
		else
			red = false;
		
		// Column Loop
		for(loc_y = 0; loc_y < 8; loc_y++){		
			//cerr << "BOARD.CPP: in y loop" << endl;

			// Each square takes 10h x 4v characters on screen	
			for(int i  = 0; i < 4; i++){
				cerr << "BOARD.CPP: in square loop" << endl;

				switch(i){
					case 1:
					case 2:
						// Middle two rows
						if (this->contains_piece(loc_x,loc_y)){
							
							string current_piece;
							if (is_king(loc_x,loc_y))
								current_piece = piece_king;
							else
								current_piece = piece;
							cerr << "HELLO!" << endl;
							if(this->is_red(loc_x,loc_y)){
								if(red){
									cout << bg_red << square_half << bg_yellow << current_piece << bg_red << square_half;
								}
								else{
									cout << bg_black << square_half << bg_red << current_piece << bg_black << square_half;
								}
							}
							else {
								if(red){
									cout << bg_red << square_half << bg_yellow << current_piece << bg_red << square_half;
								}
								else{
									cout << bg_black << square_half << bg_red << current_piece << bg_black << square_half;
								}

							}
						}
						// No piece at current location
						else{
							if (red)
								cout << bg_red << square_full;
							else
								cout << bg_black << square_full;	
						}

						break;

					case 0:
					case 3:
					default:
						// Outer two rows 
						if (red)
							cout << bg_red << square_full;
						else
							cout << bg_black << square_full;
						break;
				}
			}
			red = !red;

		}
	}


}