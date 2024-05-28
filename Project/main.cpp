// Dear ImGui: standalone example application for Win32 + OpenGL 3

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

// This is provided for completeness, however it is strongly recommended you use OpenGL with SDL or GLFW.

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <GL/GL.h>
#include <tchar.h>
#include "stb_image.h"
#include "GeomObject.h"
#include <iostream>
#include <vector>

using namespace std;

// Data stored per platform window
struct WGL_WindowData { HDC hDC; };

// Data
static HGLRC            g_hRC;
static WGL_WindowData   g_MainWindow;
static int              g_Width;
static int              g_Height;

// Forward declarations of helper functions
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData* data);
void CleanupDeviceWGL(HWND hWnd, WGL_WindowData* data);
void ResetDeviceWGL();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

GLuint LoadTextureFromFile(const char* filename, int* width, int* height) {
    unsigned char* image_data = stbi_load(filename, width, height, nullptr, 4);
    if (image_data == nullptr) {
        return 0;
    }

    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    stbi_image_free(image_data);

    return texture_id;
}


vector<GeomObject*> objects;

// Main code
int main(int, char**)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_OWNDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui Win32+OpenGL3 Example", WS_OVERLAPPEDWINDOW, 0, 0, 1280, 800, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize OpenGL
    if (!CreateDeviceWGL(hwnd, &g_MainWindow))
    {
        CleanupDeviceWGL(hwnd, &g_MainWindow);
        ::DestroyWindow(hwnd);
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }
    wglMakeCurrent(g_MainWindow.hDC, g_hRC);

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_InitForOpenGL(hwnd);
    ImGui_ImplOpenGL3_Init();

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.33f, 0.33f, 0.33f, 0.33f);//цвет бэкграунда(не меню)


    int a, b;

    GLuint XsmallSquareButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/smallSquare.png", &a, &b);
    GLuint YsmallSquareButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/smallSquare.png", &a, &b);
    GLuint ZsmallSquareButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/smallSquare.png", &a, &b);

    GLuint menuTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/menu1.png", &a, &b);


    GLuint cubeButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/newcube1.png", &a, &b);


    GLuint cylinderButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/newcylinder1.png", &a, &b);

    GLuint sphereButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/newsphere1.png", &a, &b);

    GLuint coneButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/newcone1.png", &a, &b);

    GLuint shesterenkaButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/pngwing.com.png", &a, &b);

    GLuint angledsquareButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/squarediagonal.png", &a, &b);

    GLuint rotationsquareButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/rotationsquare.png", &a, &b);

    GLuint arrowsquareButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/arrowsquare.png", &a, &b);

    GLuint LeftRectangleButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/LeftRectangle.png", &a, &b);

    GLuint RightRectangleButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/RightRectangle.png", &a, &b);

    GLuint letterXTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/LetterX1.png", &a, &b);

    GLuint letterYTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/Y.png", &a, &b);

    GLuint exitButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/exit.png", &a, &b);
    
    GLuint letterZTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/LetterZ1.png", &a, &b);

   

    GLuint lineTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/blackline.png", &a, &b);

    

    GLuint verticallineTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/blackline.png", &a, &b);

    
    GLuint rightlineTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/blackline.png", &a, &b);

    
    GLuint inscriptonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/transformation6.png", &a, &b);

    
    GLuint Axisinsigna = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/Axisinsigna.png", &a, &b);


    GLuint ToplineTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/blackline.png", &a, &b);

    
    GLuint leftlineTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/blackline.png", &a, &b);

    
    GLuint rightedgeTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/blackline.png", &a, &b);

    
    GLuint lowedgeTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/blackline.png", &a, &b);

    
    GLuint needlelineTexture1 = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/blackline.png", &a, &b);

    
    GLuint needlelineTexture2 = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/blackline.png", &a, &b);

    
    GLuint needlelineTexture3 = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/blackline.png", &a, &b);

    
    GLuint needlelineTexture4 = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/blackline.png", &a, &b);

    
    GLuint needlelineTexture5 = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/blackline.png", &a, &b);

   
    GLuint needlelineTexture6 = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/blackline.png", &a, &b);


    GLuint crossTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/cross.png", &a, &b);

    
    bool XSquareChecked = false;
    bool YSquareChecked = false;
    bool ZSquareChecked = false;

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done)
            break;

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        //if (show_demo_window)
            //ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::SetNextWindowPos(ImVec2(100, 0));//смещение окна
            ImGui::SetNextWindowSize(ImVec2(800, 400));//разрешение окна

            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.33f, 0.33f, 0.33f, 1.0f));// цвет меню #555555 75% gray
            ImGui::Begin("Hello, World!",nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);                          // Create a window called "Hello, world!" and append into it.

            



            int texture_width, texture_height;


            
            if (menuTexture != 0) {
                ImGui::SetCursorPos(ImVec2(0, 0));//вправо, вниз
                ImGui::Image((void*)(intptr_t)menuTexture, ImVec2((float)540, (float)300));//(float)50, (float)50)- ширина и высота куба
            }




            if (cubeButtonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(25, 320));//вправо, вниз
                if (ImGui::ImageButton((void*)(intptr_t)cubeButtonTexture, ImVec2((float)60, (float)60)))//(float)50, (float)50)- ширина и высота куба
                {
                    objects.push_back(new Cube());
                }
            }


            
            if (cylinderButtonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(100, 320));
                if (ImGui::ImageButton((void*)(intptr_t)cylinderButtonTexture, ImVec2((float)60, (float)60)))
                {
                    objects.push_back(new Cylinder());

                }

            }

            
            if (sphereButtonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(175, 320));
                if(ImGui::ImageButton((void*)(intptr_t)sphereButtonTexture, ImVec2((float)60, (float)60)))
                {
                    objects.push_back(new Sphere());

                }
            }

            
            if (coneButtonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(250, 320));
                if(ImGui::ImageButton((void*)(intptr_t)coneButtonTexture, ImVec2((float)60, (float)60)))
                {
                    objects.push_back(new Cone());


                }
            }

            
            if (shesterenkaButtonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(410, 320));
                ImGui::ImageButton((void*)(intptr_t)shesterenkaButtonTexture, ImVec2((float)60, (float)60));
            }


            
            if (angledsquareButtonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(570, 230));
                ImGui::ImageButton((void*)(intptr_t)angledsquareButtonTexture, ImVec2((float)30, (float)30));
            }



            
            if (rotationsquareButtonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(645, 230));
                ImGui::ImageButton((void*)(intptr_t)rotationsquareButtonTexture, ImVec2((float)30, (float)30));
            }


            
            if (arrowsquareButtonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(720, 230));
                ImGui::ImageButton((void*)(intptr_t)arrowsquareButtonTexture, ImVec2((float)30, (float)30));
            }

            
            if (LeftRectangleButtonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(600, 350));
                ImGui::ImageButton((void*)(intptr_t)LeftRectangleButtonTexture, ImVec2((float)85, (float)30));
            }

            
            if (RightRectangleButtonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(690, 350));
                ImGui::ImageButton((void*)(intptr_t)RightRectangleButtonTexture, ImVec2((float)85, (float)30));
            }

            
            if (exitButtonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(25, 10));
                ImGui::ImageButton((void*)(intptr_t)exitButtonTexture, ImVec2((float)20, (float)20));
            }

            
            /*GLuint rectangleleftButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/longRectangle_reserve.png", &texture_width, &texture_height);

            if (rectangleleftButtonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(570, 330));
                ImGui::ImageButton((void*)(intptr_t)rectangleleftButtonTexture, ImVec2((float)180, (float)40));
            }*/

            

            if (XsmallSquareButtonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(585, 290));
                if (ImGui::ImageButton((void*)(intptr_t)XsmallSquareButtonTexture, ImVec2((float)25, (float)25)))
                {
                   

                    if(XSquareChecked)
                        XsmallSquareButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/smallSquare.png", &a, &b);
                    else
                        XsmallSquareButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/checkbox.png", &texture_width, &texture_height);

                    XSquareChecked = !XSquareChecked;
                }
            }

            
            if (YsmallSquareButtonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(655, 290));
                if (ImGui::ImageButton((void*)(intptr_t)YsmallSquareButtonTexture, ImVec2((float)25, (float)25)))
                {

                    if (YSquareChecked)
                        YsmallSquareButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/smallSquare.png", &a, &b);
                    else
                        YsmallSquareButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/checkbox.png", &texture_width, &texture_height);


                    YSquareChecked = !YSquareChecked;
                }


            }


            
            if (ZsmallSquareButtonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(725, 290));
                if (ImGui::ImageButton((void*)(intptr_t)ZsmallSquareButtonTexture, ImVec2((float)25, (float)25)))
                {
                  
                    if (ZSquareChecked)

                        ZsmallSquareButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/smallSquare.png", &a, &b);
                    else
                        ZsmallSquareButtonTexture = LoadTextureFromFile("C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/checkbox.png", &texture_width, &texture_height);

                    ZSquareChecked = !ZSquareChecked;
                }

            }

          




            //"C:/Users/telep/OneDrive/Рабочий стол/IMGUI/imgui-master/examples/example_sdl2_opengl3/images/line.png", &texture_width, &texture_height);

            
            if (letterXTexture != 0) {
                ImGui::SetCursorPos(ImVec2(555, 291));
                ImGui::Image((void*)(intptr_t)letterXTexture, ImVec2((float)30, (float)25));
            }


            
            if (letterYTexture != 0) {
                ImGui::SetCursorPos(ImVec2(628, 286));
                ImGui::Image((void*)(intptr_t)letterYTexture, ImVec2((float)32, (float)35));
            }



            
            if (letterZTexture != 0) {
                ImGui::SetCursorPos(ImVec2(698, 294));
                ImGui::Image((void*)(intptr_t)letterZTexture, ImVec2((float)23, (float)23));
            }



            
            if (lineTexture != 0) {
                ImGui::SetCursorPos(ImVec2(0, 300));
                ImGui::Image((void*)(intptr_t)lineTexture, ImVec2((float)540, (float)5));
            }


            
            if (lineTexture != 0) {
                ImGui::SetCursorPos(ImVec2(540, 0));
                ImGui::Image((void*)(intptr_t)lineTexture, ImVec2((float)5, (float)391));
            }


            
            if (lineTexture != 0) {
                ImGui::SetCursorPos(ImVec2(540, 195));
                ImGui::Image((void*)(intptr_t)lineTexture, ImVec2((float)300, (float)5));
            }

            
            if (inscriptonTexture != 0) {
                ImGui::SetCursorPos(ImVec2(555, 207));
                ImGui::Image((void*)(intptr_t)inscriptonTexture, ImVec2((float)105, (float)17));
            }


            
            if (Axisinsigna != 0) {
                ImGui::SetCursorPos(ImVec2(560, 277));
                ImGui::Image((void*)(intptr_t)Axisinsigna, ImVec2((float)40, (float)10));
            }



            
            if (ToplineTexture != 0) {
                ImGui::SetCursorPos(ImVec2(0, 1));
                ImGui::Image((void*)(intptr_t)ToplineTexture, ImVec2((float)840, (float)5));
            }

            
            if (ToplineTexture != 0) {
                ImGui::SetCursorPos(ImVec2(0, 0));
                ImGui::Image((void*)(intptr_t)ToplineTexture, ImVec2((float)5, (float)390));
            }


            
            if (rightedgeTexture != 0) {
                ImGui::SetCursorPos(ImVec2(796, 0));
                ImGui::Image((void*)(intptr_t)rightedgeTexture, ImVec2((float)5, (float)390));
            }

            
            if (lowedgeTexture != 0) {
                ImGui::SetCursorPos(ImVec2(0, 390));
                ImGui::Image((void*)(intptr_t)lowedgeTexture, ImVec2((float)840, (float)8));
            }


            
            if (needlelineTexture1 != 0) {
                ImGui::SetCursorPos(ImVec2(540, 32));
                ImGui::Image((void*)(intptr_t)needlelineTexture1, ImVec2((float)300, (float)3));
            }

            
            if (needlelineTexture2 != 0) {
                ImGui::SetCursorPos(ImVec2(540, 64));
                ImGui::Image((void*)(intptr_t)needlelineTexture2, ImVec2((float)300, (float)3));
            }


            
            if (needlelineTexture3 != 0) {
                ImGui::SetCursorPos(ImVec2(540, 96));
                ImGui::Image((void*)(intptr_t)needlelineTexture3, ImVec2((float)300, (float)3));
            }


            
            if (needlelineTexture4 != 0) {
                ImGui::SetCursorPos(ImVec2(540, 128));
                ImGui::Image((void*)(intptr_t)needlelineTexture4, ImVec2((float)300, (float)3));
            }


            
            if (needlelineTexture5 != 0) {
                ImGui::SetCursorPos(ImVec2(540, 160));
                ImGui::Image((void*)(intptr_t)needlelineTexture5, ImVec2((float)300, (float)3));
            }

            
            if (needlelineTexture6 != 0) {
                ImGui::SetCursorPos(ImVec2(540, 192));
                ImGui::Image((void*)(intptr_t)needlelineTexture6, ImVec2((float)300, (float)3));
            }

            ImGui::SetCursorPos(ImVec2(546, 7));//сдвиг меню с ползунком
            if (ImGui::BeginChild("Child Window", ImVec2(245, 192), true, ImGuiWindowFlags_AlwaysVerticalScrollbar)) {

                for (int i = 0; i < objects.size(); i++) {

                    ImGui::SetCursorPos(ImVec2(0, i * 31 + 8));//31 + 8
                    ImGui::Text("%s", objects[i]->name.c_str());

                    ImGui::SetCursorPos(ImVec2(205, i * 31 + 7));// 31 + 9
                    if (ImGui::ImageButton(std::to_string(i).c_str(), (void*)(intptr_t)crossTexture, ImVec2((float)12, (float)12)))
                    {
                        objects.erase(objects.begin() + i);

                    }
                }
                ImGui::EndChild();
            }
           
            
            //-------------------------
            //ImGui::Image

            /*ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();*/
            //ImGui::Text("counter = %d", counter);

            //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 0.0f / io.Framerate, io.Framerate);
            ImGui::PopStyleColor();
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        glViewport(0, 0, g_Width, g_Height);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Present
        ::SwapBuffers(g_MainWindow.hDC);
    }

    /*ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceWGL(hwnd, &g_MainWindow);
    wglDeleteContext(g_hRC);
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);*/

    return 0;
}

// Helper functions
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
    HDC hDc = ::GetDC(hWnd);
    PIXELFORMATDESCRIPTOR pfd = { 0 };
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;

    const int pf = ::ChoosePixelFormat(hDc, &pfd);
    if (pf == 0)
        return false;
    if (::SetPixelFormat(hDc, pf, &pfd) == FALSE)
        return false;
    ::ReleaseDC(hWnd, hDc);

    data->hDC = ::GetDC(hWnd);
    if (!g_hRC)
        g_hRC = wglCreateContext(data->hDC);
    return true;
}

void CleanupDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
    wglMakeCurrent(nullptr, nullptr);
    ::ReleaseDC(hWnd, data->hDC);
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam != SIZE_MINIMIZED)
        {
            g_Width = LOWORD(lParam);
            g_Height = HIWORD(lParam);
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
