#pragma once
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

namespace axl {
namespace gl {

typedef struct
{
	HINSTANCE hinst;
	HWND hwnd;
	HDC hdc;
	HICON hicon_small;
	HICON hicon_big;
	HCURSOR hcursor;
	HCURSOR hcursor_custom;
	RECT prev_rect;
	DWORD style;
} ViewData;

} // namespace axl.gl
} // namespace axl