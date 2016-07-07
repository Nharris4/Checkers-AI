/*
* main.cpp
* Venkat Kuruturi
* ECE469 Artificial Intelligence
*/

#include "main.h"

using namespace std;

void read_board(ifstream* boardfile){
    cout << "To be implemented!" << endl;
}

void start_game(int red_player, int black_player, int time){
    cout << "To be implemented!" << endl;
}

int getnum(void){
    int x = 0;
    bool loop = true;

    while(loop){
        string s;
        getline(cin, s);
        stringstream stream(s);
        
        if(stream >> x){
            loop = false;
            continue; 
        }

        cout << "Invalid input! Please input a number!" << endl;
    }

    return x;
}
int main(int argc, char** argv){
    cout << "Checkers" << endl;
    cout << endl;
    cout << endl;
    
    int red_player,black_player,time;
    int game_mode,load;
    while(1){
        cout << "Please select an option (1-3):" << endl;
        cout << "1. Play as Red" << endl;
        cout << "2. Play as Black" << endl;
        cout << "3. AI vs AI" << endl;
        game_mode = 0;
        game_mode = getnum();
        if(game_mode < 1 || game_mode > 3)
            cout << "Invalid input!  Please select again!" << endl;
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
    cout << endl << endl;
    while(1){
        cout << "Please select an option (1-2):" << endl;
        cout << "1. Load a new game" << endl;
        cout << "2. Load game from file" << endl;
        int load;
        load = getnum();
        if(load <1 || load > 2)
            cout << "Invalid iniput! Please select again!" << endl;
        else break;
    }
    
    cout << endl << endl;
    if(load == 1)
        read_board(nullptr);
    while(load == 2){
        cout << "Enter the location of the board file: ";
        string filename;
        cin >> filename;
        cout << endl;
        ifstream boardfile(filename);
        
        if(boardfile.is_open()){
            read_board(&boardfile);
            break;
        }
        else{
            cout << "Unable to open file! Please make sure the file is valid" << endl;
        }
    }
    while(load == 2){
        cout << "Enter time for AI (3-60 in seconds): ";
        time = getnum();
        if(time <3 || time > 60)
            cout << "Invalid input! Please try again!" << endl << endl;
        else
            break;
    }
    system("Color 1A"); 
    cout << "test";
    start_game(red_player, black_player,time);
}
