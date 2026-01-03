#pragma once
#include "Includes.h"
#include "IVDevice.h"
struct IWireFrameContext {
	ID3DXLine* Line;
	bool LineReady;
	void CreateContext(IVDevice* Device) {
		if (SUCCEEDED(D3DXCreateLine(Device->Device, &Line))) {
			LineReady = true;
		}
		
	}
};