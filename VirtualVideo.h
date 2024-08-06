#pragma once
#include "D2DFramework.h"
#include <memory>

const int BITMAP_WIDTH = 1024;
const int BITMAP_HEIGHT = 768;
const int BITMAP_BYTECOuNT = 4; //R G B + A (1byte)

class VirtualVideo : public D2DFramework
{
private:
	std::unique_ptr<UINT8[]> mspMemoryBuffer;
	Microsoft::WRL::ComPtr<ID2D1Bitmap> mspVirualGC;

public:
	HRESULT Init(HINSTANCE hInstacne, LPCWSTR title = L"D2DFramework", UINT width = 1024, UINT height = 768);
	void Render() override;

};

