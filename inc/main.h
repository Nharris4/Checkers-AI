#ifndef MAIN_H_
#define MAIN_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../inc/game.h"

#ifndef HUMAN
#define HUMAN 1
#endif

#ifndef AI
#define AI 0
#endif

#ifndef BLK
#define BLK 1
#endif

#ifndef RED
#define RED 0
#endif

Game *current_game;

void start_game(int red_player, int black_player,int time_limit);

void init();
 
#endif
