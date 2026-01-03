#include "SLine.h"

SLine::SLine(Vector2D first, Vector2D second, Color color, float thickness) {
	this->first = first;
	this->second = second;
	this->color = color;
	this->thickness = thickness;

}
void SLine::WireFrameRender(IVDevice* device, ID3DXLine* line) {


	line->SetWidth(thickness);
	line->SetAntialias(1);
	D3DXVECTOR2 Vertexes[] = { D3DXVECTOR2(first.x, first.y), D3DXVECTOR2(second.x , second.y)};

	line->Begin();
	line->Draw(Vertexes, 2, color.GetDColor());
	line->End();






}