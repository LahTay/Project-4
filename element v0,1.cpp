#include <gdiplustypes.h>
#include <gdiplus.h>
#include <windows.h>
#include <gdiplusgraphics.h>
#include <vector>
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;

class element
{
public:
	element(HDC window,int x,int y, int mass, int typ){
		xpos = x;
		ypos = y;
		weight = mass;
		type = typ;
		hdc = window;
}
	element(HDC window, int x, int y, int mass) {
		xpos = x;
		ypos = y;
		weight = mass;
		type = 1;
		hdc = window;
	}
	void changeposition(int dx, int dy, std::vector<std::pair<int, int>> position) {//ten vector to pierwsze co mi przysz³o do g³owy w celu sprawdzania czy coœ znajduje siê na drodze obiektu
		bool obstacle=false;
		for (std::vector<std::pair<int, int>>::iterator i = position.begin(); i < position.end(); i++) {
			if (!(((i->first > (xpos + dx + 5)) || (i->first < (xpos + dx - 5))) && ((i->second > (ypos + dy + 5)) || (i->second < (ypos + dy - 5)))))
			{
				if (i->first != xpos || i->second != ypos)
				{
					obstacle = true;
				}
			}
		}

		if(!obstacle)
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
		else if(type==2)
			draw_triangle()
		else draw_circle()
	}
	int weight()
	{
		return weight;
	}
	Point check_pos()
	{
		Point temp(xpos, ypos)
			return temp;
	}
private:
	int weight;
	int xpos;
	int ypos;
	int type; //obecnie raczej nieu¿ywane mo¿na przechowaæ kszta³t obiektu 1 = kwadrat i tak dalej, zawsze mo¿e siê przydaæ
	Color color(255,255,0,0);
	DashStyle dash_style = 0;
	HDC hdc;
	VOID draw_rect()
	{
		Graphics graphics(hdc); //Klasa zawieraj¹ca metody do rysowania
		Pen      pen(color, 3); //Klasa zwieraj¹ca atrybuty lini takie jak: Opacity, Red, Green, Blue

		pen.SetDashStyle(dash_style);
		graphics.DrawRectangle(pen,xpos-5,ypos-5,10,10);
		DeleteObject(&pen);
	}
	VOID draw_triangle()
	{
		Graphics graphics(hdc);
		Pen      pen(color, 3);
		Point[] pointarray
		{
			new Point(xpos, ypos-5),
			new Point(xpos-5, ypos-5),
			new Point(xpos+5, ypos-5)
		}
		pen.SetDashStyle(dash_style);
		graphics.DrawPolygon(pen,pointarray);
		DeleteObject(&pen);
	}
	VOID draw_circle()
	{
		Graphics graphics(hdc);
		Pen      pen(color, 3);

		pen.SetDashStyle(dash_style);
		graphics.DrawElipse(pen, xpos - 5, ypos - 5, 10, 10);
		DeleteObject(&pen);
	}

};