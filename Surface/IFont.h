#pragma once
#include "Includes.h"
#include "IVDevice.h"

enum IFontWeight : int {
	IFW_INVALID = 0,
	IFW_THIN = 100,
	IFW_EXTRALIGHT = 200,
	IFW_LIGHT = 300,
	IFW_NORMAL = 400,
	IFW_MEDIUM = 500,
	IFW_SEMIBOLD = 600,
	IFW_BOLD = 700,
	IFW_EXTRABOLD = 800,
	IFW_HEAVY = 900
};

enum IFontType : int {
	IFT_DEFAULT = 0,
	IFT_DRAFT = 1,
	IFT_PROOF = 2,
	IFT_NONALIASED = 3,
	IFT_ALIASED = 4
};

enum RenderFlags : DWORD {
	RF_TOP = 0x00000000,
	RF_LEFT = 0x00000000,
	RF_CENTER = 0x00000001,
	RF_RIGHT = 0x00000002,
	RF_VCENTER = 0x00000004,
	RF_BOTTOM = 0x00000008,
	RF_SINGLELINE = 0x00000020,
	RF_NOCLIP = 0x00000100
};

class IFont {
public:
	IFont() { Valid = false; }
	~IFont() {}
	void GenerateFont(IVDevice* device, LPCSTR fontname,int size, IFontWeight weight, IFontType type,bool italic) {
		if (SUCCEEDED(D3DXCreateFontA(device->Device, size, 0, ((UINT)weight), 1, false, DEFAULT_CHARSET, ((DWORD)type), type, DEFAULT_PITCH, fontname, &RawFont))) {
			Valid = true;
		}
	}
	void Render(Vector2D pos, Vector2D WindowSize, std::string Text, Color color, RenderFlags flags, LPD3DXSPRITE Sprite) {
		if (Valid) {
			RECT rect;
			SetRect(&rect, pos.x, pos.y, WindowSize.x, WindowSize.y);
			RawFont->DrawTextA(Sprite, Text.c_str(), -1, &rect, flags, color.GetDColor());
		}
	}
	void Invalidate() {
		Valid = false;
		RawFont->Release();
		RawFont = nullptr;
	}

private:
	bool Valid;
	LPD3DXFONT RawFont;
};