#pragma once

#include "ECommon.h"
#include <Windows.h>

//图形渲染底层分实现
namespace E3D
{
	extern HINSTANCE GHInstace;

	//图片封装，由于图片使用的GDI+的图片封装类
	//所以这里对它进行封装，将平台相关的东西隐藏
	class EBitmap
	{
	public:
		EInt width, height;

		EBitmap(const EString& filename);
		~EBitmap();

		inline EString getName() const { return name; }
		inline bool isValid() const { return valid; }
		EColor getPixel(EInt x, EInt y);
		inline EInt getHeight() const { return height; }
		inline EInt getWidth() const { return height; }

	private:
		EString		name;
		HBITMAP		hBitmap;
		BITMAP		bitmap;
		HDC			bitmapHDC;

	public:
		EColor		*pixels;
		EInt		pitch;
		EBool		valid;
	};




}