//CHANGE LOG
// Zmiana zmiennych na static w WndProc






#include "Header.h"
#include "Globals.h"
#include "element.cpp"


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


int generate_random_number(int min_value, int max_value) {
	std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> r_distribution(min_value, max_value);
	return r_distribution(engine);
}
VOID draw_line(HDC hdc, const int x_begin, const int x_end, const int y_begin, const int y_end, const DashStyle dash_style, Color color, REAL thicc)
{
	Graphics graphics(hdc); //Klasa zawierająca metody do rysowania
	Pen      pen(color, thicc); //Klasa zwierająca atrybuty lini takie jak: Opacity, Red, Green, Blue

	pen.SetDashStyle(dash_style);
	graphics.DrawLine(&pen, x_begin, y_begin, x_end, y_end); //From x,y -> x,y to coords
	DeleteObject(&pen);
}


VOID draw_text(HDC hdc, const int x_begin, const int x_end, const int y_begin, const int y_end, const LPCWSTR text, const COLORREF color) {
	RECT rect = { x_begin, y_begin, x_end, y_end };
	SetTextColor(hdc, color);
	DrawText(hdc, (text), -1, &rect, DT_WORDBREAK | DT_TOP); // -1 to weźmie długość max zmiennej text
	SetTextColor(hdc, RGB(0, 0, 0));
}



VOID create_button(HWND hwnd_main, HWND& btn, const int x, const int y, const int width, const int height, LPCTSTR btn_text, int macro_value) {
	btn = CreateWindowEx(
		WS_EX_LEFT,
		(L"BUTTON"),  // Predefined class; Unicode assumed 
		btn_text,      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
		x,         // x position 
		y,         // y position 
		width,        // Button width
		height,        // Button height
		hwnd_main,     // Parent window
		reinterpret_cast<HMENU>(macro_value),       //ID send to WndProc
		reinterpret_cast<HINSTANCE>(GetWindowLongPtr(hwnd_main, GWLP_HINSTANCE)),
		nullptr);      // Pointer not needed.

}



VOID create_input(HWND hwnd_main, HWND& inpt, const int x, const int y, const int width, const int height, LPCTSTR btn_text, int macro_value) {
	inpt = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		(L"EDIT"),  // Predefined class; Unicode assumed 
		btn_text,      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles 
		x,         // x position 
		y,         // y position 
		width,        // Button width
		height,        // Button height
		hwnd_main,     // Parent window
		reinterpret_cast<HMENU>(macro_value),       //ID send to WndProc
		reinterpret_cast<HINSTANCE>(GetWindowLongPtr(hwnd_main, GWLP_HINSTANCE)),
		nullptr);      // Pointer not needed.

}


void generate_starting_condition(std::vector<std::pair<int, int>> &pos_array, std::vector<element> &elements)
{
		//elements.push_back(element(starting_x_of_hook, starting_y_of_hook, 1, SQUARE, pos_array));
	elements.push_back(element(beggining_of_crane + 50, GROUND - CENTER_DISTANCE, 50, SQUARE, pos_array));
	elements.push_back(element(beggining_of_crane + 100, GROUND - CENTER_DISTANCE, 100, SQUARE, pos_array));
	elements.push_back(element(beggining_of_crane + 150, GROUND - CENTER_DISTANCE, 150, SQUARE, pos_array));
	
}
void draw_all(HDC hdc, std::vector<element> elements, element hook)
{
	hook.draw(hdc);
	for (std::vector<element>::iterator i = elements.begin(); i < elements.end(); i++)
	{
		i->draw(hdc);
	}
}
VOID draw_main(HDC hdc, const PAINTSTRUCT ps) {

	RECT rect = { 0, 300, 100, 400 };

	draw_line(hdc, ps.rcPaint.left, ps.rcPaint.right, dividing_line_top, dividing_line_top, DashStyleSolid, { 255, 0, 0, 0 }, 3);
	
}

VOID draw_crane(HDC hdc) {
	draw_line(hdc, 0, window_size.right, GROUND, GROUND, DashStyleSolid, { 255, 0, 0, 0 }, 3);
	draw_line(hdc, beggining_of_crane, beggining_of_crane, dividing_line_top + 200, GROUND, DashStyleSolid, { 255, 0, 0, 0 }, 1);
	draw_line(hdc, beggining_of_crane - 20, beggining_of_crane - 20, dividing_line_top + 200, GROUND, DashStyleSolid, { 255, 0, 0, 0 }, 1);
	draw_line(hdc, beggining_of_crane - 20, beggining_of_crane, GROUND - 6, GROUND - 6, DashStyleSolid, { 255, 0 ,0 ,0 }, 12);
	draw_line(hdc, beggining_of_crane - 20, beggining_of_crane, dividing_line_top + 200 + 6, dividing_line_top + 200 + 6, DashStyleSolid, { 255, 0 ,0 ,0 }, 12);
	draw_line(hdc, beggining_of_crane, end_of_crane, top_of_crane - 10, top_of_crane - 10, DashStyleSolid, { 255, 0 , 0, 0 }, 1); //Dlugość żurawia
	draw_line(hdc, beggining_of_crane, end_of_crane, top_of_crane, top_of_crane, DashStyleSolid, { 255, 0, 0, 0 }, 1);
	draw_line(hdc, end_of_crane - 20, end_of_crane + 1, dividing_line_top + 205, dividing_line_top + 205, DashStyleSolid, { 255, 0, 0, 0 }, 10);

	draw_text(hdc, 200, 300, 300, 350, L"Poruszanie sie -> strzalki", RGB(0, 0, 0));
	draw_text(hdc, 400, 520, 300, 350, L"Zlapanie obiektu -> spacja", RGB(0, 0, 0));
	draw_text(hdc, beggining_of_crane + 40, beggining_of_crane + 60, GROUND + CENTER_DISTANCE, GROUND + CENTER_DISTANCE + 20, L"50", RGB( 255, 0, 0 ));
	draw_text(hdc, beggining_of_crane + 90, beggining_of_crane + 120, GROUND + CENTER_DISTANCE, GROUND + CENTER_DISTANCE + 20, L"100", RGB(255, 0, 0));
	draw_text(hdc, beggining_of_crane + 140, beggining_of_crane + 170, GROUND + CENTER_DISTANCE, GROUND + CENTER_DISTANCE + 20, L"150", RGB(255, 0, 0));
	draw_text(hdc, beggining_of_crane - 80 , beggining_of_crane - 40, top_of_crane,top_of_crane + 50, L"Max waga: 100", RGB(255, 0, 0));
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {


	HWND                hwnd;
	MSG                 msg;
	WNDCLASS            wcex;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;


	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = TEXT("Projekt4");


	RegisterClass(&wcex);


	hwnd = CreateWindowEx(WS_EX_LEFT, TEXT("Projekt4"), (L"Projekt 4"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, hInstance, nullptr);





	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);







	// Run the message loop.

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}

RECT window_size;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	

	bool draw_graph = true;
	//Added so the program will draw corretly in every resolution
	GetClientRect(hwnd, &window_size);

	static std::vector<std::pair<int, int>> pos_array;
	static std::vector<element> elements;

	

	static element hook(starting_x_of_hook, starting_y_of_hook, 100, HOOK, pos_array);
	
	RECT drawing_size = { beggining_of_crane + 1, top_of_crane + 1, end_of_crane + 20, GROUND };
	
	static element* pom = &hook;
	static bool taken = FALSE;
	static bool start = true;
	switch (uMsg)
	{

	case WM_CREATE:	
		return 0;
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);

		if (start) {
			generate_starting_condition(pos_array, elements);
			draw_crane(hdc);
			draw_main(hdc, ps);
			start = false;
		}
		if (draw_graph) {
			FillRect(hdc, &drawing_size, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));
			draw_crane(hdc);
			draw_all(hdc,elements,hook);
			hook.draw(hdc);
			
			
		}
		
		EndPaint(hwnd, &ps);
		draw_graph = false;
		return 0;
	}

	case WM_KEYDOWN:
	{
		
		Point xy = hook.check_pos();
		int x = xy.X;
		int y = xy.Y;
		switch (wParam) {
		case VK_UP:
			if (y - hook_size / 2 > top_of_crane) {
				if (taken) 
					pom->change_position(0, -changing_range, pos_array);

				if (!pom->was_made_obstacle())
					hook.change_position(0, -changing_range, pos_array);

					draw_graph = true;
				InvalidateRect(hwnd, &window_size, FALSE);
			}
			else {
				if(pom->check_type() == hook.check_type())
					hook.change_position(0, -(y - top_of_crane - 1), pos_array);
				else if (pom->check_y() - changing_range - center_distance > top_of_crane) {
					if (taken)
						pom->change_position(0, -changing_range, pos_array);
					hook.change_position(0, -(y - top_of_crane - 1), pos_array);
				}
					draw_graph = true;
					InvalidateRect(hwnd, &window_size, FALSE);
				
			}

			
			return 0;
		case VK_DOWN:
			if (y + hook_size / 2 < GROUND) {
				
				if (taken)
					pom->change_position(0, changing_range, pos_array);
				if (!pom->was_made_obstacle())
					hook.change_position(0, changing_range, pos_array);
					draw_graph = true;
				InvalidateRect(hwnd, &window_size, FALSE);
			}
			else {
				if (pom->check_type() == hook.check_type())
					hook.change_position(0, (GROUND - y - 1), pos_array);
				if (pom->check_y() + changing_range + center_distance < GROUND) {
					if (taken)
						pom->change_position(0, changing_range, pos_array);
					hook.change_position(0, (GROUND - y - 1), pos_array);
				}
					draw_graph = true;
					InvalidateRect(hwnd, &window_size, FALSE);
				
			}
			return 0;
		case VK_RIGHT:
			if (x + hook_size / 2 < end_of_crane) {
				
				if (taken)	
					pom->change_position(changing_range, 0, pos_array);
				if (!pom->was_made_obstacle())
					hook.change_position(changing_range, 0, pos_array);
					draw_graph = true;
				InvalidateRect(hwnd, &window_size, FALSE);
				
			}
			else {
				if (pom->check_type() == hook.check_type())
					hook.change_position(end_of_crane - x - 1, 0, pos_array);
				if (pom->check_x() + changing_range + center_distance < end_of_crane) {
					if (taken)
						pom->change_position(changing_range, 0, pos_array);
					hook.change_position(end_of_crane - x - 1, 0, pos_array);
				}
					draw_graph = true;
					InvalidateRect(hwnd, &window_size, FALSE);
				
			}
			
			return 0;
		case VK_LEFT:
			if (x - hook_size / 2 > beggining_of_crane) {
				if (taken)
					pom->change_position(-changing_range, 0, pos_array);
				if (!pom->was_made_obstacle())
					hook.change_position(-changing_range, 0, pos_array);
					draw_graph = true;
				InvalidateRect(hwnd, &window_size, FALSE);
			}
			else {
				if (pom->check_type() == hook.check_type())
					hook.change_position(-(x - beggining_of_crane - hook_size / 2), 0, pos_array);
				if (pom->check_x() - changing_range - center_distance > end_of_crane) {
					if (taken)
						pom->change_position(-changing_range, 0, pos_array);
					hook.change_position(-(x - beggining_of_crane - hook_size / 2), 0, pos_array);
					draw_graph = true;
					InvalidateRect(hwnd, &window_size, FALSE);
				}
			}
			return 0;
		case VK_SPACE:
			if (!taken)
			{
				int j = 0;
					for (std::vector<element>::iterator i = elements.begin(); i < elements.end(); i++)
					{
						Point element_coords = i->check_pos();
						j++;
						if (element_coords.X >= (x - center_distance) && element_coords.X <= (x + center_distance) && element_coords.Y >= (y - center_distance) && element_coords.Y <= (y + center_distance))
						{
							if (hook.check_weight() >= i->check_weight()) {
								pom = &*i;
								taken = true;
							}
						}
					}
				
			}
			else
			{
				pom = &hook;
				taken = false;
			}
				
			
			return 0;
		}
	}
	case WM_COMMAND:
		
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

}

