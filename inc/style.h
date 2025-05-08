#pragma once

#include <cstdint>
#include <string>

using namespace std;

typedef struct F_COLOR {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} F_COLOR;

typedef struct B_COLOR {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} B_COLOR;

typedef struct CHAR {
	F_COLOR f_color;
	B_COLOR b_color;
} CHAR;

#define normal "\e[0m"
#define bold "\e[1m"
#define dim "\e[2m"
#define italic "\e[3m"
#define underline "\e[4m"
#define blink "\e[5m"
#define reverse "\e[7m"
#define invisible "\e[8m"

#define back_black "\e[40m"
#define back_red "\e[41m"
#define back_green "\e[42m"
#define back_yellow "\e[43m"
#define back_blue "\e[44m"
#define back_violet "\e[45m"
#define back_cyan "\e[46m"
#define back_white "\e[47m"

#define black "\e[90m"
#define red "\e[91m"
#define green "\e[92m"
#define yellow "\e[93m"
#define blue "\e[94m"
#define violet "\e[95m"
#define cyan "\e[96m"
#define white "\e[97m"

const bool NOT_EXPANDABLE = false;
const bool EXPANDABLE = true;
const bool DIRECTION_H = 0;
const bool DIRECTION_V = 1;
