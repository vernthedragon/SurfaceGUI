#pragma once
#include "SBaseRenderable.h"


class SFilledCircle : public SBaseRenderable {
public:
	SFilledCircle(Vector2D center, float radius, Color color);
	void Render(IVDevice* device);
	void WireFrameRender(IVDevice* device, ID3DXLine* line) { };
	bool WireFrame() { return false; };
private:
	Vector2D center; float radius; Color color;
};

