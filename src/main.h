#ifndef MAIN_H_
#define MAIN_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>

#ifndef HUMAN
#define HUMAN 1
#endif

#ifndef AI
#define AI 0
#endif

void start_game(int red_player, int black_player,int time_limit);

void init();
 

#endif
