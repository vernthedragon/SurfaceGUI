#pragma once
#include "SBaseRenderable.h"

class SGradientCircle : public SBaseRenderable {
public:
	SGradientCircle(Vector2D center, float radius, Color color1, Color color2);
	void Render(IVDevice* device);
	void WireFrameRender(IVDevice* device, ID3DXLine* line) { };
	bool WireFrame() { return false; };
private:
	Vector2D center; float radius; Color color1, color2;
};

