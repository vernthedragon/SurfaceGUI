#pragma once
#include "SBaseRenderable.h"

class SRectangle : public SBaseRenderable {
public:
	SRectangle(Vector2D TopLeft, Vector2D Size, Color color, float thickness);
	void Render(IVDevice* device) {};
	void WireFrameRender(IVDevice* device, ID3DXLine* line);
	bool WireFrame() { return true; };
private:
	Vector2D TopLeft, Size; Color color; float thickness;
};

