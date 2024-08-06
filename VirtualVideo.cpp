#include "VirtualVideo.h"

HRESULT VirtualVideo::Init(HINSTANCE hInstacne, LPCWSTR title, UINT width, UINT height)
{
	D2DFramework::Init(hInstacne, title, width, height);

	//
	return S_OK;
}

void VirtualVideo::Render()
{
	mpRenderTarget->BeginDraw();

	mpRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

	//

	mpRenderTarget->EndDraw();
	HRESULT hr = mpRenderTarget->EndDraw();
	if (hr == D2DERR_RECREATE_TARGET)
	{
		CreateDeviceResources();
	}
}
