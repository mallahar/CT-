#include <Windows.h>

///////////////////////////////
///////////////////////////////
// I hate globals, but to keep this simple, we'll have our image stuff be global
HDC         imageDC;        // the DC to hold our image
HBITMAP     imageBmp;       // the actual bitmap which contains the image (will be put in the DC)
HBITMAP     imageBmpOld;    // the DC's old bitmap (for cleanup)

const int   screenSize_X = 640;
const int   screenSize_Y = 480;

///////////////////////////////
///////////////////////////////
// Function to load the image into our DC so we can draw it to the screen
void loadImage(const char* pathname)
{
    imageDC = CreateCompatibleDC(NULL);     // create an offscreen DC

    imageBmp = (HBITMAP)LoadImageA(         // load the bitmap from a file
            NULL,                           // not loading from a module, so this is NULL
            pathname,                       // the path we're loading from
            IMAGE_BITMAP,                   // we are loading a bitmap
            0,0,                            // don't need to specify width/height
            LR_DEFAULTSIZE | LR_LOADFROMFILE// use the default bitmap size (whatever the file is), and load it from a file
            );

    imageBmpOld = (HBITMAP)SelectObject(imageDC,imageBmp);  // put the loaded image into our DC
}


///////////////////////////////
// Function to clean up
void cleanUpImage()
{
    SelectObject(imageDC,imageBmpOld);      // put the old bmp back in our DC
    DeleteObject(imageBmp);                 // delete the bmp we loaded
    DeleteDC(imageDC);                      // delete the DC we created
}

///////////////////////////////
///////////////////////////////
// The function to draw our image to the display (the given DC is the screen DC)
void drawImage(HDC screen)
{
    BitBlt(
        screen,         // tell it we want to draw to the screen
        0,0,            // as position 0,0 (upper-left corner)
        screenSize_X,   // width of the rect to draw
        screenSize_Y,   // height of the rect
        imageDC,        // the DC to get the rect from (our image DC)
        0,0,            // take it from position 0,0 in the image DC
        SRCCOPY         // tell it to do a pixel-by-pixel copy
        );
}


///////////////////////////////
///////////////////////////////
// A callback to handle Windows messages as they happen
LRESULT CALLBACK wndProc(HWND wnd,UINT msg,WPARAM w,LPARAM l)
{
    // what kind of message is this?
    switch(msg)
    {
        // we are interested in WM_PAINT, as that is how we draw
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC screen = BeginPaint(wnd,&ps);   // Get the screen DC
            drawImage(screen);                  // draw our image to our screen DC
            EndPaint(wnd,&ps);                  // clean up
        }break;

        // we are also interested in the WM_DESTROY message, as that lets us know when to close the window
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    // for everything else, let the default window message handler do its thing
    return DefWindowProc(wnd,msg,w,l);
}


///////////////////////////////
///////////////////////////////
// A function to create the window and get it set up
HWND createWindow(HINSTANCE inst)
{
    WNDCLASSEX wc = {0};        // create a WNDCLASSEX struct and zero it
    wc.cbSize =         sizeof(WNDCLASSEX);     // tell windows the size of this struct
    wc.hCursor =        LoadCursor(NULL,MAKEINTRESOURCE(IDC_ARROW));        // tell it to use the normal arrow cursor for this window
    wc.hInstance =      inst;                   // give it our program instance
    wc.lpfnWndProc =    wndProc;                // tell it to use our wndProc function to handle messages
    wc.lpszClassName =  TEXT("DisplayImage");   // give this window class a name.

    RegisterClassEx(&wc);           // register our window class with Windows

    // the style of the window we want... we want a normal window but do not want it resizable.
    int style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;    // normal overlapped window with a caption and a system menu (the X to close)
        
    // Figure out how big we need to make the window so that the CLIENT area (the part we will be drawing to) is
    //  the desired size
    RECT rc = {0,0,screenSize_X,screenSize_Y};      // desired rect
    AdjustWindowRect(&rc,style,FALSE);              // adjust the rect with the given style, FALSE because there is no menu

    return CreateWindow(            // create the window
        TEXT("DisplayImage"),       // the name of the window class to use for this window (the one we just registered)
        TEXT("Display an Image"),   // the text to appear on the title of the window
        style | WS_VISIBLE,         // the style of this window (OR it with WS_VISIBLE so it actually becomes visible immediately)
        100,100,                    // create it at position 100,100
        rc.right - rc.left,         // width of the window we want
        rc.bottom - rc.top,         // height of the window
        NULL,NULL,                  // no parent window, no menu
        inst,                       // our program instance
        NULL);                      // no extra parameter

}


///////////////////////////////
///////////////////////////////
// The actual entry point for the program!
//  This is Windows' version of the 'main' function:
int WINAPI WinMain(HINSTANCE inst,HINSTANCE prev,LPSTR cmd,int show)
{
    // load our image
    loadImage("terminator.jpg");

    // create our window
    HWND wnd = createWindow(inst);

    // Do the message pump!  keep polling for messages (and respond to them)
    //  until the user closes the window.
    MSG msg;
    while( GetMessage(&msg,wnd,0,0) ) // while we are getting non-WM_QUIT messages...
    {
        TranslateMessage(&msg);     // translate them
        DispatchMessage(&msg);      // and dispatch them (our wndProc will process them)
    }

    // once the user quits....
    cleanUpImage();
}
// I'm cheating a little with this header -- you normally have to include
// SFML/Graphics.hpp and SFML/Window.hpp and link to the libs, but I just include
// this common header I made which does all that automatically
#include <sfml.h>


///////////////////////////////
///////////////////////////////

const int   screenSize_X = 640;
const int   screenSize_Y = 480;

///////////////////////////////
///////////////////////////////
// Function to load the image into our texture and sprite so we can draw it
void loadImage(const char* pathname, sf::Texture& texture, sf::Sprite& sprite)
{
    texture.loadFromFile(pathname);     // load it from the file
    sprite.setTexture(texture);         // put that texture in our sprite
    sprite.setTextureRect( sf::IntRect(0,0,screenSize_X,screenSize_Y) );    // the rectangle of the texture to use for this sprite
}

///////////////////////////////
///////////////////////////////
// Normal entry point
int main()
{
    // Create our window
    sf::RenderWindow window(
        sf::VideoMode(screenSize_X,screenSize_Y),       // size of the client area we want
        "Display an Image"                              // The text to appear on the window title
        );

    // load our image
    sf::Texture     texture;        // the texture which will contain our pixel data
    sf::Sprite      sprite;         // the sprite which will actually draw it
    loadImage("image.bmp",texture,sprite);

    // Set FPS so this draws at 60 FPS (note:  I didn't do this for the WinAPI version because it'd be too hard for such
    //  a small example)
    window.setFramerateLimit( 60 );
    
    bool program_running = true;        // true until the user wants to quit
    while(program_running)
    {
        // Do the event pump -- same idea as with Windows... look for events and process them
        sf::Event evt;
        while( window.pollEvent(evt) )      // while there are any events to process...
        {
            // process them. But we're only interested in the closed event
            if(evt.type == sf::Event::EventType::Closed)        // is this a close event?
                program_running = false;                        // indicate that we want the window to close
        }

        // now that events are processed... draw our image
        window.draw(sprite);        // just draw it to the back buffer
        window.display();           // and display it so the back buffer moves to the front
    }
}