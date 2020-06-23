
#include "Globals.h"
#include "Header.h"
using namespace Gdiplus;
//z racji ¿e tylko podpunkt 4 to niepotrzebne s¹ inne kszta³ty
class element
{
public:
	
	element(int x,int y, int mass, int typ, std::vector<std::pair<int, int>> &position){
		xpos = x;
		ypos = y;
		weight = mass;
		type = typ;
		position.push_back(std::make_pair(x, y));
}
	


	

	void change_position(int dx, int dy, std::vector<std::pair<int, int>>& position) {//ten vector to pierwsze co mi przysz³o do g³owy w celu sprawdzania czy coœ znajduje siê na drodze obiektu
		bool obstacle = false;
		
		if (type == HOOK) { //Sprawdza czy wszystkie coorynaty po zmianie bêd¹ w obszarze dzwigu
				std::vector<std::pair<int, int>>::iterator it = position.begin(); // hook to pierwszy element position
				it->first = xpos + dx; 
				it->second = ypos + dy;
				xpos += dx;
				ypos += dy;
				is_obstacle = false;
			}

		
		else if (xpos + dx - center_distance > beggining_of_crane and xpos + dx + center_distance < end_of_crane and ypos + dy - center_distance > top_of_crane  and ypos + dy + center_distance <= GROUND ) {  // Czy jest w obszarze dzwigu
				for (std::vector<std::pair<int, int>>::iterator it = (position.begin() + 1); it < position.end(); it++) {   // PrzejdŸ przez wszystkie elementy
					if (it->first == xpos and it->second == ypos) // Jeœli element ma te same koordynaty co przenoszony to jest on sam sob¹ i jest pomijany
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
		

		
			/*
				for (std::vector<std::pair<int, int>>::iterator i = (position.begin() + 1); i < position.end(); i++) {
					if (dy == 0)
					{
						if ((ypos < (i->second - 2 * CENTER_DISTANCE + 1)) && (ypos > i->second + 2 * CENTER_DISTANCE - 1))
						{
							if ((xpos + dx > i->first + 2 * CENTER_DISTANCE) || (xpos + dx < i->first - 2 * CENTER_DISTANCE))
							{
							}
							else obstacle = true;

						}
					}
					else
					{
						if ((xpos < (i->first - 2 * CENTER_DISTANCE + 1)) && (xpos > i->first + 2 * CENTER_DISTANCE - 1))
						{
							if ((ypos + dy > i->second + 2 * CENTER_DISTANCE) || (ypos + dy < i->second - 2 * CENTER_DISTANCE))
							{
							}
							else obstacle = true;

						}
					}
				}
			
			if (!obstacle && type == SQUARE)
			{
				for (std::vector<std::pair<int, int>>::iterator i = position.begin() + 1; i < position.end(); i++) {
					if (i->first == xpos && i->second == ypos)
					{
						i->first = xpos + dx;
						i->second = ypos + dy;
						xpos += dx;
						ypos += dy;
					}
				}
			}
			else if (type == HOOK)
			{
				std::vector<std::pair<int, int>>::iterator i = position.begin();
				i->first = xpos + dx;
				i->second = ypos + dy;
				xpos += dx;
				ypos += dy;
			}
		*/
	}
	bool check_lift(int max)
	{
		if (weight > max)
			return false;
		else return true;
	}
	void draw(HDC hdc)
	{
		switch (type) { //Zamiast wielu if else
		case SQUARE:
			draw_rect(hdc);
			break;
		case TRIANGLE:
			draw_triangle(hdc);
			break;
		case CIRCLE:
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
	bool was_made_obstacle() {
		return is_obstacle;
	}

	
private:
	int weight;
	int xpos;
	int ypos;
	int type; //obecnie raczej nieu¿ywane mo¿na przechowaæ kszta³t obiektu 1 = kwadrat i tak dalej, zawsze mo¿e siê przydaæ, po zmianie typ 1 element typ 2 hak
	bool is_obstacle;

	Point starting_point = { xpos, ypos };
	Color color{ 255,255,0,0 };
	
	VOID draw_rect(HDC hdc)
	{
		Graphics graphics(hdc); //Klasa zawieraj¹ca metody do rysowania
		Pen      pen(color, 3); //Klasa zwieraj¹ca atrybuty lini takie jak: Opacity, Red, Green, Blue

		pen.SetDashStyle(DashStyleSolid);
		graphics.DrawRectangle(&pen, (xpos - CENTER_DISTANCE), (ypos - CENTER_DISTANCE), CENTER_DISTANCE * 2, CENTER_DISTANCE * 2);
		DeleteObject(&pen);
	}
	VOID draw_triangle(HDC hdc)
	{
		Graphics graphics(hdc);
		Pen      pen(color, 3);

		Point p1(xpos, ypos - CENTER_DISTANCE) ;
		Point p2(xpos - CENTER_DISTANCE, ypos - CENTER_DISTANCE) ;
		Point p3(xpos + CENTER_DISTANCE, ypos - CENTER_DISTANCE) ;
		Point pointarray[3] = { p1,p2,p3 };
		
		pen.SetDashStyle(DashStyleSolid);
		graphics.DrawPolygon(&pen, pointarray,3);
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
