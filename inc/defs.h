#ifndef DEFS_H_
#define DEFS_H_

	#include <string>

	// ANSI escape color codes 
	// Definitions used for displaying the board
	const std::string bg_white    = "\x1b[47m";
	const std::string bg_black    = "\x1b[40m";
	const std::string bg_red      = "\x1b[41m";
	const std::string bg_yellow   = "\x1b[43m";
	const std::string fg_white    = "\x1b[30m";
	const std::string fg_black    = "\x1b[37m";
	const std::string cls         = "\033[2J\033[1H";
	const std::string rst         = "\x1b[0m";


	const std::string square_full = "          ";
	const std::string piece       = "    ";
	const std::string piece_king  = "|^^|"; // 
	const std::string square_half = "   ";


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

	typedef struct move {
	    int path[10][2];
	    int pieces_taken;
	    int move_count;
	} move;

#endif
