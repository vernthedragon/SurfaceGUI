#pragma once
#include "Includes.h"
#include "IFont.h"
#include "SBaseRenderable.h"
#include "SGradientCircle.h"
#include "SFilledCircle.h"
#include "SText.h"
#include "SFilledRectangle.h"
#include "SRectangle.h"
#include "IWireFrameContext.h"
#include "SCircle.h"
#include "SGradientRectangle.h"
#include "SLine.h"
class CDrawList {
public:
	void GradientCircle(Vector2D center, float radius, Color color1, Color color2) {
		Renderables.push_back(new SGradientCircle(center, radius, color1, color2));
	}
	void FilledCircle(Vector2D center, float radius, Color color) {
		Renderables.push_back(new SFilledCircle(center, radius, color));
	}
	void RenderText(Vector2D pos, std::string text,Color col, IFont* font, RenderFlags flags) {
		Renderables.push_back(new SText(pos, font, ClipSize, col, text, flags));
	}
	void FilledRectangle(Vector2D topleft, Vector2D size, Color col) {
		Renderables.push_back(new SFilledRectangle(topleft, size, col));
	}
	void GradientRectangle(Vector2D topleft, Vector2D size, Color tl, Color tr, Color bl, Color br) {
		Renderables.push_back(new SGradientRectangle(topleft, size, tl,tr,bl,br));
	}
	void Rectangle(Vector2D topleft, Vector2D size, Color col, float thickness) {
		Renderables.push_back(new SRectangle(topleft, size, col, thickness));
	}
	void Circle(Vector2D center, float radius, Color color, float thickness) {
		Renderables.push_back(new SCircle(center, radius, color, thickness));
	}
	void Line(Vector2D first, Vector2D second, Color color, float thickness) {
		Renderables.push_back(new SLine(first, second, color, thickness));
	}
	void Clear() {
		Renderables.clear();
	}
	Vector2D ClipSize;
	std::vector<SBaseRenderable*> Renderables;
	IWireFrameContext WireFrameCtx;
};