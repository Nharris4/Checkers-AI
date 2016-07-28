//board.cpp
//ECE 469 AI

#include "../inc/board.h"
#include "../inc/colors.h"

using namespace std;

Board::clean_board = {
        {1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,1,0,1,0,1,0,1},
        {1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1}
    };

Board::Board(int[][] new_board){
	if (sizeof(new_board) < sizeof(int) * 8 * 8){

	}
	else {
		board_array = new_board 
	}

}
Board::is_king(int loc_x, int loc_y){
	return (board_array[loc_x][loc_y] > 2) ? true : false;
}

Board::contains_piece(int loc_x,int loc_y){
	return (board_array[loc_x][loc_y] > 0)? true : false;
}

Board::is_red(int loc_x, int loc_y){
	return (board_array[loc_x][loc_y] % 2) ? true : false;
}



Board::display(void){
	int loc_x = 0;
	int loc_y = 0;

	// Row loop
	for(loc_x = 0; loc_x < 8; loc_x++){
		
		bool even_row = !((loc_x % 2) & 0x01);
		bool red;
		if (even_row)
			red = true;
		else
			red = false;
		
		// Column Loop
		for(loc_y = 0; loc_y < 8; loc_y++){		
			// Each square takes 10h x 4v characters on screen	
			for(int i  = 0; i < 4; i++){
				switch(i){
					case 1:
					case 2:
						// Middle two rows
						if (self.contains_piece(loc_x,loc_y)){
							if(self.is_red(loc_x,loc_y)){
								if(red)
									cout << bg_red << square_half << bg_yellow <<< is_king(loc_x,loc_y) ? piece_king : piece << bg_red << square_half;
								else
									cout << bg_black << square_half << bg_red <<< is_king(loc_x,loc_y) ? piece_king : piece << bg_black << square_half;
							}
							else {
								if(red)
									cout << bg_red << square_half << bg_yellow <<< is_king(loc_x,loc_y) ? piece_king : piece << bg_red << square_half;
								else
									cout << bg_black << square_half << bg_red <<< is_king(loc_x,loc_y) ? piece_king : piece << bg_black << square_half;

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
			red = !red

		}
	}


}