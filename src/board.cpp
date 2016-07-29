//board.cpp
//ECE 469 AI

#include "board.h"
#include "colors.h"

using namespace std;

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
		return (this->board_array[loc_x][loc_y] > 0)? true : false;
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
	for(loc_x = 0; loc_x < 8; loc_x++){
		bool even_row = ((loc_x % 2) & 0x01);
		bool red;
		if (even_row)
			red = true;
		else
			red = false;
		
		// Column Loop
		for(int i  = 0; i < 4; i++){
			
			for(loc_y = 0; loc_y < 8; loc_y++){		

			// Each square takes 10h x 4v characters on screen	
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
							if(this->is_red(loc_x,loc_y))
								cout << bg_white << square_half << bg_red << current_piece << bg_white << square_half;
							else 
								cout << bg_white << square_half << bg_black << current_piece << bg_white << square_half;								
						}
						// No piece at current location
						else{
							if (red)
								cout << bg_red << square_full;
							else
								cout << bg_white << square_full;	
						}

						break;

					case 0:
					case 3:
					default:
						// Outer two rows 
						if (red)
							cout << bg_red << square_full;
						else
							cout << bg_white << square_full;
						break;
				}
				red = !red;
			}
			cout << rst << endl;
		}
		
	}


}