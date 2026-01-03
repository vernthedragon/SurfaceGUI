#include "SText.h"

SText::SText(Vector2D pos, IFont* font, Vector2D size, Color col, std::string text, RenderFlags flags) {
	this->pos = pos;
	this->font = font;
	this->size = size;
	this->col = col;
	this->text = text;
	this->flags = flags;
}
void SText::Render(IVDevice* device) {
	this->font->Render(pos, size, text, col, flags, NULL);
}