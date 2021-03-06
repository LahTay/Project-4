
#include "Globals.h"
#include "Header.h"
using namespace Gdiplus;

class element
{
public:
	
	element(int x,int y, int mass, int typ, std::vector<std::pair<int, int>> &position){
		xpos = x;
		ypos = y;
		weight = mass;
		type = typ;
		position.push_back(std::make_pair(x, y));
		is_obstacle = false;
		cant_move = false;
	}

	void change_position(int dx, int dy, std::vector<std::pair<int, int>>& position) {//ten vector to pierwsze co mi przysz�o do g�owy w celu sprawdzania czy co� znajduje si� na drodze obiektu
		bool obstacle = false;
		
		if (type == HOOK) { //Sprawdza czy wszystkie coorynaty po zmianie b�d� w obszarze dzwigu
				std::vector<std::pair<int, int>>::iterator it = position.begin(); // hook to pierwszy element position
				it->first = xpos + dx; 
				it->second = ypos + dy;
				xpos += dx;
				ypos += dy;
				is_obstacle = false;
			}

		
		else if (xpos + dx - center_distance > beggining_of_crane and xpos + dx + center_distance < end_of_crane and ypos + dy - center_distance > top_of_crane  and ypos + dy + center_distance <= GROUND ) {  // Czy jest w obszarze dzwigu
				for (std::vector<std::pair<int, int>>::iterator it = (position.begin() + 1); it < position.end(); it++) {   // Przejd� przez wszystkie elementy
					if (it->first == xpos and it->second == ypos) // Je�li element ma te same koordynaty co przenoszony to jest on sam sob� i jest pomijany
						continue;					
					
					
					if (dx) {																																//Jesli w elemencie jest
						if ((xpos + dx + center_distance > it->first - center_distance and xpos + dx + center_distance < it->first + center_distance or  // (prawa sciana LUB
							xpos + dx - center_distance > it->first - center_distance and xpos + dx - center_distance < it->first + center_distance) and  // lewa sciana) I
							(ypos + dy + center_distance >= it->second - center_distance and ypos + dy + center_distance <= it->second + center_distance or  // (dolna sciana LUB
								ypos + dy - center_distance >= it->second - center_distance and ypos + dy - center_distance <= it->second + center_distance)) // gorna sciana)
							obstacle = true;																										// To jest w elemencie
					}
					else
						if ((xpos + dx + center_distance >= it->first - center_distance and xpos + dx + center_distance <= it->first + center_distance or  // (prawa sciana LUB
							xpos + dx - center_distance >= it->first - center_distance and xpos + dx - center_distance <= it->first + center_distance) and  // lewa sciana) I
							(ypos + dy + center_distance > it->second - center_distance and ypos + dy + center_distance < it->second + center_distance or  // (dolna sciana LUB
								ypos + dy - center_distance > it->second - center_distance and ypos + dy - center_distance < it->second + center_distance)) // gorna sciana)
							obstacle = true;

					is_obstacle = true;
					

				
				}
				if (!obstacle) {
					for (std::vector<std::pair<int, int>>::iterator it = position.begin() + 1; it < position.end(); it++) {
						if (it->first == xpos and it->second == ypos) {
							it->first = xpos + dx;
							it->second = ypos + dy;
							xpos += dx;
							ypos += dy;
							is_obstacle = false;
						}
					}
				}
			}
		else if (dx > 0 and !dy) {
			for (std::vector<std::pair<int, int>>::iterator it = position.begin() + 1; it < position.end(); it++) {
				if (it->first == xpos and it->second == ypos) {
					it->first = end_of_crane - center_distance - 1;
					xpos = end_of_crane - center_distance - 1;
					is_obstacle = true;
					
				}
			}
		}

		else if (dx < 0 and !dy) {
			for (std::vector<std::pair<int, int>>::iterator it = position.begin() + 1; it < position.end(); it++) {
				if (it->first == xpos and it->second == ypos) {
					it->first = beggining_of_crane + center_distance + 1;
					xpos = beggining_of_crane + center_distance + 1;
					is_obstacle = true;

				}
			}
		}

		else if (!dx  and dy > 0 ) {
			for (std::vector<std::pair<int, int>>::iterator it = position.begin() + 1; it < position.end(); it++) {
				if (it->first == xpos and it->second == ypos) {
					it->second = GROUND - center_distance - 1;
					ypos = GROUND - center_distance - 1;
					is_obstacle = true;

				}
			}
		}

		else if (!dx and dy < 0) {
			for (std::vector<std::pair<int, int>>::iterator it = position.begin() + 1; it < position.end(); it++) {
				if (it->first == xpos and it->second == ypos) {
					it->second = top_of_crane + center_distance + 1;
					ypos = top_of_crane + center_distance + 1;
					is_obstacle = true;

				}
			}
		}

	}

	void draw(HDC hdc)
	{
		switch (type) { //Zamiast wielu if else
		case SQUARE:
			draw_rect(hdc);
			break;
		case HOOK:
			draw_line(hdc);
			draw_hook(hdc);
			break;
		default:
			break;
		}
	}
	int check_weight()
	{
		return weight;
	}
	Point check_pos()
	{
		Point temp(xpos, ypos);
			return temp;
	}
	int check_x() {
		return xpos;
	}
	int check_y() {
		return ypos;
	}
	bool was_made_obstacle() {
		return is_obstacle;
	}
	bool can_move() {
		return cant_move;
	}
	int check_type() {
		return type;
	}

	
private:
	int weight;
	int xpos;
	int ypos;
	int type;
	bool is_obstacle;
	bool cant_move;

	Point starting_point = { xpos, ypos };
	Color color{ 255,255,0,0 };
	
	VOID draw_rect(HDC hdc)
	{
		Graphics graphics(hdc); //Klasa zawieraj�ca metody do rysowania
		Pen      pen(color, 3); //Klasa zwieraj�ca atrybuty lini takie jak: Opacity, Red, Green, Blue

		pen.SetDashStyle(DashStyleSolid);
		graphics.DrawRectangle(&pen, (xpos - CENTER_DISTANCE), (ypos - CENTER_DISTANCE), CENTER_DISTANCE * 2, CENTER_DISTANCE * 2);
		DeleteObject(&pen);
	}
	
	VOID draw_line(HDC hdc) {
		Graphics graphics(hdc);
		Pen      pen(color, 3);

		Point beggining(xpos, top_of_crane);
		Point ending(xpos, ypos);

		graphics.DrawLine(&pen, beggining, ending); //From x,y -> x,y to coords

		DeleteObject(&pen);
	}
	VOID draw_hook(HDC hdc) {
		Graphics graphics(hdc);
		Pen      pen(color, 3);
	
		Point first(xpos - HOOK_SIZE / 2, ypos);
		Point second(xpos + HOOK_SIZE / 2, ypos);

		graphics.DrawLine(&pen, first, second); //From x,y -> x,y to coords

		DeleteObject(&pen);
	}
};
