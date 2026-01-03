#pragma once
#include "Includes.h"
class IVDevice {
public:
	IVDevice() {}
	~IVDevice() {
		if (Device) {
			Device->Release();
			Device = NULL;
		}
		if (DirectX) {
			DirectX->Release();
			DirectX = NULL;
		}
	};
	void Bind(HWND hwnd, bool windowed);
	void Clear(Color color);
	void BeginScene();
	void EndScene();
	void Present();
	IDirect3D9* DirectX;
	IDirect3DDevice9* Device;
};
