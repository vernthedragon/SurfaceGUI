#include "SFilledCircle.h"


SFilledCircle::SFilledCircle(Vector2D center, float radius, Color color) {
	this->center = center;
	this->radius = radius;
	this->color = color;
}
void SFilledCircle::Render(IVDevice* device) {
	SDrawHelper.BuildMoveTable();
	const auto col = color.rn32();


	vertex vert[64 + 2] = {};

	for (auto i = 1; i <= 64; i++)
		vert[i] =
	{
		center.x + radius * SDrawHelper.MoveTable[i].x,
		center.y - radius * SDrawHelper.MoveTable[i].y,
		0.0f,
		1.0f,
		col
	};

	vert[0] = { center.x, center.y, 0.0f, 1.0f, col };
	vert[64 + 1] = vert[1];

	device->Device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, true);
	device->Device->SetTexture(0, nullptr);
	device->Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 64, &vert, sizeof vertex);
	device->Device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, false);
}