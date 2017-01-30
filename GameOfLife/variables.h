#ifndef VARIABLES_H
#define VARIABLES_H

#include <array>

static const std::array<std::array<int,  2>, 8>  envir
{{{{0,1}},
   {{0,-1}},
   { {1,0}},
   { {-1,0}},
   { {1,1}},
   { {-1,-1}},
   { {-1,1}},
   { {1,-1}}}};

enum :int {
    DEAD = 0,
    ALIVE = 1
};

static const int g_default_width = 15;
static const int g_default_height = 15;
static const int g_amount_of_enviroment_pos = 8;
static const int g_second = 1000;

#endif // VARIABLES_H

