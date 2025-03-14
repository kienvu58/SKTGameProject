#include <windows.h>
#include "esUtil.h"

// Main window procedure
LRESULT WINAPI ESWindowProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) 
{
   LRESULT  lRet = 1; 

   switch (uMsg) 
   { 
      case WM_CREATE:
         break;

      case WM_PAINT:
         {
            ESContext *esContext = reinterpret_cast<ESContext*>(LONG_PTR(GetWindowLongPtr ( hWnd, GWL_USERDATA )));
            
            if ( esContext && esContext->drawFunc )
               esContext->drawFunc ( esContext );
            
            ValidateRect( esContext->hWnd, nullptr );
         }
         break;

      case WM_DESTROY:
         PostQuitMessage(0);             
         break; 
      
	  case WM_KEYDOWN:
		  {
			  ESContext *esContext = reinterpret_cast<ESContext*>(LONG_PTR(GetWindowLongPtr ( hWnd, GWL_USERDATA )));

			  if ( esContext && esContext->keyFunc )
				  esContext->keyFunc ( esContext, static_cast<unsigned char>(wParam), true );
		  }
		  break;

	  case WM_KEYUP:
		  {
			  ESContext *esContext = reinterpret_cast<ESContext*>(LONG_PTR(GetWindowLongPtr ( hWnd, GWL_USERDATA )));

			  if ( esContext && esContext->keyFunc )
				  esContext->keyFunc ( esContext, static_cast<unsigned char>(wParam), false );
		  }
		  break;
	  case WM_MOUSEMOVE:
		  if (wParam & MK_LBUTTON)
		  {
			  POINTS      point;
			  ESContext *esContext = reinterpret_cast<ESContext*>(LONG_PTR(GetWindowLongPtr(hWnd, GWL_USERDATA)));

			  point = MAKEPOINTS(lParam);
			  if (esContext && esContext->mouseMoveFunc)
				  esContext->mouseMoveFunc(esContext, float(point.x), float(point.y));
		  }
		  break;
	  case WM_LBUTTONDOWN:
		  {
			  POINTS      point;
			  ESContext *esContext = reinterpret_cast<ESContext*>(LONG_PTR(GetWindowLongPtr(hWnd, GWL_USERDATA)));

			  point = MAKEPOINTS(lParam);
			  if (esContext && esContext->mouseDownFunc)
				  esContext->mouseDownFunc(esContext, float(point.x), float(point.y));
		  }
		  break;
	  case WM_LBUTTONUP:
	  {
		  POINTS     point;
		  ESContext *esContext = reinterpret_cast<ESContext*>(LONG_PTR(GetWindowLongPtr(hWnd, GWL_USERDATA)));

		  point = MAKEPOINTS(lParam);

		  if (esContext && esContext->mouseUpFunc)
			  esContext->mouseUpFunc(esContext, float(point.x), float(point.y));
	  }
	  break;
	  default: 
		 lRet = DefWindowProc (hWnd, uMsg, wParam, lParam); 
		 break; 
   } 

   return lRet; 
}

//      Create Win32 instance and window
GLboolean WinCreate ( ESContext *esContext, const char *title )
{
   WNDCLASS wndclass = {0}; 
   DWORD    wStyle;
   RECT     windowRect;
   HINSTANCE hInstance = GetModuleHandle(nullptr);


   wndclass.style         = CS_OWNDC;
   wndclass.lpfnWndProc   = WNDPROC(ESWindowProc); 
   wndclass.hInstance     = hInstance; 
   wndclass.hbrBackground = HBRUSH(GetStockObject(BLACK_BRUSH)); 
   wndclass.lpszClassName = "opengles2.0"; 

   if (!RegisterClass (&wndclass) ) 
      return FALSE; 

   wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;
   
   // Adjust the window rectangle so that the client area has
   // the correct number of pixels
   windowRect.left = 0;
   windowRect.top = 0;
   windowRect.right = esContext->width;
   windowRect.bottom = esContext->height;

   AdjustWindowRect ( &windowRect, wStyle, FALSE );

   esContext->hWnd = CreateWindow(
                         "opengles2.0",
                         title,
                         wStyle,
                         0,
                         0,
                         windowRect.right - windowRect.left,
                         windowRect.bottom - windowRect.top,
                         NULL,
                         NULL,
                         hInstance,
                         NULL);

   // Set the ESContext* to the GWL_USERDATA so that it is available to the 
   // ESWindowProc
   SetWindowLongPtr (  esContext->hWnd, GWL_USERDATA, LONG(LONG_PTR(esContext)) );

   if ( esContext->hWnd == nullptr )
      return GL_FALSE;

   ShowWindow ( esContext->hWnd, TRUE );

   return GL_TRUE;
}



//      Start main windows loop
void WinLoop ( ESContext *esContext )
{
   MSG msg = { nullptr };
   int done = 0;
   DWORD lastTime = GetTickCount();
   
   while (!done)
   {
      int gotMsg = (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0);
      DWORD curTime = GetTickCount();
      float deltaTime = float(curTime - lastTime) / 1000.0f;
      lastTime = curTime;

      if ( gotMsg )
      {
         if (msg.message==WM_QUIT)
         {
             done=1; 
         }
         else
         {
             TranslateMessage(&msg); 
             DispatchMessage(&msg); 
         }
      }
      else
         SendMessage( esContext->hWnd, WM_PAINT, 0, 0 );

      // Call update function if registered
      if ( esContext->updateFunc != nullptr )
         esContext->updateFunc ( esContext, deltaTime );
   }
}
