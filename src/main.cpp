/*
* main.cpp
* Venkat Kuruturi
* ECE469 Artificial Intelligence
*/


public static void main(String args[]){
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
        cin >> game_mode;
        if(game_mode < 1 || game_mode > 3)
            cout << "Invalid input!  Please select again!" << endl;
        else break;
    }
    if (game_mode == 1){
        red_player = HUMAN;
        black_player = AI;
    }
    else if (game_mode = 2){
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
        cin >> load;
        if(load <1 || load > 2)
            cout << "Invalid iniput! Please select again!" << endl;
        else break;
    }
}
