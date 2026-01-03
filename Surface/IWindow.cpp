#include "IWindow.h"

void IWindow::EnableDPIScalling() {
	SetProcessDPIAware();
}
void IWindow::BindRender(IVRender* renderview) {
	renderview->Bind(hWnd, true, Size);
}
void IWindow::Initialize(const char* Class, const char* title, int W, int H) {

	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wcex.lpszClassName = Class;
	wcex.lpszMenuName = nullptr;
	wcex.hInstance = GetInstance();
	wcex.lpfnWndProc = DefWindowProc;
	RegisterClassEx(&wcex);
	hWnd = CreateWindow(Class, title, CW_USEDEFAULT,
		CW_USEDEFAULT, 0, W, H, nullptr, nullptr, GetInstance(), nullptr);
	Size = Vector2D(W, H);
	SetRect(&Rect, 0, 0, W, H);

}
void IWindow::Show() {
	ShowWindow(hWnd, SW_SHOW);
}
void IWindow::Hide() {
	ShowWindow(hWnd, SW_HIDE);
}
void IWindow::SetBorderLess() {
	SetWindowLongW(hWnd, GWL_EXSTYLE, 0);
}
IO IWindow::GetIO() {
	IO io;
	POINT MP;
	GetCursorPos(&MP);
	io.MousePos = Vector2D(MP.x, MP.y);
	ScreenToClient(hWnd, &MP);
	io.MousePosRelativeToWindow = Vector2D(MP.x, MP.y);
	return io;
}
void IWindow::UpdateEvents() {
	if (!Dragable) {
		SetMouseCache = false;
		return;
	}
	if ((GetAsyncKeyState(1) & (1 << 16))) {
		auto IO = GetIO();
		if (InRegion(Pos, Size, IO.MousePos)) {

			if (!SetMouseCache) {
				SetMouseCache = true;
				MouseCache = IO.MousePos - Pos;
			}
			SetPosition(IO.MousePos - MouseCache);
		}
	}
	else
		SetMouseCache = false;
}
void IWindow::SetPosition(Vector2D Pos) {
	SetWindowPos(hWnd, NULL, Pos.x, Pos.y, Size.x, Size.y, NULL);
	this->Pos = Pos;
	SetRect(&Rect, Pos.x,Pos.y, Size.x, Size.y);
}
HWND IWindow::GetWindow() {
	return hWnd;
}
LPRECT IWindow::ClipRect() {

}
void CWindowManager::HideConsole() {
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	FreeConsole();
}

IWindow* CWindowManager::CreateNewWindow(const char* Class, const char* title, int W, int H) {
	IWindow* window = new IWindow();
	window->Initialize(Class, title, W, H);
	return window;
}