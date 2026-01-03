#pragma once
#include "SBaseRenderable.h"

class SCircle : public SBaseRenderable {
public:
	SCircle(Vector2D Center, float radius, Color color, float thickness);
	void Render(IVDevice* device) {};
	void WireFrameRender(IVDevice* device, ID3DXLine* line);
	bool WireFrame() { return true; };
private:
	Vector2D Center; Color color; float thickness, radius;
};

