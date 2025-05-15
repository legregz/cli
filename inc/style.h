#pragma once

#include <cfenv>
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

typedef struct PADDING {
	int l, t, r, b;
} PADDING;

typedef struct ALIGNMENT {
	char w, h;
} ALIGNMENT;

typedef struct COLOR {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} COLOR;

typedef struct CHAR {
	COLOR f_color;
	COLOR b_color;
} CHAR;

const string NORMAL = "\e[0m";
const string BOLD = "\e[1m";
const string DIM = "\e[2m";
const string ITALIC = "\e[3m";
const string UNDERLINE = "\e[4m";
const string BLINK = "\e[5m";
const string REVERSE = "\e[7m";
const string INVISIBLE = "\e[8m";

const COLOR BLACK {0, 0, 0};
const COLOR RED {255, 0, 0};
const COLOR GREEN {0, 255, 0};
const COLOR BLUE {0, 0, 255};
const COLOR YELLOW {255, 255, 0};
const COLOR VIOLET {255, 0, 255};
const COLOR CYAN {0, 255, 255};
const COLOR WHITE {255, 255, 255};

const bool NOT_EXPANDABLE = false;
const bool EXPANDABLE = true;

const bool DIRECTION_H = 0;
const bool DIRECTION_V = 1;

const char LEFT = 'l';
const char CENTER = 'c';
const char RIGHT = 'r';
const char TOP = 't';
const char BOTTOM = 'b';
