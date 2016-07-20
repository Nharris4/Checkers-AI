//board.cpp
//ECE 469 AI

#include "board.h"
#include "colors.h"

using namespace std;

Board::display(){
    cout << bg_red;
    for(int i = 0; i < 56; i++)
            cout << square;

    cout << rst << endl;
    cout << bg_red << square;
    cout << bg_white;

    for(int i = 0; i < 52; i++)
            cout << square;

    cout << bg_red << square << rst << endl;

    bool odd;
    for (int i = 0; i < 8; i++)
            for(int j =0; j<3; j++)
                    for(int k = 0; k<4; k++){
                        int n = i*4+k;

                        if(k == 0){
                            cout << bg_red << square;;
                            if (i < 4)
                                    cout << bg_white << square;
                            else
                                    cout << bg_black << square;
                        }

                        odd = (((n - (n%4))/4)%2);
                        if(!odd)
                                cout << bg_yellow << square;
                        else    cout << bg_black << square;
                        
                        cout << bg_red;
                        if(j ==0){
                                if (i <10)

                    
                    }



}
