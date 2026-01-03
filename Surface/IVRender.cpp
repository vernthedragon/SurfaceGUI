#include "IVRender.h"

void IVRender::Bind(HWND hwnd, bool windowed, Vector2D ClipSize) {
	Device->Bind(hwnd, windowed);
	this->ClipSize = ClipSize;
}
void IVRender::CreateIFont(IFont* font, std::string fontname, int size, IFontWeight weight, IFontType type, bool italic) {
	font->GenerateFont(Device, fontname.c_str(), size, weight, type, italic);
}
void IVRender::DestroyIFont(IFont* font) {
	font->Invalidate();
	font = nullptr;
}
void IVRender::CreateIFont(IFont& font, std::string fontname, int size, IFontWeight weight, IFontType type, bool italic) {
	font.GenerateFont(Device, fontname.c_str(), size, weight, type, italic);
}
void IVRender::FilledRectangle(Vector2D topleft, Vector2D size, Color color) {
	DrawList->FilledRectangle(topleft, size, color);
}
void IVRender::DestroyIFont(IFont& font) {
	font.Invalidate();
}
void IVRender::RenderText(Vector2D pos, std::string text, Color col, IFont* font, RenderFlags flags) {
	DrawList->RenderText(pos, text, col, font, flags);
}


void IVRender::SetColor(Color col) {
	this->col = col;

}
IVDevice* IVRender::GetDevice() {
	return Device;
}
void IVRender::GradientCircle(Vector2D center, float radius, Color color1, Color color2) {
	DrawList->GradientCircle(center, radius, color1, color2);
}
void IVRender::FilledCircle(Vector2D center, float radius, Color color) {
	DrawList->FilledCircle(center, radius, color);
}
void IVRender::Rectangle(Vector2D topleft, Vector2D size, Color color, float thickness) {
	DrawList->Rectangle(topleft, size, color, thickness);
}
void IVRender::Circle(Vector2D center, float radius, Color color, float thickness) {
	DrawList->Circle(center, radius, color, thickness);
}
void IVRender::GradientRectangle(Vector2D topleft, Vector2D size, Color tl, Color tr, Color bl, Color br) {
	DrawList->GradientRectangle(topleft, size, tl, tr, bl, br);
}
void IVRender::AddCallback(std::function<void(IVDevice*, CDrawList*)> func, IVRenderCallback type) {
	switch (type) {
	case IVRenderCallback::CALLBACK_PRERENDER:
		PreRenderCallback.push_back(func);
		break;
	case IVRenderCallback::CALLBACK_RENDER:
		RenderCallback.push_back(func);
		break;
	case IVRenderCallback::CALLBACK_RESET:
		ResetCallback.push_back(func);
		break;
	}
}
void IVRender::Line(Vector2D first, Vector2D second, Color color, float thickness) {
	DrawList->Line(first, second, color, thickness);
}
void IVRender::ClearCallbacks(IVRenderCallback type) {
	switch (type) {
	case IVRenderCallback::CALLBACK_PRERENDER:
		PreRenderCallback.clear();
		break;
	case IVRenderCallback::CALLBACK_RENDER:
		RenderCallback.clear();
		break;
	case IVRenderCallback::CALLBACK_RESET:
		ResetCallback.clear();
		break;
	}
}
void IVRender::Render() {
	DrawList->ClipSize = ClipSize;
	Device->Clear(col);
	Device->BeginScene();
	for (auto& callbacks : PreRenderCallback) {
		callbacks(Device, DrawList);
	}

	Device->Device->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	Device->Device->SetRenderState(D3DRS_LIGHTING, false);
	Device->Device->SetRenderState(D3DRS_FOGENABLE, false);
	Device->Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	Device->Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	Device->Device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	Device->Device->SetRenderState(D3DRS_SCISSORTESTENABLE, true);
	Device->Device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	Device->Device->SetRenderState(D3DRS_STENCILENABLE, false);

	Device->Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	Device->Device->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	Device->Device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, true);
	Device->Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->Device->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA);
	Device->Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	Device->Device->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);

	Device->Device->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
	Device->Device->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);

	Device->Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	Device->Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	Device->Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	Device->Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	Device->Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	Device->Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	Device->Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);


	//render here

	if (!DrawList->WireFrameCtx.LineReady) {
		DrawList->WireFrameCtx.CreateContext(Device);
	}
	for (auto& callbacks : RenderCallback) {
		callbacks(Device, DrawList);
	}

	for (auto& renderable : DrawList->Renderables)
	{
		if (renderable->WireFrame())
			renderable->WireFrameRender(Device, DrawList->WireFrameCtx.Line);
		else
			renderable->Render(Device);
	}
	DrawList->Clear();
	for (auto& callbacks : ResetCallback) {
		callbacks(Device, DrawList);
	}

	Device->EndScene();
	Device->Present();

}