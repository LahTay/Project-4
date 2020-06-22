
#include "Globals.h"
#include "Header.h"
using namespace Gdiplus;
//z racji �e tylko podpunkt 4 to niepotrzebne s� inne kszta�ty
class element
{
public:
	
	element(int x,int y, int mass, int typ, std::vector<std::pair<int, int>> &position){
		xpos = x;
		ypos = y;
		weight = mass;
		type = typ;
		position.push_back(std::make_pair(x, y));
		falling = false;
}
	void change_position(int dx, int dy, std::vector<std::pair<int, int>> &position) {//ten vector to pierwsze co mi przysz�o do g�owy w celu sprawdzania czy co� znajduje si� na drodze obiektu
		bool obstacle = false;
		
		if (!((xpos+dx-2*CENTER_DISTANCE)<beggining_of_crane||(ypos+dy-2*CENTER_DISTANCE)<top_of_crane||(xpos+dx+2*CENTER_DISTANCE)>end_of_crane||(ypos+dy+2*CENTER_DISTANCE)>GROUND)) {
			if (type == SQUARE) {
				for (std::vector<std::pair<int, int>>::iterator i = (position.begin() + 1); i < position.end(); i++) {
					if (dy == 0)
					{
						if ((ypos < (i->second - 2 * CENTER_DISTANCE + 1)) && (ypos> i->second + 2 * CENTER_DISTANCE - 1))
						{
							if((xpos+dx>i->first+2*CENTER_DISTANCE)|| (xpos + dx < i->first - 2 * CENTER_DISTANCE))
							{ }
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
			}
			if (!obstacle && type==SQUARE)
			{
				for (std::vector<std::pair<int, int>>::iterator i = position.begin()+1; i < position.end(); i++) {
					if (i->first == xpos && i->second == ypos)
					{
						i->first = xpos + dx;
						i->second = ypos + dy;
						xpos += dx;
						ypos += dy;
					}
				}
			}
			else if (type==HOOK)
			{
				std::vector<std::pair<int, int>>::iterator i = position.begin();
				i->first = xpos + dx;
				i->second = ypos + dy;
				xpos += dx;
				ypos += dy;
			}
		}
		else if(type==SQUARE) obstacle = true;

		if (obstacle && !falling)
		{
			falling = true;
			taken = false;
			for (int j = 0; j < 100; j++)change_position(0, 5, position);
			falling = false;
		}
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
	int check_x()
	{
		return xpos;
	}
	int check_y()
	{
		return ypos;
	}
private:
	int weight;
	int xpos;
	int ypos;
	int type;//obecnie raczej nieu�ywane mo�na przechowa� kszta�t obiektu 1 = kwadrat i tak dalej, zawsze mo�e si� przyda�, po zmianie typ 1 element typ 2 hak
	bool falling;
	Point starting_point = { xpos, ypos };
	Color color{ 255,255,0,0 };
	
	VOID draw_rect(HDC hdc)
	{
		Graphics graphics(hdc); //Klasa zawieraj�ca metody do rysowania
		Pen      pen(color, 3); //Klasa zwieraj�ca atrybuty lini takie jak: Opacity, Red, Green, Blue
		pen.SetDashStyle(DashStyleSolid);
		graphics.DrawRectangle(&pen, (xpos - CENTER_DISTANCE), (ypos - CENTER_DISTANCE), 2*CENTER_DISTANCE, 2*CENTER_DISTANCE);
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

	/*VOID draw_circle()
	{
		Graphics graphics(hdc);
		Pen      pen(color, 3);

		pen.SetDashStyle(dash_style);
		graphics.DrawElipse(pen, xpos - 5, ypos - 5, 10, 10);
		DeleteObject(&pen);
	}
	*/
};
