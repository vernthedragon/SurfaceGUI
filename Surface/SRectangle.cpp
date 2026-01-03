#include "SRectangle.h"

SRectangle::SRectangle(Vector2D TopLeft, Vector2D Size, Color color, float thickness) {
	this->TopLeft = TopLeft;
	this->Size = Size;
	this->color = color;
	this->thickness = thickness;

}
void SRectangle::WireFrameRender(IVDevice* device, ID3DXLine* line) {


	line->SetWidth(thickness);
	line->SetAntialias(1);
	D3DXVECTOR2 Vertexes[] = { D3DXVECTOR2(TopLeft.x, TopLeft.y), D3DXVECTOR2(TopLeft.x + Size.x, TopLeft.y), D3DXVECTOR2(TopLeft.x + Size.x, TopLeft.y + Size.y),D3DXVECTOR2(TopLeft.x, TopLeft.y + Size.y),D3DXVECTOR2(TopLeft.x,TopLeft.y) };

	line->Begin();
	line->Draw(Vertexes, 5, color.GetDColor());
	line->End();

	

	


}