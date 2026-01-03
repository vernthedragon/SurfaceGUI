#pragma once
#include "Includes.h"
#include "IVRender.h"
#include "IVDevice.h"
#include "IWindow.h"
#include "SDK.h"
struct {
	IVRender* Render = new IVRender();
	CWindowManager* WindowManager = new CWindowManager();
	SDK* Sdk = new SDK();
}Surface;