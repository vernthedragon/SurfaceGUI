#include "Interfaces.h"

int main() {
	Surface.WindowManager->HideConsole();
	auto Window = new IWindow();
	Window->Initialize("test", "test", 500, 500);
	Window->EnableDPIScalling();
	Window->BindRender(Surface.Render);
	Window->Show();
	Window->Dragable = true;
	Surface.Render->SetColor({ 0,0,0,255 });
	MSG msg = { 0 };
	IFont font;
	Surface.Render->CreateIFont(font, "Arial", 30, IFontWeight::IFW_NORMAL, IFontType::IFT_ALIASED, false);

	Surface.Render->AddCallback([&](IVDevice* device, CDrawList* drawlist) { 
		Surface.Render->RenderText({ 50,50 }, std::to_string(Surface.Sdk->Vars.TickCount), { 255,255,255,255 }, &font, RenderFlags::RF_LEFT); 
		Surface.Render->FilledRectangle({ 100,100 }, { 50,50 }, Color(255, 255, 255, 255));
		}, IVRenderCallback::CALLBACK_PRERENDER);

	Surface.Sdk->GlobalTimer.AddCallback([]() {Surface.Render->Render(); });
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Window->UpdateEvents();
	}

		
	
	
	return 0;
}