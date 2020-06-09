#include "pch.h"
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

	create_button(hwnd_main, btn.velocity_btn, 10, 96, 150, 40, LPCTSTR(L"up"), V_CONST);
	//create_input(hwnd_main, inpt.velocity_edit, 10, 40, 150, 20, LPCTSTR(L"1"), V_EDIT_CONST);

	create_button(hwnd_main, btn.time_btn, 250, 96, 150, 40, LPCTSTR(L"down"), T_CONST);
	//create_input(hwnd_main, inpt.time_edit, 250, 40, 150, 20, LPCTSTR(L"0"), NULL);

	create_button(hwnd_main, btn.scale_btn, 500, 96, 150, 40, LPCTSTR(L"left"), SC_CONST);
	//create_input(hwnd_main, inpt.scale_edit, 500, 40, 150, 20, LPCTSTR(L"1"), SC_EDIT_CONST);

	create_button(hwnd_main, btn.starting_btn, 1000, 96, 150, 40, LPCTSTR(L"take/leave element"), ST_CONST);

	//create_input(hwnd_main, inpt.samples_throw_edit, 1000, 40, 150, 20, LPCTSTR(L"0"), CH_EDIT_CONST);
	create_button(hwnd_main, btn.samples_throw_btn, 750, 96, 150, 40, LPCTSTR(L"right"), CH_CONST);

}


void generate_starting_condition(std::vector<std::pair<int, int>> &pos_array, std::vector<element> &elements)
{
	for (int i = 0; i < 15; i++)
	{
		elements.push_back(element(i * 10, 300, generate_random_number(1, 10) * 100, pos_array));
	}
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
/*	draw_line(hdc, ps.rcPaint.left, ps.rcPaint.right - dividing_line_right, (ps.rcPaint.bottom + dividing_line_top) / 2, (ps.rcPaint.bottom + dividing_line_top) / 2, DashStyleDash, { 255, 0, 0, 0 }, 1);
	draw_line(hdc, ps.rcPaint.right - dividing_line_right, ps.rcPaint.right, (ps.rcPaint.bottom + dividing_line_top) / 2, (ps.rcPaint.bottom + -dividing_line_top) / 2, DashStyleSolid, { 255, 0, 0, 0 }, 2);
	draw_line(hdc, ps.rcPaint.right - dividing_line_right, ps.rcPaint.right - dividing_line_right, dividing_line_top, ps.rcPaint.bottom, DashStyleSolid, { 255, 0, 0, 0 }, 3);
	draw_line(hdc, (ps.rcPaint.right - dividing_line_right) / 2, (ps.rcPaint.right - dividing_line_right) / 2, dividing_line_top, ps.rcPaint.bottom, DashStyleDash, { 255, 0, 0, 0 }, 1);
	draw_line(hdc, ps.rcPaint.right - dividing_line_right, ps.rcPaint.right, ((ps.rcPaint.bottom + dividing_line_top) / 2 + dividing_line_top) / 2, ((ps.rcPaint.bottom + dividing_line_top) / 2 + dividing_line_top) / 2, DashStyleDash, { 255, 0, 0, 255 }, 1);
	draw_line(hdc, ps.rcPaint.right - 400, ps.rcPaint.right - 400, dividing_line_top, (ps.rcPaint.bottom + dividing_line_top) / 2, DashStyleDash, { 255, 0, 0, 255 }, 1);

	draw_text(hdc, 10, 190, 20, 40, L"Set robot's current velocity", RGB(255, 0, 0));
	draw_text(hdc, 250, 500, 20, 40, L"Choose the time interval", RGB(255, 0, 0));
	draw_text(hdc, 500, 750, 20, 40, L"Scale the X,Y values", RGB(255, 0, 0));
	draw_text(hdc, 1000, 1400, 10, 60, L"How many first samples do you want to throw away? (Recommended at least 120) Has to be set before starting!", RGB(255, 0, 0));
	draw_text(hdc, 75, 1000, 70, 90, L"All values have to be set and a valid number! You can't assign an empty value!", RGB(255, 0, 0));
	draw_text(hdc, 700, 900, 50, 120, L"Values drawn on the graph in color blue are equal to currently passed time in seconds", RGB(0, 0, 255));
	draw_text(hdc, 650, 840, 0, 40, L"Scale has to be bigger than 0.03", RGB(255, 0, 0));

	draw_text(hdc, (ps.rcPaint.right - dividing_line_right - 50) / 2, (ps.rcPaint.right - dividing_line_right) / 2, dividing_line_top + 10, dividing_line_top + 30, L"OY", RGB(0, 0, 0));
	draw_text(hdc, (ps.rcPaint.right - dividing_line_right - 30), (ps.rcPaint.right - dividing_line_right), (ps.rcPaint.bottom + dividing_line_top) / 2 - 30, (ps.rcPaint.bottom + dividing_line_top) / 2 - 10, L"OX", RGB(0, 0, 0));
	draw_text(hdc, ps.rcPaint.right - 424, ps.rcPaint.right - 400, dividing_line_top + 10, dividing_line_top + 30, L"OZ", RGB(0, 0, 0));
	draw_text(hdc, ps.rcPaint.right - 30, ps.rcPaint.right, ((ps.rcPaint.bottom + dividing_line_top) / 2 + dividing_line_top) / 2 + 10, ((ps.rcPaint.bottom + dividing_line_top) / 2 + dividing_line_top) / 2 + 30, L"Ot", RGB(0, 0, 0));

	int draw_scale = 0;
	wchar_t draw_scale_w[256];
	if (scale_double == 0)
		scale_double = 1;

	if (scale_double < 0.04)
		scale_double = 0.04;


	for (draw_scale = 0; draw_scale < (CURRENT_RIGHT_LINE / 2) * scale_double; draw_scale += (100 * scale_double)) {
		swprintf_s(draw_scale_w, L"%d", draw_scale);
		wcsncat_s(draw_scale_w, L"m", 2);
		draw_text(hdc, CURRENT_RIGHT_LINE / 2 + (draw_scale / scale_double), (CURRENT_RIGHT_LINE / 2) + 50 + (draw_scale / scale_double), CURRENT_Y_OF_0_POINT + 5, CURRENT_Y_OF_0_POINT + 30, draw_scale_w, RGB(0, 0, 0));
	}

	for (draw_scale = 0; draw_scale < (CURRENT_Y_OF_0_POINT - dividing_line_top) * scale_double; draw_scale += (100 * scale_double)) {
		swprintf_s(draw_scale_w, L"%d", draw_scale);
		wcsncat_s(draw_scale_w, L"m", 2);
		draw_text(hdc, CURRENT_X_OF_0_POINT - 30, CURRENT_X_OF_0_POINT, CURRENT_Y_OF_0_POINT + 5 + (draw_scale / scale_double), CURRENT_Y_OF_0_POINT + 30 + (draw_scale / scale_double), draw_scale_w, RGB(0, 0, 0));
	}


	int draw_count = 0;
	for (draw_scale = 0; draw_scale < window_size.right * scale_double; draw_scale += 25 * scale_double) {
		swprintf_s(draw_scale_w, L"%d", draw_count);
		wcsncat_s(draw_scale_w, L"s", 2);
		draw_text(hdc, CURRENT_T_OF_0_POINT + (draw_scale / scale_double), CURRENT_T_OF_0_POINT + (draw_scale / scale_double) + 50, CURRENT_Z_OF_0_POINT + 5, CURRENT_Z_OF_0_POINT + 30, draw_scale_w, RGB(0, 0, 0));
		draw_count += scale_double;
	}


	for (draw_scale = 0; draw_scale < (CURRENT_Z_OF_0_POINT - dividing_line_top) * scale_double; draw_scale += 25 * scale_double) {
		swprintf_s(draw_scale_w, L"%d", draw_scale);
		wcsncat_s(draw_scale_w, L"m", 2);
		draw_text(hdc, CURRENT_T_OF_0_POINT - 30, CURRENT_T_OF_0_POINT, CURRENT_Z_OF_0_POINT + 5 - (draw_scale / scale_double), CURRENT_Z_OF_0_POINT + 30 - (draw_scale / scale_double) + 50, draw_scale_w, RGB(0, 0, 0));

	}*/
}

/*
void draw(HDC hdc, LPWSTR throw_samples, double velocity_double, double scale_double, int time_int)
{
	double temp;
	double x0 = CURRENT_X_OF_0_POINT;
	double y0 = CURRENT_Y_OF_0_POINT;
	double z0 = CURRENT_Z_OF_0_POINT;
	double t = CURRENT_T_OF_0_POINT;
	double x;
	double y;
	double z;
	double pitch;
	double yaw;
	double r;

	for (int i = 0; i < std::stoi(throw_samples) * 12; i++)
		file >> temp;

	for (int i = 0; i != time_int * 12 * 25; ++i)
		file >> temp;



	int time_cnt = 0;
	wchar_t draw_time_w[256];
	int written_counter = 0;

	while (!file.eof())
	{

		for (int j = 1; j <= 12; j++) {
			file >> temp;
			if (j % 12 == 2) pitch = temp;
			if (j % 12 == 3) yaw = temp;
		}
		pitch = pitch * PI / 180;
		yaw = yaw * PI / 180;
		r = sin(pitch)*velocity_double / scale_double;
		y = y0 + sin(yaw)*r;
		x = x0 + cos(yaw)*r;
		z = z0 - cos(pitch) * velocity_double / scale_double;
		t++;

		if (x < CURRENT_RIGHT_LINE and y > dividing_line_top) {
			draw_line(hdc, x0, round(x), y0, round(y), DashStyleSolid, { 255, 255, 0, 0 }, 3);

			int helpful_vel = (velocity_double);
			const int helpful_scl = (scale_double);
			const float what_to_write = (written_counter / velocity_double * scale_double + time_int);
			if (velocity_double > 75)
				helpful_vel = 75;
			if (time_cnt % static_cast<int>(75 / helpful_vel * scale_double) == 0) {

				swprintf_s(draw_time_w, L"%f", what_to_write);



				draw_line(hdc, x0, x0 + 20, y0, y0 - 20, DashStyleSolid, { 255, 0, 255, 0 }, 3);
				draw_text(hdc, x0 + 20, x0 + 70, y0 - 35, y0 - 20, draw_time_w, RGB(0, 0, 255));
				written_counter += 3;
			}
			++time_cnt;
		}
		if (z > dividing_line_top and z < CURRENT_Y_OF_0_POINT)
			draw_line(hdc, t - 1, t, z0, z, DashStyleSolid, { 255, 255, 0, 0 }, 3);

		x0 = x;
		y0 = y;
		z0 = z;
	}

}
*/

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
	wcex.lpszClassName = TEXT("Projekt3");


	RegisterClass(&wcex);


	hwnd = CreateWindowEx(WS_EX_LEFT, TEXT("Projekt3"), (L"Projekt 3"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
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
	std::vector<std::pair<int, int>> pos_array;
	std::vector<element> elements;
	element hook( 200, 200, 0, 2, pos_array);
	RECT drawing_size = { 0, dividing_line_top, window_size.right, window_size.bottom };
	bool taken = false;
	element* pom=&hook;
	switch (uMsg)
	{

	case WM_CREATE:


		make_buttons(hwnd, btn, inpt);
		generate_starting_condition(pos_array, elements);
		return 0;
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);


		draw_main(hdc, ps);

		if (draw_graph) {
			FillRect(hdc, &drawing_size, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));
			draw_all(hdc,elements,hook);

		}

		EndPaint(hwnd, &ps);
		draw_graph = false;
		return 0;
	}

	case WM_COMMAND:
		switch (wParam) {
		case V_CONST:
			hook.changeposition(0, -10, pos_array);
			if (taken) { pom->changeposition(0, -1, pos_array); }
			draw_graph = true;
			return 0;

		case T_CONST:
			hook.changeposition(0, 10, pos_array);
			if (taken) { pom->changeposition(0, 1, pos_array); }
			draw_graph = true;
			return 0;
		case CH_CONST:
			hook.changeposition(10, 0, pos_array);
			if (taken) { pom->changeposition(1, 0, pos_array); }
			draw_graph = true;
		case ST_CONST:

			return 0;
		case SC_CONST:
			hook.changeposition(-10, 0, pos_array);
			if (taken) { pom->changeposition(-1, 0, pos_array); }
			draw_graph = true;
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

