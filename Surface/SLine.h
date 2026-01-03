#pragma once
#include "SBaseRenderable.h"

class SLine : public SBaseRenderable {
public:
	SLine(Vector2D first, Vector2D second, Color color, float thickness);
	void Render(IVDevice* device) {};
	void WireFrameRender(IVDevice* device, ID3DXLine* line);
	bool WireFrame() { return true; };
private:
	Vector2D first, second; Color color; float thickness;
};

