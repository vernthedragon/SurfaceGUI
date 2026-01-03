#include "SGradientRectangle.h"

SGradientRectangle::SGradientRectangle(Vector2D TopLeft, Vector2D Size, Color tp, Color tr, Color bl, Color bt) {
	this->TopLeft = TopLeft;
	this->Size = Size;
	this->tp = tp;
	this->tr = tr;
	this->bl = bl;
	this->bt = bt;
}
void SGradientRectangle::Render(IVDevice* device) {
	vertex vert[5];
	vert[0] = {
		TopLeft.x,
		TopLeft.y,
		0.0f,
		1.0f,
		tp.rn32()
	};
	vert[1] = {
	TopLeft.x + Size.x,
	TopLeft.y,
	0.0f,
	1.0f,
	tr.rn32()
	};
	vert[2] = {
	TopLeft.x + Size.x,
	TopLeft.y + Size.y,
	0.0f,
	1.0f,
	bt.rn32()
	};
	vert[3] = {
	TopLeft.x,
	TopLeft.y + Size.y,
	0.0f,
	1.0f,
	bl.rn32()
	};
	vert[4] = {
	TopLeft.x,
	TopLeft.y,
	0.0f,
	1.0f,
	tp.rn32()
	};

	device->Device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, false);
	device->Device->SetTexture(0, nullptr);
	device->Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 4, &vert, sizeof vertex);
	device->Device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, false);
}