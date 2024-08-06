#pragma once
#include<d2d1.h>
#include<wrl/client.h>
#include<exception>
#include<stdio.h>

class com_exception : public std::exception
{
public:
	com_exception(HRESULT hr) : result(hr) {}
	virtual const char* what() const override
	{
		static char str[64]{};

		sprintf_s(str, "Fail with HRESULT code : %X", (unsigned int)result);
		return str;
	}
private:
	HRESULT result;
};

inline void ThowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		throw com_exception(hr);
	}
}

class D2DFramework
{
public:
	virtual HRESULT Init(HINSTANCE hInstacne, LPCWSTR title = L"D2DFramework", UINT width = 1024, UINT height = 768);
	
	virtual void Release();
	virtual void Render();
	virtual int GameLoop();

protected:
	Microsoft::WRL::ComPtr<ID2D1Factory> mpD2DFactory{};
	Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> mpRenderTarget{};

	HRESULT InitWindow(HINSTANCE hInstacne, LPCWSTR title, UINT width, UINT height);
	HRESULT InitD2D();

	virtual HRESULT CreateDeviceResources();

protected:
	HWND mHwnd;
	

private:
	//컴파일은 cpp에서만 가능 / 헤더에서는 안됨
	const wchar_t* CLASS_NAME{ L"Direct2DSampleClass" };
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
