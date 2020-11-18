#include <cstdlib>
#include "defs.h"
#include <axl.glw/wglext.hpp>
#include <axl.gl/View.hpp>
#include <axl.gl/KeyMap.hpp>
#include "ViewData.hpp"

namespace axl {
namespace gl {
using namespace axl::math;
/////////
// View

static bool _cursors_loaded = false;
static HCURSOR _hcur_arrow = NULL;
static HCURSOR _hcur_cross = NULL;
static HCURSOR _hcur_hand = NULL;
static HCURSOR _hcur_wait = NULL;
static HCURSOR _hcur_help = NULL;
static HCURSOR _hcur_ibeam = NULL;
static HCURSOR _hcur_no = NULL;
static HBRUSH _hbrush_black = NULL;


LRESULT CALLBACK MWindowProc(HWND, UINT, WPARAM, LPARAM);

View::View(const axl::utils::WString& title_, const axl::math::Vec2<int>& position_, const axl::math::Vec2<int>& size_, const Cursor& cursor_) :
	position(m_position),
	size(m_size),
	title(m_title),
	config(m_config),
	cursor(m_cursor),
	visiblity(m_visiblity),
	is_paused(m_is_paused),
	pointers(m_pointers),
	reserved(m_reserved),
	m_position(position_),
	m_size(size_),
	m_title(title_),
	m_config(View::Config::Default),
	m_cursor(cursor_),
	m_visiblity(View::VS_HIDDEN),
	m_is_paused(false),
	m_pointers(),
	m_reserved((void*)calloc(1, sizeof(ViewData)))
{
	for(int i=0; i<MAX_POINTERS; ++i) m_pointers[i] = false;
	setCursor(m_cursor);
	if(m_reserved)
	{
		((ViewData*)m_reserved)->hinst = GetModuleHandleW(0);
	}
}

View::~View()
{
	this->destroy();
	if(m_reserved)
	{
		free(m_reserved);
		m_reserved = (void*)0;
	}
}

bool View::isValid() const
{
	return (m_reserved && ((ViewData*)m_reserved)->hwnd && ((ViewData*)m_reserved)->hdc);
}

bool View::create(bool recreate, const Config* configs_, int configs_count_)
{
	if(!_cursors_loaded) // load cursors
	{
		_hcur_arrow = LoadCursor(NULL, IDC_ARROW);
		_hcur_cross = LoadCursor(NULL, IDC_CROSS);
		_hcur_hand = LoadCursor(NULL, IDC_HAND);
		_hcur_wait = LoadCursor(NULL, IDC_WAIT);
		_hcur_help = LoadCursor(NULL, IDC_HELP);
		_hcur_ibeam = LoadCursor(NULL, IDC_IBEAM);
		_hcur_no = LoadCursor(NULL, IDC_NO);
		_cursors_loaded = true;
	}
	if(!_hbrush_black)
		_hbrush_black = CreateSolidBrush(RGB(0,0,0));
	if(!m_reserved) m_reserved = (void*)calloc(1, sizeof(ViewData));
	if(m_reserved)
	{
		if(!recreate)
		{
			if(((ViewData*)m_reserved)->hwnd && ((ViewData*)m_reserved)->hdc) return true;
			if(((ViewData*)m_reserved)->hwnd && !((ViewData*)m_reserved)->hdc)
			{
				((ViewData*)m_reserved)->hdc = GetDC(((ViewData*)m_reserved)->hwnd);
				if(((ViewData*)m_reserved)->hdc) return true;
			};
		}
		else
		{
			if(m_reserved && ((ViewData*)m_reserved)->hwnd)
			{
				ReleaseDC(((ViewData*)m_reserved)->hwnd, ((ViewData*)m_reserved)->hdc);
				DestroyWindow(((ViewData*)m_reserved)->hwnd);
			}
		}
		axl::utils::WString class_name(L"AXL.GLW.VIEW.");
		class_name += m_title.substring(12);
		DWORD style = WS_OVERLAPPEDWINDOW;
		HINSTANCE hinst = (HINSTANCE)GetModuleHandleW(0);
		HWND hwnd = NULL;
		HDC hdc = NULL;
		WNDCLASSEXW wc;
		ZeroMemory(&wc, sizeof(WNDCLASSEXW));
		wc.cbSize = sizeof(WNDCLASSEXW);
		wc.hInstance = hinst;
		wc.lpszClassName = class_name.cwstr();
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = MWindowProc;
		wc.hbrBackground = (HBRUSH)_hbrush_black;
		if(RegisterClassExW(&wc))
		{
			RECT rc = {0, 0, m_size.x, m_size.y};
			AdjustWindowRect(&rc, style, FALSE);
			hwnd = CreateWindowExW(0, class_name.cwstr(), m_title.cwstr(), style, m_position.x+rc.left, m_position.y+rc.top,
				rc.right-rc.left, rc.bottom-rc.top, NULL, NULL, hinst, NULL);
			if(hwnd)
			{
				SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)this);
				hdc = GetDC(hwnd);
				SendMessageW(hwnd, WM_USER+1, 0, (LPARAM)this);
			}
		}
		((ViewData*)m_reserved)->hinst = hinst;
		((ViewData*)m_reserved)->hwnd = hwnd;
		((ViewData*)m_reserved)->hdc = hdc;
		((ViewData*)m_reserved)->style = style;
		if(!((ViewData*)m_reserved)->hcursor) setCursor(m_cursor);
		if(((ViewData*)m_reserved)->hwnd)
		{
			if(((ViewData*)m_reserved)->hicon_small)
			{
				SendMessageW(((ViewData*)m_reserved)->hwnd, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)((ViewData*)m_reserved)->hicon_small);
			}
			if(((ViewData*)m_reserved)->hicon_big)
			{
				SendMessageW(((ViewData*)m_reserved)->hwnd, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)((ViewData*)m_reserved)->hicon_big);
			}
		}
		if(isValid())
		{
			axl::glw::wglext::init(true);
			// set the pixelformat
			const View::Config *config;
			BOOL set = FALSE;
			for(int i=0; i<configs_count_+1; ++i)
			{
				if(i<configs_count_) config = &configs_[i];
				else config = &Config::Default;
				if(axl::glw::wglext::WGL_ARB_pixel_format)
				{
					UINT num_formats;
					const UINT max_formats = 32;
					int formats[max_formats];
					int pixel_type;
					switch(config->pixel_type)
					{
						default:
						case View::PT_RGBA: pixel_type = axl::glw::wglext::WGL_TYPE_RGBA_ARB; break;
						case View::PT_RGBA_FLOAT: pixel_type = axl::glw::wglext::WGL_TYPE_RGBA_FLOAT_ARB; break;
						case View::PT_COLORINDEX: pixel_type = axl::glw::wglext::WGL_TYPE_COLORINDEX_ARB; break;
					}
					int attribs[] = {
						axl::glw::wglext::WGL_DRAW_TO_WINDOW_ARB, axl::glw::gl::GL_TRUE,
						axl::glw::wglext::WGL_SUPPORT_OPENGL_ARB, axl::glw::gl::GL_TRUE,
						axl::glw::wglext::WGL_STEREO_ARB, !config->stereo ? axl::glw::gl::GL_FALSE : axl::glw::gl::GL_TRUE,
						axl::glw::wglext::WGL_ACCELERATION_ARB, (int)axl::glw::wglext::WGL_FULL_ACCELERATION_ARB,
						axl::glw::wglext::WGL_PIXEL_TYPE_ARB, pixel_type,
						axl::glw::wglext::WGL_COLOR_BITS_ARB, config->bits_color,
						axl::glw::wglext::WGL_RED_BITS_ARB, config->bits_red,
						axl::glw::wglext::WGL_GREEN_BITS_ARB, config->bits_green,
						axl::glw::wglext::WGL_BLUE_BITS_ARB, config->bits_blue,
						axl::glw::wglext::WGL_ALPHA_BITS_ARB, config->bits_alpha,
						axl::glw::wglext::WGL_DEPTH_BITS_ARB, config->bits_depth,
						axl::glw::wglext::WGL_STENCIL_BITS_ARB, config->bits_stencil,
						axl::glw::wglext::WGL_ACCUM_BITS_ARB, config->bits_accum,
						axl::glw::wglext::WGL_ACCUM_RED_BITS_ARB, config->bits_red_accum,
						axl::glw::wglext::WGL_ACCUM_GREEN_BITS_ARB, config->bits_green_accum,
						axl::glw::wglext::WGL_ACCUM_BLUE_BITS_ARB, config->bits_blue_accum,
						axl::glw::wglext::WGL_ACCUM_ALPHA_BITS_ARB, config->bits_alpha_accum,
						axl::glw::wglext::WGL_DOUBLE_BUFFER_ARB, !config->double_buffered ? axl::glw::gl::GL_FALSE : axl::glw::gl::GL_TRUE,
						axl::glw::wglext::WGL_SAMPLE_BUFFERS_ARB, config->samples > 0 ? axl::glw::gl::GL_TRUE : axl::glw::gl::GL_FALSE,
						axl::glw::wglext::WGL_SAMPLES_ARB, config->samples,
						0
					};
					if(FALSE != axl::glw::wglext::wglChoosePixelFormatARB(hdc, attribs, NULL, max_formats, formats, &num_formats))
					{
						if(num_formats > 0)
						{
							PIXELFORMATDESCRIPTOR pfd;
							for(int i=0; i<num_formats; ++i)
							{
								DescribePixelFormat(hdc, formats[i], sizeof(pfd), &pfd);
								if(FALSE != (set = SetPixelFormat(hdc, formats[i], &pfd))) break;
							}
						}
					}
					else return false;
				}
				else if(config->pixel_type != View::PT_RGBA_FLOAT)
				{
					BYTE pixel_type;
					switch(config->pixel_type)
					{
						default:
						case View::PT_RGBA: pixel_type = PFD_TYPE_RGBA; break;
						case View::PT_COLORINDEX: pixel_type = PFD_TYPE_COLORINDEX; break;
					}
					PIXELFORMATDESCRIPTOR pfd;
					ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
					pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
					pfd.nVersion = 1;
					pfd.dwFlags = PFD_GENERIC_ACCELERATED|PFD_SUPPORT_OPENGL|PFD_DRAW_TO_WINDOW|(!config->double_buffered?0:PFD_DOUBLEBUFFER)|(!config->stereo?0:PFD_STEREO);
					pfd.iPixelType = pixel_type;
					pfd.cColorBits = config->bits_color;
					pfd.cRedBits = config->bits_red;
					pfd.cGreenBits = config->bits_green;
					pfd.cBlueBits = config->bits_blue;
					pfd.cAlphaBits = config->bits_alpha;
					pfd.cDepthBits = config->bits_depth;
					pfd.cStencilBits = config->bits_stencil;
					pfd.cAccumBits = config->bits_accum;
					pfd.cAccumRedBits = config->bits_red_accum;
					pfd.cAccumGreenBits = config->bits_green_accum;
					pfd.cAccumBlueBits = config->bits_blue_accum;
					pfd.cAccumAlphaBits = config->bits_alpha_accum;
					set = SetPixelFormat(hdc, ChoosePixelFormat(hdc, &pfd), &pfd);
				}
				if(set != FALSE)
				{
					m_config = *config;
					break;
				}
			}
			return set != FALSE;
		}
	}
	return false;
}

void View::destroy()
{
	if(m_reserved && ((ViewData*)m_reserved)->hwnd)
	{
		ReleaseDC(((ViewData*)m_reserved)->hwnd, ((ViewData*)m_reserved)->hdc);
		DestroyWindow(((ViewData*)m_reserved)->hwnd);
	}
}

void View::cleanup()
{
	if(_hbrush_black)
	{
		DeleteObject(_hbrush_black);
		_hbrush_black = NULL;
	}
	axl::glw::wglext::cleanup();
}

bool View::setPosition(const axl::math::Vec2<int>& position_)
{
	if(SetWindowPos(((ViewData*)m_reserved)->hwnd, NULL, position_.x, position_.y, 0, 0, SWP_NOSIZE|SWP_NOREDRAW|SWP_NOZORDER) != FALSE)
	{
		this->m_position = position_;
		return true;
	}
	return false;
}

bool View::setSize(const axl::math::Vec2<int>& size_)
{
	if(SetWindowPos(((ViewData*)m_reserved)->hwnd, NULL, 0, 0, size_.x, size_.y, SWP_NOMOVE|SWP_FRAMECHANGED|SWP_NOZORDER) != FALSE)
	{
		this->m_size = size_;
		return true;
	}
	return false;
}

bool View::setTitle(const axl::utils::WString& title_)
{
	if(SetWindowTextW(((ViewData*)m_reserved)->hwnd, title_.cwstr()) != FALSE)
	{
		this->m_title = title_;
		return true;
	}
	return false;
}

bool View::setCursor(const Cursor& cursor_)
{
	m_cursor = cursor_;
	HCURSOR hcursor = NULL;
	if(m_cursor == CUR_CUSTOM)
	{
		hcursor = ((ViewData*)m_reserved)->hcursor_custom;
	}
	else
	{
		switch (m_cursor)
		{
			case CUR_ARROW: hcursor = _hcur_arrow; break;
			case CUR_CROSS: hcursor = _hcur_cross; break;
			case CUR_HAND: hcursor = _hcur_hand; break;
			case CUR_WAIT: hcursor = _hcur_wait; break;
			case CUR_HELP: hcursor = _hcur_help; break;
			case CUR_IBEAM: hcursor = _hcur_ibeam; break;
			case CUR_NO: hcursor = _hcur_no; break;
			case CUR_NONE:
				hcursor = NULL;
				m_cursor = CUR_NONE;
				break;
			default: return false;
		}
	}
	((ViewData*)m_reserved)->hcursor = hcursor;
	SetCursor(hcursor);
	return true;
}

bool View::setCursorFromResource(int res_id)
{
	m_cursor = CUR_CUSTOM;
	HCURSOR hcursor = LoadCursorW(((ViewData*)m_reserved)->hinst, MAKEINTRESOURCEW(res_id));
	if(!hcursor) return false;
	((ViewData*)m_reserved)->hcursor = hcursor;
	SetCursor(hcursor);
	return true;
}

bool View::setIcon(const axl::utils::WString& icon_file)
{
	HICON icon_small = (HICON)NULL;
	HICON icon_big = (HICON)NULL;
	if(!icon_file.isNull())
	{
		icon_small = (HICON)LoadImageW(NULL, icon_file.cwstr(), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
		icon_big = (HICON)LoadImageW(NULL, icon_file.cwstr(), IMAGE_ICON, 48, 48, LR_LOADFROMFILE);
		if(!icon_small) return false;
		if(!icon_big) icon_big = icon_small;
	}
	if(((ViewData*)m_reserved)->hwnd)
	{
		SendMessageW(((ViewData*)m_reserved)->hwnd, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)icon_small);
		SendMessageW(((ViewData*)m_reserved)->hwnd, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)icon_big);
	}
	((ViewData*)m_reserved)->hicon_small = icon_small;
	((ViewData*)m_reserved)->hicon_big = icon_big;
	return true;
}

bool View::setIconFromResource(int res_id)
{
	LPWSTR res_str = MAKEINTRESOURCEW(res_id);
	HICON icon_small = (HICON)LoadImageW(((ViewData*)m_reserved)->hinst, res_str, IMAGE_ICON, 32, 32, 0);
	HICON icon_big = (HICON)LoadImageW(((ViewData*)m_reserved)->hinst, res_str, IMAGE_ICON, 48, 48, 0);
	if(!icon_small) return false;
	if(!icon_big) icon_big = icon_small;
	if(((ViewData*)m_reserved)->hwnd)
	{
		SendMessageW(((ViewData*)m_reserved)->hwnd, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)icon_small);
		SendMessageW(((ViewData*)m_reserved)->hwnd, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)icon_big);
	}
	((ViewData*)m_reserved)->hicon_small = icon_small;
	((ViewData*)m_reserved)->hicon_big = icon_big;
	return true;
}

bool View::show(ShowMode show_mode)
{
	if(!((ViewData*)m_reserved)->hwnd) return false;
	switch (show_mode)
	{
		case View::SM_HIDE:
			switch(m_visiblity)
			{
				case View::VS_HIDDEN:
					return true;
				case View::VS_SHOWN:
				case View::VS_FULLSCREEN:
					ShowWindow(((ViewData*)m_reserved)->hwnd, SW_HIDE);
					break;
			}
			m_visiblity = View::VS_HIDDEN;
			break;
		case View::SM_SHOW:
			switch(m_visiblity)
			{
				case View::VS_HIDDEN:
					ShowWindow(((ViewData*)m_reserved)->hwnd, SW_NORMAL);
					break;
				case View::VS_SHOWN:
					return true;
				case View::VS_FULLSCREEN:
					{
						// restore the style and size
						SetWindowLongW(((ViewData*)m_reserved)->hwnd, GWL_STYLE, ((ViewData*)m_reserved)->style);
						if(SetWindowPos(((ViewData*)m_reserved)->hwnd, NULL, ((ViewData*)m_reserved)->prev_rect.left, ((ViewData*)m_reserved)->prev_rect.top, ((ViewData*)m_reserved)->prev_rect.right-((ViewData*)m_reserved)->prev_rect.left, ((ViewData*)m_reserved)->prev_rect.bottom-((ViewData*)m_reserved)->prev_rect.top, SWP_SHOWWINDOW))
						{
							m_visiblity = VS_SHOWN;
							return true;
						}
						else return false;
					}
					break;
			}
			m_visiblity = View::VS_SHOWN;
			break;
		case View::SM_FULLSCREEN:
			switch(m_visiblity)
			{
				case View::VS_SHOWN:
					//save the rect data
					GetWindowRect(((ViewData*)m_reserved)->hwnd, &((ViewData*)m_reserved)->prev_rect);
				case View::VS_HIDDEN:
					{
						// get the screen's size
						int screen_width = GetSystemMetrics(SM_CXSCREEN);
						int screen_height = GetSystemMetrics(SM_CYSCREEN);
						// set the window style and size
						SetWindowLongW(((ViewData*)m_reserved)->hwnd, GWL_STYLE, ((ViewData*)m_reserved)->style & ~(WS_CAPTION|WS_THICKFRAME|WS_SYSMENU));
						if(SetWindowPos(((ViewData*)m_reserved)->hwnd, NULL, 0, 0, screen_width, screen_height, SWP_SHOWWINDOW))
						{
							m_visiblity = View::VS_FULLSCREEN;
							return true;
						}
						else return false;
					}
					break;
				case View::VS_FULLSCREEN:
					return true;
			}
			m_visiblity = View::VS_FULLSCREEN;
			break;
	}
	return true;
}

bool View::setCursorPosition(const axl::math::Vec2<int>& pointer_position)
{
	return SetCursorPos(m_position.x + pointer_position.x, m_position.y + pointer_position.y) != FALSE;
}

bool View::swap() const
{
	return SwapBuffers(((ViewData*)m_reserved)->hdc) != FALSE;
}

///////////
/// Events

bool View::onCreate()
{
	return true;
}

void View::onDestroy()
{
	m_is_paused = false;
}

void View::onMove(int x, int y)
{
	this->m_position.set(x, y);
}

void View::onSize(int w,int h)
{
	this->m_size.set(w, h);
}

void View::onPause()
{
	this->m_is_paused = true;
}

void View::onResume()
{
	this->m_is_paused = false;
}

void View::onKey(KeyCode key_code, bool is_down)
{}

void View::onChar(char char_code)
{}

void View::onPointer(int index, int x, int y, bool is_down)
{
	if(index >= 0 && index < MAX_POINTERS)
		m_pointers[index] = is_down;
}

void View::onPointerMove(int index, int x, int y)
{
	HCURSOR hcursor = ((ViewData*)this->m_reserved)->hcursor;
	if(GetCursor() != hcursor)// && x >= 0 && y >= 0 && x <= m_size.x && y <= m_size.y)
	{
		SetCursor(hcursor);
	}
}

LRESULT CALLBACK MWindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	View* view = (View*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	UINT scancode = (lparam & 0x00ff0000) >> 16;
    int extended  = (lparam & 0x01000000) != 0;
	switch (message)
	{
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYDOWN:
		case WM_KEYUP:
			if(view)
			{
				bool is_down = (message == WM_KEYDOWN || message == WM_SYSKEYDOWN);
				switch(wparam)
				{
					case VK_CONTROL:
						view->onKey(MapPlatformKeyCode((int)wparam), is_down);
						view->onKey(MapPlatformKeyCode((int)(extended ? VK_RCONTROL : VK_LCONTROL)), is_down);
						break;
					case VK_SHIFT:
						view->onKey(MapPlatformKeyCode((int)wparam), is_down);
						view->onKey(MapPlatformKeyCode((int)(MapVirtualKeyW(scancode, MAPVK_VSC_TO_VK_EX))), (message == WM_KEYDOWN));
						break;
					case VK_MENU:
						view->onKey(axl::gl::KEY_ALT, is_down);
						view->onKey(MapPlatformKeyCode((int)(extended ? VK_RMENU : VK_LMENU)), is_down);
						break;
					case VK_LWIN:
					case VK_RWIN:
						view->onKey(axl::gl::KEY_CMD, is_down);
						view->onKey(MapPlatformKeyCode((int)wparam), is_down);
						break;
					default:
						view->onKey(MapPlatformKeyCode((int)wparam), is_down);
						break;
				}
			}
			break;
		case WM_CHAR:
			if(view)
			{
				view->onChar((char)wparam);
			}
			break;
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
			if(view)
			{
				SHORT x, y;
				x = (SHORT)LOWORD(lparam);
				y = (SHORT)HIWORD(lparam);
				view->onPointer(View::PB_LEFT_BUTTON, (int)x, (int)y, (message == WM_LBUTTONDOWN));
			}
			break;
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
			if(view)
			{
				SHORT x, y;
				x = (SHORT)LOWORD(lparam);
				y = (SHORT)HIWORD(lparam);
				view->onPointer(View::PB_RIGHT_BUTTON, (int)x, (int)y, (message == WM_RBUTTONDOWN));
			}
			break;
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
			if(view)
			{
				SHORT x, y;
				x = (SHORT)LOWORD(lparam);
				y = (SHORT)HIWORD(lparam);
				view->onPointer(View::PB_MIDDLE_BUTTON, (int)x, (int)y, (message == WM_MBUTTONDOWN));
			}
			break;
		case WM_MOUSEMOVE:
			if(view)
			{
				SHORT x, y;
				x = (SHORT)LOWORD(lparam);
				y = (SHORT)HIWORD(lparam);
				view->onPointerMove(0, (int)x, (int)y);
			}
			break;
			break;
		case WM_MOVE:
			if(view)
			{
				SHORT w, h;
				w = (SHORT)LOWORD(lparam);
				h = (SHORT)HIWORD(lparam);
				view->onMove((int)w, (int)h);
			}
			break;
		case WM_SIZE:
			if(view)
			{
				switch(wparam)
				{
					case SIZE_MINIMIZED:
						view->onPause();
						break;
					default:
						{
							SHORT w, h;
							if(view->is_paused) view->onResume();
							w = (SHORT)LOWORD(lparam);
							h = (SHORT)HIWORD(lparam);
							view->onSize((int)w, (int)h);
						}
						break;
				}
			}
			break;
		case WM_USER+1: // window created and configured
			if(view != (View*)lparam)
			{
				DestroyWindow(hwnd);
			}
			if(view)
			{
				if(!view->onCreate()) DestroyWindow(hwnd);
			}
			break;
		case WM_DESTROY:
			if(view && view->isValid())
			{
				view->onDestroy();
			}
			break;
		default:
			return DefWindowProcW(hwnd, message, wparam, lparam);
	}
	return 0;
}

View::Cursor View::DefaultCursor = View::CUR_ARROW;

//////////////////
// View::Config

View::Config::Config() :
	Config(View::Config::Default)
{}

View::Config::Config(long id_, PixelType pixel_type_, 
		char bits_color_, char bits_red_, char bits_green_, char bits_blue_, char bits_alpha_, 
		char bits_depth_, char bits_stencil_, 
		char bits_accum_, char bits_red_accum_, char bits_green_accum_, char bits_blue_accum_, char bits_alpha_accum_, 
		char samples_, bool double_buffered_, bool stereo_) :
	id(id_),
	pixel_type(pixel_type_),
	bits_color(bits_color_),
	bits_red(bits_red_),
	bits_green(bits_green_),
	bits_blue(bits_blue_),
	bits_alpha(bits_alpha_),
	bits_depth(bits_depth_),
	bits_stencil(bits_stencil_),
	bits_accum(bits_accum_),
	bits_red_accum(bits_red_accum_),
	bits_green_accum(bits_green_accum_),
	bits_blue_accum(bits_blue_accum_),
	bits_alpha_accum(bits_alpha_accum_),
	samples(samples_),
	double_buffered(double_buffered_),
	stereo(stereo_)
{}

View::Config::Config(const Config& config) :
	id(config.id),
	pixel_type(config.pixel_type),
	bits_color(config.bits_color),
	bits_red(config.bits_red),
	bits_green(config.bits_green),
	bits_blue(config.bits_blue),
	bits_alpha(config.bits_alpha),
	bits_depth(config.bits_depth),
	bits_stencil(config.bits_stencil),
	bits_accum(config.bits_accum),
	bits_red_accum(config.bits_red_accum),
	bits_green_accum(config.bits_green_accum),
	bits_blue_accum(config.bits_blue_accum),
	bits_alpha_accum(config.bits_alpha_accum),
	samples(config.samples),
	double_buffered(config.double_buffered),
	stereo(config.stereo)
{}

bool View::Config::operator==(const Config& rhs) const
{
	return	(
		pixel_type == rhs.pixel_type &&
		bits_color == rhs.bits_color &&
		bits_red == rhs.bits_red &&
		bits_green == rhs.bits_green &&
		bits_blue == rhs.bits_blue &&
		bits_alpha == rhs.bits_alpha &&
		bits_depth == rhs.bits_depth &&
		bits_stencil == rhs.bits_stencil &&
		bits_accum == rhs.bits_accum &&
		bits_red_accum == rhs.bits_red_accum &&
		bits_green_accum == rhs.bits_green_accum &&
		bits_blue_accum == rhs.bits_blue_accum &&
		bits_alpha_accum == rhs.bits_alpha_accum &&
		samples == rhs.samples &&
		double_buffered == rhs.double_buffered &&
		stereo == rhs.stereo
		);
}

bool View::Config::operator!=(const Config& rhs) const
{
	return	(
		pixel_type != rhs.pixel_type ||
		bits_color != rhs.bits_color ||
		bits_red != rhs.bits_red ||
		bits_green != rhs.bits_green ||
		bits_blue != rhs.bits_blue ||
		bits_alpha != rhs.bits_alpha ||
		bits_depth != rhs.bits_depth ||
		bits_stencil != rhs.bits_stencil ||
		bits_accum != rhs.bits_accum ||
		bits_red_accum != rhs.bits_red_accum ||
		bits_green_accum != rhs.bits_green_accum ||
		bits_blue_accum != rhs.bits_blue_accum ||
		bits_alpha_accum != rhs.bits_alpha_accum ||
		samples != rhs.samples ||
		double_buffered != rhs.double_buffered ||
		stereo != rhs.stereo
		);
}

View::Config View::Config::Default(
	0, // id
	View::PT_RGB, // pixel_type
	24, // bits_color
	8, // bits_red
	8, // bits_green
	8, // bits_blue
	0, // bits_alpha
	24, // bits_depth
	8, // bits_stencil
	0, // bits_accum
	0, // bits_red_accum
	0, // bits_green_accum
	0, // bits_blue_accum
	0, // bits_alpha_accum
	0, // samples
	false, // double_buffered
	false // stereo
);

const View::Config View::Config::Null(
	-1, // id
	View::PT_RGB, // pixel_type
	-1, // bits_color
	-1, // bits_red
	-1, // bits_green
	-1, // bits_blue
	-1, // bits_alpha
	-1, // bits_depth
	-1, // bits_stencil
	-1, // bits_accum
	-1, // bits_red_accum
	-1, // bits_green_accum
	-1, // bits_blue_accum
	-1, // bits_alpha_accum
	-1, // samples
	false, // double_buffered
	false // stereo
);

} // namespace axl.gl
} // namespace axl