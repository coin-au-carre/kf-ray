/*
 * Copyright 1993-2009 NVIDIA Corporation.  All rights reserved.
 *
 * NOTICE TO USER:
 *
 * This source code is subject to NVIDIA ownership rights under U.S. and
 * international Copyright laws.  Users and possessors of this source code
 * are hereby granted a nonexclusive, royalty-free license to use this code
 * in individual and commercial software.
 *
 * NVIDIA MAKES NO REPRESENTATION ABOUT THE SUITABILITY OF THIS SOURCE
 * CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR
 * IMPLIED WARRANTY OF ANY KIND.  NVIDIA DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOURCE CODE, INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS,  WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION,  ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OR PERFORMANCE OF THIS SOURCE CODE.
 *
 * U.S. Government End Users.   This source code is a "commercial item" as
 * that term is defined at  48 C.F.R. 2.101 (OCT 1995), consisting  of
 * "commercial computer  software"  and "commercial computer software
 * documentation" as such terms are  used in 48 C.F.R. 12.212 (SEPT 1995)
 * and is provided to the U.S. Government only as a commercial end item.
 * Consistent with 48 C.F.R.12.212 and 48 C.F.R. 227.7202-1 through
 * 227.7202-4 (JUNE 1995), all U.S. Government End Users acquire the
 * source code with only those rights set forth herein.
 *
 * Any use of this source code in individual and commercial software must
 * include, in the user documentation and internal comments to the code,
 * the above Disclaimer and U.S. Government End Users Notice.
 */




#include "SimpleCudaGLWindow.h"

SimpleCudaGLWindow::SimpleCudaGLWindow(void) : 
	hDC(NULL),
	hGLRC(NULL),
	hInstance(NULL),
	hWnd(NULL),
	ImgWidth(0),
	ImgHeight(0),
    IsCreated(false)
{
}

SimpleCudaGLWindow::~SimpleCudaGLWindow(void)
{
	// just in case, close it
    if(IsCreated)
    {
	    CloseCudaGLWindow();
    }
}


bool SimpleCudaGLWindow::CreateCudaGLWindow(int left, int top, int width, int height, const char * title)
{
	
    try
    {
	    WNDCLASSEX	wc;						// Windows Class Structure
	    DWORD		dwExStyle;				// Window Extended Style
	    DWORD		dwStyle;				// Window Style
	    RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
     
    	
	    ///// STEP 1:  We need to create a standard Win32 Window

	    hInstance = GetModuleHandle(NULL);	// Need a handle to this process instance
    		
	    // Create the window class
	    wc.cbSize			= sizeof(WNDCLASSEX); 
	    wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	    wc.lpfnWndProc		= (WNDPROC) StaticWndProc;			    // WndProc Handles Messages, we'll pass a static version, which will receive a 'this' pointer
	    wc.cbClsExtra		= 0;									// No Extra Window Data
	    wc.cbWndExtra		= 0;									// No Extra Window Data
	    wc.hInstance		= hInstance;							// Set The Instance
	    wc.hIcon			= NULL;									// Load The Default Icon
	    wc.hIconSm		    = NULL; 
	    wc.hCursor			= LoadCursor(hInstance, IDC_ARROW);		// Load The Arrow Pointer
	    wc.hbrBackground	= NULL;									// No Background Required For GL
	    wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	    wc.lpszClassName	= "SimpleCudaGLWindow";						// Set The Class Name

	    // register the window class
	    if (!RegisterClassEx(&wc)) throw;
		    
    	
	    // Set the windows styles
	    dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	    dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style

	    // compute the window rect
	    WindowRect.left=left;							// Set Left Value To the defined window position
	    WindowRect.right=left+width;					// Set Right Value To Requested Width
	    WindowRect.top=top;								// Set Top Value To teh defined window position
	    WindowRect.bottom=top + height;					// Set Bottom Value To Requested Height
	    AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size
    		
	    // Call the windows function to create the window.  The 
	    hWnd = CreateWindowEx(	dwExStyle,									// Extended Style For The Window
							    "SimpleCudaGLWindow",					// Class Name
							    title,								// Window Title
							    dwStyle |							// Defined Window Style
							    WS_CLIPSIBLINGS |					// Required Window Style
							    WS_CLIPCHILDREN,					// Required Window Style
							    WindowRect.left,					// Window Position
							    WindowRect.top,						// 
							    WindowRect.right-WindowRect.left,	// Calculate Window Width
							    WindowRect.bottom-WindowRect.top,	// Calculate Window Height
							    NULL,								// No Parent Window
							    NULL,								// No Menu
							    NULL,								// Instance
							    this);								// pass a parameter to this class to the window proc so we can redraw it.
	    
        // Check if the window is created
	    if(hWnd == NULL) throw;
	  
	    // Get the windows device context
	    if (!(hDC=GetDC(hWnd)))	throw;					
	  
    	
	    ///// STEP 2: Now we need to create an OpenGL context for this window

	    // We need a pixel format descriptor.  A PFD tells how OpenGL draws
	    static	PIXELFORMATDESCRIPTOR pfd=				
	    {
		    sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		    1,											// Version Number
		    PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		    PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		    PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		    PFD_TYPE_RGBA,								// Request An RGBA Format
		    8,										    // Select Our Color Depth
		    0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		    0,											// No Alpha Buffer
		    0,											// Shift Bit Ignored
		    0,											// No Accumulation Buffer
		    0, 0, 0, 0,									// Accumulation Bits Ignored
		    16,											// 16Bit Z-Buffer (Depth Buffer)  
		    0,											// No Stencil Buffer
		    0,											// No Auxiliary Buffer
		    PFD_MAIN_PLANE,								// Main Drawing Layer
		    0,											// Reserved
		    0, 0, 0										// Layer Masks Ignored
	    };
    	
	    GLuint PixelFormat;			
	    // create the pixel pixel format descriptor
	    if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	 throw;
	       	
	    //  set the pixel format descriptor
	    if(!SetPixelFormat(hDC,PixelFormat,&pfd)) throw;	
	    
	    // Create a wGL rendering context
	    if (!(hGLRC=wglCreateContext(hDC))) throw;
	    
	    //  Activate the rendering context
	    if(!wglMakeCurrent(hDC,hGLRC)) throw;	

        // Make sure we have GL extension support and at least OpenGL 2.0 (certainly will on CUDA GPUs)
        glewInit();	
        if (! glewIsSupported("GL_VERSION_2_0 " "GL_ARB_pixel_buffer_object " "GL_EXT_framebuffer_object ")) 
            throw;

        //  Set some basic OpenGL options and put us in orthogonal mode
        glDisable(GL_DEPTH_TEST);
        glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	    glLoadIdentity();	
	    glOrtho(0,1,0,1,-1,1);
    	
	    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

	    glEnable(GL_TEXTURE_2D);
        glClearColor( 0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        // Set the GL drawing area to be the full window
        glViewport(0, 0, width, height);

        // Now check if there were any OpenGL Errors
        if(glGetError() != GL_NO_ERROR) throw;

        // Finally, show the window
        ShowWindow(hWnd,SW_SHOW);
        SetFocus(hWnd);
	    SetForegroundWindow(hWnd);	

        IsCreated = true;
	    // if we made it this far everything should be OK.
	    return true;
    }
    catch (...)
    {
        // something went wrong
        CloseCudaGLWindow();
        return(false);
    }
}

void SimpleCudaGLWindow::CloseCudaGLWindow()
{
    // Unregister the buffer from CUDA
    cudaGLUnregisterBufferObject(bufferID);

	// delete the buffer & texture
	if(glIsBuffer(bufferID))
		glDeleteBuffers(1,&bufferID);
	if(glIsTexture(textureID))
		glDeleteTextures(1,&textureID);
	// Delete the OpenGL Context
	if(hGLRC)
	{	wglMakeCurrent(NULL,NULL);
		wglDeleteContext(hGLRC);
	}
	// Release the windows device context
	if(hDC && hWnd) ReleaseDC(hWnd,hDC);
	// Close the window
	if(hWnd) DestroyWindow(hWnd);
	// And unregister the windows class
	if(hInstance) UnregisterClass("SimpleCudaGLWindow",hInstance);

	// Set our global parameters to NULL so we can use another window
	hGLRC = NULL;
	hDC = NULL;
	hWnd = NULL;
	hInstance = NULL;	
	ImgWidth = 0;
	ImgHeight = 0;
    IsCreated = false;
}

bool SimpleCudaGLWindow::DrawImage(unsigned char * pCudaImageMem, int width, int height, int pitch, bool color)
{
    try
    {
        // Make this the current GL Context (in case there are many windows)
        wglMakeCurrent(hDC,hGLRC);

        // Make sure we have buffers & textures, and that they are the correct size, otherwise allocate new ones
        if(!glIsBuffer(bufferID) || !glIsTexture(textureID) || width != ImgWidth || height != ImgHeight || color != ImgColor)
            SetImageBufferSize(width, height, color);
       
        ///// STEP 1, copy the data from CUDA memory into a GL buffer

        // Map the GL buffer to cuda memory space
        void * GLtemp;
        cudaError_t c_err;
	    c_err = cudaGLMapBufferObject(&GLtemp, bufferID);
        if(c_err != cudaSuccess) throw;

        // Copy the data from CUDA's memory to the buffer memory
        // Note: This copy is not the most ideal for performance, but keeps our example more simple
        //       In an optimized configuration one would allocate GL buffers and then map them to CUDA as the output memory
        //       for any image processing, then unmap them.  We make a copy instead, which completely isolates the CUDA example from
        //       OpenGL code.  
        c_err = cudaMemcpy2D(GLtemp,                        // the destination
                             ImgWidth * (ImgColor ? 4 : 1),    // width of each row of data to be copies, in bytes
                             (void*)pCudaImageMem,          // source of the copy
                             pitch,                         // source data pitch
                             ImgWidth * (ImgColor ? 4 : 1),    // width of each row of data to be copied, in bytes
                             ImgHeight,                     // number of rows to copy
                             cudaMemcpyDeviceToDevice);     // the copy is from one GPU memory location to another

        if(c_err != cudaSuccess) throw;
        cudaGLUnmapBufferObject(bufferID);      // unmap the buffer object so GL has it back

        ///// STEP 2, Create an OpenGL texture from the data stored in the OpenGL buffer

        glBindTexture( GL_TEXTURE_2D, textureID);          // Select our Image Texture
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, bufferID);   // And Bind the OpenGL Buffer for the pixel data 
        
        // the glTexSubImage command copies the data from the bound GL buffer into the texture
        glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, ImgWidth, ImgHeight, ImgColor ? GL_RGBA : GL_LUMINANCE, GL_UNSIGNED_BYTE, 0); 
        
        // done with the GBuffer
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, NULL);

        // A quick error check
        if(glGetError() != GL_NO_ERROR) throw;



        //// STEP 3, We'll draw a quad on the screen, with the texture we just created.
        // This code is in the DrawTexture function and is also called whenever we need to repaint the window
        if(!DrawTexture()) throw;
       
        // Everything's OK.  return
        return true;
    }
    catch(...)
    {
        return false;
    }
       
}

bool SimpleCudaGLWindow::DrawTexture()
{
    try
    {
        if(!glIsTexture(textureID)) return false;

        // bind the texture
        glBindTexture( GL_TEXTURE_2D, textureID);

        // Set the texture interopolation parameters
        glEnable(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

        // Now draw a quad.  We won't attempt any scaling in this simple example.  If the window is a different aspect ratio then the image, it will be distorted
              
        glBegin(GL_QUADS);
            glTexCoord2f( 0, 0);
            glVertex3f(0,0,0);

            glTexCoord2f(0,1.0f);
            glVertex3f(0,1.0f,0);

            glTexCoord2f(1.0f,1.0f);
            glVertex3f(1.0f,1.0f,0);
            
            glTexCoord2f(1.0f,0);
            glVertex3f(1.0f,0,0);
        glEnd();

        // Done with the texture 
        glBindTexture(GL_TEXTURE_2D ,0);


        // Finally swap the back framebuffer and the front framebuffer actually creating the draw
        SwapBuffers(hDC);
         // A quick error check
        if(glGetError() != GL_NO_ERROR) throw;

        return true;
    }
    catch(...)
    {
        return false;
    }
}





// This fuction allocates the GLbuffer & GLtexture needed to draw an image
// If a buffer already exists, it is first freed
// width & height are the size of the image in pixels, color indicates if the 
// image is RGBA (8-bit/channel) or 8-bit Grayscale
bool SimpleCudaGLWindow::SetImageBufferSize(int width, int height, bool color)
{
    try
    {
        // Make this the current GL Context (in case there are many windows)
        wglMakeCurrent(hDC,hGLRC);

        // If the buffers exist, delete them.
	    if(glIsBuffer(bufferID))
		    glDeleteBuffers(1,&bufferID);
	    if(glIsTexture(textureID))
		    glDeleteTextures(1,&textureID);
       
        // Create a texture for drawing the image
        glGenTextures(1,&textureID);
        glBindTexture( GL_TEXTURE_2D, textureID);  
       
        // glTexImage2D actually allocates the texture data according to the desired format.  
        // Since we are not filling the texture right now, the data pointer parameter is null
        GLuint tex_format = color ? GL_RGBA : GL_LUMINANCE;
        glTexImage2D( GL_TEXTURE_2D, 0, tex_format, width, height, 0, tex_format, GL_UNSIGNED_BYTE, NULL);
        
        // Quick error check
        if(glGetError() != GL_NO_ERROR) throw;

        // Now we need to generate an OpenGL buffer object we can share with CUDA
        glGenBuffers(1,&bufferID);
        glBindBuffer( GL_PIXEL_UNPACK_BUFFER, bufferID); 	
	    
        // Now actually allocate the data
        glBufferData( GL_PIXEL_UNPACK_BUFFER, width * height * (color ? 4 : 1), NULL, GL_DYNAMIC_DRAW);       
         
        // Quick error check
        if(glGetError() != GL_NO_ERROR) throw;

        // Now register the buffer so CUDA can use it
        cudaError_t c_err = cudaGLRegisterBufferObject(bufferID);
        if(c_err != cudaSuccess) throw;

        // Set the class member variables indicating the buffer's size
        ImgWidth = width;
        ImgHeight = height;
        ImgColor = color;

        // Everything is OK!
        return true;


    }
    catch (...)
    {
        // Something went wrong, free the memory
        if(glIsBuffer(bufferID))
        {
            cudaGLUnregisterBufferObject(bufferID);
		    glDeleteBuffers(1,&bufferID);
        }
	    if(glIsTexture(textureID))
		    glDeleteTextures(1,&textureID);
        
        return false;
    }
}








// This is the static windows callback which is first called.  It must be static. 
// During create, we had set the user parameter of the window to contain a pointer to the instance of 
// the GLImageWindow class corresponding
// to it.  We call the WndProc for the specific instance after that.
LRESULT CALLBACK SimpleCudaGLWindow::StaticWndProc(HWND hWnd_in, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    SimpleCudaGLWindow* pParent;

   // Get pointer to window
   if(uMsg == WM_CREATE)
   {
      pParent = (SimpleCudaGLWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams;
      SetWindowLongPtr(hWnd_in,GWL_USERDATA,(LONG_PTR)pParent);
   }
   else
   {
      pParent = (SimpleCudaGLWindow*)GetWindowLongPtr(hWnd_in,GWL_USERDATA);
      if(!pParent) return DefWindowProc(hWnd_in,uMsg,wParam,lParam);
   }
   return pParent->WndProc(uMsg,wParam,lParam);
}


// This is the  WndProc for the specific instance of the class.
LRESULT  SimpleCudaGLWindow::WndProc(UINT	uMsg, WPARAM	wParam,	LPARAM	lParam)	
{
	switch (uMsg)									// Check For Windows Messages
	{
				
		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{            
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);
            // Reset the current glviewport to the new size
            wglMakeCurrent(hDC,hGLRC);
            glViewport(0, 0, width, height);
            DrawTexture();
			return 0;								
		}
     
        case WM_PAINT:
        {
            wglMakeCurrent(hDC,hGLRC);  // make sure we are current
            DrawTexture();              // and redraw
            return 0;
        }
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

// This function checks and processes any windows messages pending.  This must be called to make the window
// repsonsive.  This is a simple example, so there is no multithreading between the main app and the window
int SimpleCudaGLWindow::CheckWindowsMessages()
{
	MSG		msg;
	while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
	{
		if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
		{
			return(-1);							// this means quit
		}
		else									// If Not, Deal With Window Messages
		{
			TranslateMessage(&msg);				// Translate The Message
			DispatchMessage(&msg);				// Dispatch The Message
		}
	}
	return(0);
}