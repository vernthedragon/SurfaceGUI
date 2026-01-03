#include "SFilledRectangle.h"

SFilledRectangle::SFilledRectangle(Vector2D TopLeft, Vector2D Size, Color color) {
	this->TopLeft = TopLeft;
	this->Size = Size;
	this->color = color;
}
void SFilledRectangle::Render(IVDevice* device) {
	vertex vert[5];
	vert[0] = {
		TopLeft.x,
		TopLeft.y,
		0.0f,
		1.0f,
		color.rn32()
	};
	vert[1] = {
	TopLeft.x + Size.x,
	TopLeft.y,
	0.0f,
	1.0f,
	color.rn32()
	};
	vert[2] = {
	TopLeft.x + Size.x,
	TopLeft.y + Size.y,
	0.0f,
	1.0f,
	color.rn32()
	};
	vert[3] = {
	TopLeft.x,
	TopLeft.y + Size.y,
	0.0f,
	1.0f,
	color.rn32()
	};
	vert[4] = {
	TopLeft.x,
	TopLeft.y,
	0.0f,
	1.0f,
	color.rn32()
	};

	device->Device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, false);
	device->Device->SetTexture(0, nullptr);
	device->Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 4, &vert, sizeof vertex);
	device->Device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, false);
}