#include "D2DFramework.h"
#pragma comment (lib,"d2d1.lib")

using namespace Microsoft::WRL;

HRESULT D2DFramework::Init(HINSTANCE hInstacne, LPCWSTR title, UINT width, UINT height)
{
	InitWindow(hInstacne, title, width, height);
	InitD2D();

	ShowWindow(mHwnd, SW_SHOW);
	UpdateWindow(mHwnd);

	return S_OK;
}

void D2DFramework::Release()
{
	mpRenderTarget.Reset();
	mpD2DFactory.Reset();
}

void D2DFramework::Render()
{
	// 3. 그리기
	mpRenderTarget->BeginDraw();

	mpRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

	mpRenderTarget->EndDraw();
	HRESULT hr = mpRenderTarget->EndDraw();
	if (hr == D2DERR_RECREATE_TARGET)
	{
		CreateDeviceResources();
	}
}

int D2DFramework::GameLoop()
{
	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			//게임 그리기 혹은 연산
			Render();
		}
	}
	return (int)msg.wParam;
}

HRESULT D2DFramework::InitWindow(HINSTANCE hInstacne, LPCWSTR title, UINT width, UINT height)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstacne;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpfnWndProc = WindowProc;
	wc.cbSize = sizeof(WNDCLASSEX);

	if (!RegisterClassEx(&wc))
	{
		ThowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
	}

	RECT wr = { 0,0,(LONG)width, (LONG)height };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hwnd = CreateWindowEx(
		NULL,
		CLASS_NAME,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		wr.right - wr.left, wr.bottom - wr.top,
		NULL,
		NULL,
		hInstacne,
		NULL
	);

	if (!hwnd)
	{
		ThowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
		return E_FAIL;
	}

	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);

	mHwnd = hwnd;
	return S_OK;
}

HRESULT D2DFramework::InitD2D()
{
	// 1. Factory 생성
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, mpD2DFactory.GetAddressOf());

	// if(SUCCEEDED(hr))	//성공
	ThowIfFailed(hr);

	// 2. 렌더타겟 생성
	//D2D1_RENDER_TARGET_PROPERTIES rtp;
	//ZeroMemory();
	//rtp.dpiX;...



	return CreateDeviceResources();
}

HRESULT D2DFramework::CreateDeviceResources()
{
	RECT wr;
	GetClientRect(mHwnd, &wr);

	HRESULT hr = mpD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(mHwnd, D2D1::SizeU(wr.right - wr.left, wr.bottom - wr.top)),
		&mpRenderTarget);

	ThowIfFailed(hr);

	return S_OK;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	D2DFramework* pFramework = (D2DFramework*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	switch (message)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}