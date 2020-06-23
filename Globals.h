#pragma once
#include "Header.h"

extern RECT window_size;

constexpr INT dividing_line_top = 140;
constexpr INT dividing_line_right = 450; // Screen length - dividing_line_right gives curren line position
constexpr INT top_of_crane = dividing_line_top + 210;
constexpr INT beggining_of_crane = 220;
constexpr INT end_of_crane = 800;
constexpr INT starting_x_of_hook = beggining_of_crane + 50;
constexpr INT starting_y_of_hook = top_of_crane + 100;
constexpr INT changing_range = 5;
constexpr INT center_distance = 10;
constexpr INT hook_size = 20;
constexpr INT lift = 1000;


/*
constexpr LONG current_x_of_0_point = (window_size.right - dividing_line_right) / 2;
constexpr LONG current_y_of_0_point = (window_size.bottom) + dividing_line_top) / 2;
constexpr LONG current_z_of_0_point = ((1000 + dividing_line_top) / 2 + dividing_line_top) / 2;
constexpr LONG current_t_of_0_point = window_size.right - 400;
constexpr LONG current_right_line = 1903 - dividing_line_right;

*/
//1903, 1000 to wymiary zmaksymalizowanego ekranu (bez scrolla) Je¿eli program jest otwierany w ekranie o innym rozmiarze nale¿y zmieniæ te sta³e

#define PI			   	 3.141592

#define UP_CONST			 1
#define DWN_CONST			 2
#define LFT_CONST		 3
#define GRB_CONST		 4
#define RGT_CONST		 5


#define SQUARE				  100
#define TRIANGLE			  101
#define CIRCLE				  102
#define HOOK				  103
#define LINE				  104

#define CENTER_DISTANCE				  10   //Odleg³oœæ od œrodka do rogu obiektu (lub jego promieñ)
#define HOOK_SIZE						  20  //Wielkoœæ ka¿dego z elementów


#define CURRENT_X_OF_0_POINT  ((window_size.right - dividing_line_right) / 2)
#define CURRENT_Y_OF_0_POINT  ((window_size.bottom + dividing_line_top) / 2)
#define CURRENT_Z_OF_0_POINT  (((window_size.bottom + dividing_line_top) / 2 + dividing_line_top) / 2)
#define CURRENT_T_OF_0_POINT  (window_size.right - 400)
#define CURRENT_RIGHT_LINE    (window_size.right - dividing_line_right)

#define GROUND				  (window_size.bottom - 200)
