#include <iostream>

#include<Windows.h>
#include <windowsx.h>

#include <GL/glew.h>
#include <GL/wglew.h>

using namespace std;

HWND window;
HDC dc;
HGLRC context;

LRESULT CALLBACK
_fake_window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_KEYDOWN:
			if(wparam == VK_ESCAPE)
			{
				PostQuitMessage(0);
				return 0;
			}
			break;

		default:
			break;
	}

	return DefWindowProcA(hwnd, msg, wparam, lparam);
}


void
init_window()
{
	WNDCLASSEXA wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = _fake_window_proc;
	wc.hInstance = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass";

	RegisterClassExA(&wc);

	window = CreateWindowExA(NULL,
							 "WindowClass",
							 "Totoroooo",
							 WS_OVERLAPPEDWINDOW,
							 100,
							 0,
							 800,
							 600,
							 NULL,
							 NULL,
							 NULL,
							 NULL);

	ShowWindow(window, SW_SHOW);
	SetForegroundWindow(window);
	SetFocus(window);

	dc = GetDC(window);

	//init opengl context
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(pfd));

	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_STEREO_DONTCARE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int index = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, index, &pfd);

	HGLRC fake_ctx = wglCreateContext(dc);
	wglMakeCurrent(dc, fake_ctx);
	glewInit();

	const int pixel_attribs[] = {
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
		WGL_COLOR_BITS_ARB, 32,
		WGL_ALPHA_BITS_ARB, 8,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
		WGL_SAMPLES_ARB, 2,
		0, 0
	};

	UINT num_formats;
	wglChoosePixelFormatARB(dc, pixel_attribs, NULL, 1, &index, &num_formats);
	
	PIXELFORMATDESCRIPTOR pixel_format{};
	DescribePixelFormat(dc, index, sizeof(pixel_format), &pixel_format);
	SetPixelFormat(dc, index, &pixel_format);

	const int major_min = 4, minor_min = 0;
	int context_attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, major_min,
		WGL_CONTEXT_MINOR_VERSION_ARB, minor_min,
		//WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
		0
	};

	context = wglCreateContextAttribsARB(dc, 0, context_attribs);

	wglMakeCurrent(dc, context);

	glEnable(GL_DEPTH_TEST);

	wglDeleteContext(fake_ctx);
}

void draw()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
		glVertex2f(-1.0f, -1.0f);
		glVertex2f(0.0f, 1.0f);
		glVertex2f(1.0f, -1.0f);
	glEnd();
}

void main_loop()
{
	MSG msg;
	while(true)
	{
		if(PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
			if(msg.message == WM_QUIT)
				break;
		}

		draw();
		SwapBuffers(dc);
	}
}

int main()
{
    cout<<"Helooooooo"<<endl;
	init_window();
	main_loop();
    return 0;
}