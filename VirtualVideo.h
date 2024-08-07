#pragma once
#include "D2DFramework.h"
#include <memory>

const int BITMAP_WIDTH = 1024;
const int BITMAP_HEIGHT = 768;
const int BITMAP_BYTECOUNT = 4; //R G B + A (1byte)

class VirtualVideo : public D2DFramework
{
private:
	std::unique_ptr<UINT8[]> mspMemoryBuffer;
	Microsoft::WRL::ComPtr<ID2D1Bitmap> mspVirualGC;

public:
	HRESULT Init(HINSTANCE hInstacne, LPCWSTR title = L"D2DFramework", UINT width = 1024, UINT height = 768);
	void Render() override;

	void Present();

	void DrowPixelToBuffer(int x, int y, D2D1::ColorF color);

	void ClearBuffer(D2D1::ColorF color);
	//사각형 채우기
	void FillRectToBuffer(int left, int top, int width, int height, D2D1::ColorF color);
	//선기르기
	//두 점을 잇는 직선의 방정식
	void LineToBuffer(int x1, int y1, int x2, int y2, D2D1::ColorF color);
	//원을 챠우는 건 아니고 테두리만 그리기
	//원점과 반지름이 주어질 때 원의 방정식
	void CircleToBuffer(int centerX, int centerY, int radius, D2D1::ColorF color);
};

