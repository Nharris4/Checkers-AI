#ifndef COLORS_H_
#define COLORS_H_

#include <string>


//Definitions used for displaying the board
const std::string bg_white    = "\x1b[47m";
const std::string bg_black    = "\x1b[40m";
const std::string bg_red      = "\x1b[41m";
const std::string bg_yellow   = "\x1b[43m";
const std::string fg_white    = "\x1b[30m";
const std::string fg_black    = "\x1b[37m";
const std::string cls         = "\033[2J\033[1H";
const std::string rst         = "\x1b[0m";
const std::string square      = "  ";

#endif
