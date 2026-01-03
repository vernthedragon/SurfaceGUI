#include "IVDevice.h"

void IVDevice::Bind(HWND hwnd, bool windowed) {
	DirectX = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS PresentParam;
	ZeroMemory(&PresentParam, sizeof(D3DPRESENT_PARAMETERS));
	PresentParam.Windowed = windowed;
	PresentParam.SwapEffect = D3DSWAPEFFECT_DISCARD;
	PresentParam.hDeviceWindow = hwnd;
	DirectX->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_MIXED_VERTEXPROCESSING, &PresentParam, &Device);
}
void IVDevice::Clear(Color color) {
	Device->Clear(0, NULL, D3DCLEAR_TARGET, color.GetDColor(), 1.0f, 0);
}
void IVDevice::BeginScene() {
	Device->BeginScene();
}
void IVDevice::EndScene() {
	Device->EndScene();
}
void IVDevice::Present() {
	Device->Present(NULL, NULL, NULL, NULL);
}