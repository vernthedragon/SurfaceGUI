#pragma once
#include "IVDevice.h"
#include "DrawList.h"
#include "IFont.h"

enum IVRenderCallback : int {
	CALLBACK_RESET = 0,
	CALLBACK_RENDER = 1,
	CALLBACK_PRERENDER = 2
};

class IVRender {
public:
	IVRender() {
		Device = new IVDevice();
	}
	void Bind(HWND hwnd, bool windowed, Vector2D ClipSize);
	void CreateIFont(IFont* font, std::string fontname, int size, IFontWeight weight, IFontType type, bool italic);
	void CreateIFont(IFont& font, std::string fontname, int size, IFontWeight weight, IFontType type, bool italic);
	void DestroyIFont(IFont& font);
	void DestroyIFont(IFont* font);
	void RenderText(Vector2D pos, std::string text, Color col, IFont* font, RenderFlags flags);
	void SetColor(Color col);
	IVDevice* GetDevice();
	void GradientCircle(Vector2D center, float radius, Color color1, Color color2);
	void FilledCircle(Vector2D center, float radius, Color color);
	void FilledRectangle(Vector2D topleft, Vector2D size, Color color);
	void GradientRectangle(Vector2D topleft, Vector2D size, Color tl, Color tr, Color bl, Color br);
	void Rectangle(Vector2D topleft, Vector2D size, Color color, float thickness);
	void Circle(Vector2D center, float radius, Color color, float thickness);
	void Line(Vector2D first, Vector2D second, Color color, float thickness);
	void Render();
	void AddCallback(std::function<void(IVDevice*, CDrawList*)> func, IVRenderCallback type);
	void ClearCallbacks(IVRenderCallback type);
private:
	std::vector < std::function<void(IVDevice*, CDrawList*)>> RenderCallback;
	std::vector < std::function<void(IVDevice*, CDrawList*)>> PreRenderCallback;
	std::vector < std::function<void(IVDevice*, CDrawList*)>> ResetCallback;
	CDrawList* DrawList = new CDrawList();
	IVDevice* Device;
	Color col;
	Vector2D ClipSize;
};
