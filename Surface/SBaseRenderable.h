#pragma once
#include "IVDevice.h"
#include "Includes.h"
class SBaseRenderable {
public:
	virtual void Render(IVDevice* device) = 0;
	virtual bool WireFrame() = 0;
	virtual void WireFrameRender(IVDevice* device, ID3DXLine* line) = 0;
};

struct {
	void BuildMoveTable()
	{
		if (!MoveTable.empty())
			return;

		for (auto i = 0; i <= points; i++)
			MoveTable.emplace_back(
				std::cos(2.f * PI * (i / static_cast<float>(points))),
				std::sin(2.f * PI * (i / static_cast<float>(points)))
			);
	}
	static constexpr auto points = 64;
	std::vector<Vector2D> MoveTable;
}SDrawHelper;