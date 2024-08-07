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
	//�簢�� ä���
	void FillRectToBuffer(int left, int top, int width, int height, D2D1::ColorF color);
	//���⸣��
	//�� ���� �մ� ������ ������
	void LineToBuffer(int x1, int y1, int x2, int y2, D2D1::ColorF color);
	//���� í��� �� �ƴϰ� �׵θ��� �׸���
	//������ �������� �־��� �� ���� ������
	void CircleToBuffer(int centerX, int centerY, int radius, D2D1::ColorF color);
};

