#pragma once

#include <cstdint>
#include <string>

using namespace std;

typedef struct POSITION {
	int x, y;
} POSITION;

typedef struct SIZE {
	int w, h;
} SIZE;

typedef struct BORDER {
	bool l, t, r, b;
} BORDER;

typedef struct COLOR {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} COLOR;

typedef struct CHAR {
	COLOR f_color;
	COLOR b_color;
} CHAR;

#define normal "\e[0m"
#define bold "\e[1m"
#define dim "\e[2m"
#define italic "\e[3m"
#define underline "\e[4m"
#define blink "\e[5m"
#define reverse "\e[7m"
#define invisible "\e[8m"

const COLOR black {0, 0, 0};
const COLOR red {255, 0, 0};
const COLOR green {0, 255, 0};
const COLOR blue {0, 0, 255};
const COLOR yellow {0, 255, 255};
const COLOR violet {255, 0, 255};
const COLOR cyan {255, 255, 0};
const COLOR white {255, 255, 255};

const bool NOT_EXPANDABLE = false;
const bool EXPANDABLE = true;
const bool DIRECTION_H = 0;
const bool DIRECTION_V = 1;
