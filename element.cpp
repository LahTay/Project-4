
#include "Globals.h"
#include "Header.h"
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;
//z racji ¿e tylko podpunkt 4 to niepotrzebne s¹ inne kszta³ty
class element
{
public:
	
	element(HDC window,int x,int y, int mass, int typ,std::vector<std::pair<int, int>> position){
		xpos = x;
		ypos = y;
		weight = mass;
		type = typ;
		hdc = window;
		position.push_back(std::make_pair(x, y));
}
	element(HDC window, int x, int y, int mass, std::vector<std::pair<int, int>> position) {
		xpos = x;
		ypos = y;
		weight = mass;
		type = 1;
		hdc = window;
		position.push_back(std::make_pair(x,y));
	}
	void changeposition(int dx, int dy, std::vector<std::pair<int, int>> position) {//ten vector to pierwsze co mi przysz³o do g³owy w celu sprawdzania czy coœ znajduje siê na drodze obiektu
		bool obstacle = false;
		if (!((xpos+dx-5)<0||(ypos+dx-5)<dividing_line_top||(xpos+dx+5)>window_size.right||(ypos+dx+5)>window_size.bottom)) {
			if (type = 1) {
				for (std::vector<std::pair<int, int>>::iterator i = position.begin(); i < position.end(); i++) {
					if (!(((i->first > (xpos + dx + 5)) || (i->first < (xpos + dx - 5))) && ((i->second > (ypos + dy + 5)) || (i->second < (ypos + dy - 5)))))
					{
						if (i->first != xpos || i->second != ypos)
						{
							obstacle = true;
						}
					}
				}
			}
			if (!obstacle)
			{
				for (std::vector<std::pair<int, int>>::iterator i = position.begin(); i < position.end(); i++) {
					if (i->first == xpos && i->second == ypos)
					{
						i->first = xpos + dx;
						i->second = ypos + dy;
						xpos += dx;
						ypos += dy;
					}
				}
			}
		}
	}
	bool check_lift(int max)
	{
		if (weight > max)
			return false;
		else return true;
	}
	void draw()
	{
		if (type == 1)
			draw_rect();
		else if (type == 2)
			draw_triangle();
		//else draw_circle();
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
private:
	int weight;
	int xpos;
	int ypos;
	int type; //obecnie raczej nieu¿ywane mo¿na przechowaæ kszta³t obiektu 1 = kwadrat i tak dalej, zawsze mo¿e siê przydaæ, po zmianie typ 1 element typ 2 hak
	Color color{ 255,255,0,0 };
	DashStyle dash_style = DashStyleSolid;
	HDC hdc;
	VOID draw_rect()
	{
		Graphics graphics(hdc); //Klasa zawieraj¹ca metody do rysowania
		Pen      pen(color, 3); //Klasa zwieraj¹ca atrybuty lini takie jak: Opacity, Red, Green, Blue

		pen.SetDashStyle(dash_style);
		graphics.DrawRectangle(&pen, (xpos - 5), (ypos - 5), 10, 10);
		DeleteObject(&pen);
	}
	VOID draw_triangle()
	{
		Graphics graphics(hdc);
		Pen      pen(color, 3);
		Point p[3];
		Point p1(xpos, ypos - 5) ;
			Point p2(xpos - 5, ypos - 5) ;
			Point p3(xpos + 5, ypos - 5) ;
			Point temp[3] = { p1,p2,p3 };
			Point* pointarray = temp;
		pen.SetDashStyle(dash_style);
		graphics.DrawPolygon(&pen, pointarray,3);
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