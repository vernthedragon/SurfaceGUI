#pragma once
#include "SBaseRenderable.h"

class SGradientRectangle : public SBaseRenderable {
public:
	SGradientRectangle(Vector2D TopLeft, Vector2D Size, Color tp, Color tr, Color bl, Color bt);
	void Render(IVDevice* device);
	void WireFrameRender(IVDevice* device, ID3DXLine* line) { };
	bool WireFrame() { return false; };
private:
	Vector2D TopLeft, Size; Color tp,  tr,  bl,  bt;
};

