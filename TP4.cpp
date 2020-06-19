#include "Header.h"
#include "Globals.h"
#include "element.cpp"


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

typedef struct button_struct
{
	HWND velocity_btn;
	HWND scale_btn;
	HWND time_btn;
	HWND starting_btn;
	HWND samples_throw_btn;
}button;

typedef struct input_struct
{
	HWND velocity_edit;
	HWND scale_edit;
	HWND time_edit;
	HWND samples_throw_edit;
}input;

button              btn;
input               inpt;

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

VOID make_buttons(HWND hwnd_main, button& btn, input& inpt) {

	create_button(hwnd_main, btn.velocity_btn, 10, 96, 150, 40, LPCTSTR(L"up"), UP_CONST);
	//create_input(hwnd_main, inpt.velocity_edit, 10, 40, 150, 20, LPCTSTR(L"1"), V_EDIT_CONST);

	create_button(hwnd_main, btn.time_btn, 250, 96, 150, 40, LPCTSTR(L"down"), DWN_CONST);
	//create_input(hwnd_main, inpt.time_edit, 250, 40, 150, 20, LPCTSTR(L"0"), NULL);

	create_button(hwnd_main, btn.scale_btn, 500, 96, 150, 40, LPCTSTR(L"left"), LFT_CONST);
	//create_input(hwnd_main, inpt.scale_edit, 500, 40, 150, 20, LPCTSTR(L"1"), SC_EDIT_CONST);

	create_button(hwnd_main, btn.starting_btn, 1000, 96, 150, 40, LPCTSTR(L"grab/release element"), GRB_CONST);

	//create_input(hwnd_main, inpt.samples_throw_edit, 1000, 40, 150, 20, LPCTSTR(L"0"), CH_EDIT_CONST);
	create_button(hwnd_main, btn.samples_throw_btn, 750, 96, 150, 40, LPCTSTR(L"right"), RGT_CONST);

}


void generate_starting_condition(std::vector<std::pair<int, int>> &pos_array, std::vector<element> &elements)
{
		elements.push_back(element(starting_x_of_hook, starting_y_of_hook, 1, SQUARE, pos_array));
	
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
	static element hook(starting_x_of_hook, starting_y_of_hook, 1, HOOK, pos_array);
	

	RECT drawing_size = { 0, dividing_line_top, window_size.right, window_size.bottom };
	bool taken = FALSE;
	element* pom=&hook;

	bool start = true;
	switch (uMsg)
	{

	case WM_CREATE:


		make_buttons(hwnd, btn, inpt);
		generate_starting_condition(pos_array, elements);
		
		return 0;
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);

		if (start) {
			draw_crane(hdc);
			draw_main(hdc, ps);
			start = false;
		}
		if (draw_graph) {
			FillRect(hdc, &drawing_size, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));
			draw_crane(hdc);
			//draw_all(hdc,elements,hook);
			hook.draw(hdc);
			
			
		}

		EndPaint(hwnd, &ps);
		draw_graph = false;
		return 0;
	}

	case WM_COMMAND:
		switch (wParam) {
		case UP_CONST:
			hook.change_position(0, -10, pos_array);
			
			if (taken) 
				 pom->change_position(0, -1, pos_array); 
			draw_graph = true;
			InvalidateRect(hwnd, &window_size, FALSE);
			return 0;

		case DWN_CONST:
			hook.change_position(0, 10, pos_array);
			
			if (taken) 
				pom->change_position(0, 1, pos_array); 
			draw_graph = true;
			InvalidateRect(hwnd, &window_size, FALSE);
			return 0;
		case RGT_CONST:
			hook.change_position(10, 0, pos_array);
			
			if (taken) 
				pom->change_position(1, 0, pos_array);
			draw_graph = true;
			InvalidateRect(hwnd, &window_size, FALSE);
		case GRB_CONST:

			return 0;
		case LFT_CONST:
			hook.change_position(-10, 0, pos_array);
			
			if (taken)
				pom->change_position(-1, 0, pos_array);
			draw_graph = true;
			InvalidateRect(hwnd, &window_size, FALSE);
			return 0;


		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

}

