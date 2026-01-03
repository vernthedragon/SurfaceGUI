#include "SCircle.h"

SCircle::SCircle(Vector2D Center, float radius, Color color, float thickness) {
	this->Center = Center;
	this->radius = radius;
	this->color = color;
	this->thickness = thickness;

}
void SCircle::WireFrameRender(IVDevice* device, ID3DXLine* line) {
	SDrawHelper.BuildMoveTable();

	line->SetWidth(thickness);
	line->SetAntialias(1);
	std::vector< D3DXVECTOR2 > vertexes;
	vertexes.push_back(D3DXVECTOR2(Center.x + radius * SDrawHelper.MoveTable[0].x, Center.y - radius * SDrawHelper.MoveTable[0].y));
	for (auto i = 1; i < 64; i++)
	{
		vertexes.push_back(D3DXVECTOR2(Center.x + radius * SDrawHelper.MoveTable[i].x, Center.y - radius * SDrawHelper.MoveTable[i].y));
	}
	vertexes.push_back(D3DXVECTOR2(Center.x + radius * SDrawHelper.MoveTable[0].x, Center.y - radius * SDrawHelper.MoveTable[0].y));

	line->Begin();
	line->Draw(vertexes.data(), vertexes.size(), color.GetDColor());
	line->End();






}