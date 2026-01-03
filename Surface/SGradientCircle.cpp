#include "SGradientCircle.h"

SGradientCircle::SGradientCircle(Vector2D center, float radius, Color color1, Color color2) {
	this->center = center;
	this->radius = radius;
	this->color1 = color1;
	this->color2 = color2;
}
void SGradientCircle::Render(IVDevice* device) {
	SDrawHelper.BuildMoveTable();
	const auto col1 = color1.rn32();
	const auto col2 = color2.rn32();


	vertex vert[64 + 2] = {};

	for (auto i = 1; i <= 64; i++)
		vert[i] =
	{
		center.x + radius * SDrawHelper.MoveTable[i].x,
		center.y - radius * SDrawHelper.MoveTable[i].y,
		0.0f,
		1.0f,
		col1
	};

	vert[0] = { center.x, center.y, 0.0f, 1.0f, col2 };
	vert[64 + 1] = vert[1];

	device->Device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, true);
	device->Device->SetTexture(0, nullptr);
	device->Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 64, &vert, sizeof vertex);
	device->Device->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, false);
}