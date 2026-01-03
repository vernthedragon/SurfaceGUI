#pragma once
#include "SBaseRenderable.h"
#include "IFont.h"
class SText : public SBaseRenderable {
public:
	SText(Vector2D pos, IFont* font, Vector2D size, Color col, std::string text, RenderFlags flags);
	void Render(IVDevice* device);
	void WireFrameRender(IVDevice* device, ID3DXLine* line) { };
	bool WireFrame() { return false; };
private:
	Vector2D pos, size; IFont* font; Color col; std::string text; RenderFlags flags;
};

