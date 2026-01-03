#pragma once
#include "Includes.h"
#include "IVRender.h"
#define MAX_WINDOW_NAME_SIZE 256
#define GetInstance() GetModuleHandle(NULL)
struct IO {
	Vector2D MousePos;
	Vector2D MousePosRelativeToWindow;
};
class IWindow {
public:
	void EnableDPIScalling();
	void BindRender(IVRender* renderview);
	void Initialize(const char* Class, const char* title, int W, int H);
	void Show();
	void Hide();
	void SetBorderLess();
	IO GetIO();
	void UpdateEvents();
	void SetPosition(Vector2D Pos);
	HWND GetWindow();	
	LPRECT ClipRect();
	Vector2D Pos;
	Vector2D Size;
	Vector2D MouseCache;
	bool SetMouseCache = false;
	bool Dragable = true;
	bool InRegion(Vector2D pos, Vector2D size, Vector2D cursor) {
		return(cursor.x > pos.x && cursor.x < pos.x + size.x && cursor.y > pos.y && cursor.y < pos.y + size.y);
	}
private:

	HWND hWnd;
	RECT Rect;

};
class CWindowManager {
public:
	void HideConsole();
	IWindow* CreateNewWindow(const char* Class, const char* title, int W, int H);
};
