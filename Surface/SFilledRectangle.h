#pragma once
#include "SBaseRenderable.h"

class SFilledRectangle : public SBaseRenderable {
public:
	SFilledRectangle(Vector2D TopLeft, Vector2D Size, Color color);
	void Render(IVDevice* device);
	void WireFrameRender(IVDevice* device, ID3DXLine* line) { };
	bool WireFrame() { return false; };
private:
	Vector2D TopLeft, Size; Color color;
};

