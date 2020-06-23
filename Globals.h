#pragma once
#include "Header.h"

extern RECT window_size;

constexpr INT dividing_line_top = 140;
constexpr INT top_of_crane = dividing_line_top + 210;
constexpr INT beggining_of_crane = 220;
constexpr INT end_of_crane = 800;
constexpr INT starting_x_of_hook = beggining_of_crane + 50;
constexpr INT starting_y_of_hook = top_of_crane + 100;
constexpr INT changing_range = 5;
constexpr INT center_distance = 10;
constexpr INT hook_size = 20;



#define SQUARE				  100
#define TRIANGLE			  101
#define CIRCLE				  102
#define HOOK				  103
#define LINE				  104

#define CENTER_DISTANCE				  10   //Odleg³oœæ od œrodka do rogu obiektu (lub jego promieñ)
#define HOOK_SIZE						  20  //Wielkoœæ ka¿dego z elementów


#define GROUND				  (window_size.bottom - 200)
