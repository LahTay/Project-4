#pragma once
#include "Header.h"

extern RECT window_size;

constexpr INT dividing_line_top = 140;
constexpr INT dividing_line_right = 450; // Screen length - dividing_line_right gives curren line position
/*
constexpr LONG current_x_of_0_point = (window_size.right - dividing_line_right) / 2;
constexpr LONG current_y_of_0_point = (window_size.bottom) + dividing_line_top) / 2;
constexpr LONG current_z_of_0_point = ((1000 + dividing_line_top) / 2 + dividing_line_top) / 2;
constexpr LONG current_t_of_0_point = window_size.right - 400;
constexpr LONG current_right_line = 1903 - dividing_line_right;

*/
//1903, 1000 to wymiary zmaksymalizowanego ekranu (bez scrolla) Je¿eli program jest otwierany w ekranie o innym rozmiarze nale¿y zmieniæ te sta³e

#define PI			   	 3.141592

#define V_CONST			 1
#define T_CONST			 2
#define SC_CONST		 3
#define ST_CONST		 4
#define CH_CONST		 5
#define CH_EDIT_CONST    6
#define SC_EDIT_CONST    7
#define V_EDIT_CONST     8

#define CURRENT_X_OF_0_POINT  ((window_size.right - dividing_line_right) / 2)
#define CURRENT_Y_OF_0_POINT  ((window_size.bottom + dividing_line_top) / 2)
#define CURRENT_Z_OF_0_POINT  (((window_size.bottom + dividing_line_top) / 2 + dividing_line_top) / 2)
#define CURRENT_T_OF_0_POINT  (window_size.right - 400)
#define CURRENT_RIGHT_LINE    (window_size.right - dividing_line_right)