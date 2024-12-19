#include "draw.h"
#include "RWTools.h"
#include "Setting.h"
#include "Function.h"
#include "DrawFuntion.h"

#include "My_font/zh_Font.h"
#include "My_font/fontawesome-brands.h"
#include "My_font/fontawesome-regular.h"
#include "My_font/fontawesome-solid.h"
#include "My_font/gui_icon.h"
   
#include "My_icon/pic_ZhenAiKun_png.h"

bool permeate_record = false;
bool permeate_record_ini = false;
struct Last_ImRect LastCoordinate = {0, 0, 0, 0};


std::unique_ptr<AndroidImgui> graphics;
ANativeWindow *window = NULL; 
android::ANativeWindowCreator::DisplayInfo displayInfo;// 屏幕信息
ImGuiWindow *g_window = NULL;// 窗口信息
int abs_ScreenX = 0, abs_ScreenY = 0;// 绝对屏幕X _ Y
int native_window_screen_x = 0, native_window_screen_y = 0;

TextureInfo Aekun_image{};

ImFont* zh_font = NULL;
ImFont* icon_font_0 = NULL;
ImFont* icon_font_1 = NULL;
ImFont* icon_font_2 = NULL;



bool M_Android_LoadFont(float SizePixels) {
    ImGuiIO &io = ImGui::GetIO();
    
    //ImFontConfig config; //oppo字体部分
    //config.FontDataOwnedByAtlas = false;
    //config.SizePixels = SizePixels;
    //config.OversampleH = 1;
    //::zh_font = io.Fonts->AddFontFromMemoryTTF((void *)OPPOSans_H, OPPOSans_H_size, 0.0f, &config, io.Fonts->GetGlyphRangesChineseFull());    
    ////io.Fonts->AddFontDefault(&config);

	static const ImWchar icons_ranges[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.OversampleH = 3.0;
    icons_config.OversampleV = 3.0;		
    icons_config.SizePixels = SizePixels;
    //icons_config.GlyphOffset.y += 7.0f; // 通过 GlyphOffset 调整单个字形偏移量，向下偏移 size 像素
	::icon_font_0 = io.Fonts->AddFontFromMemoryCompressedTTF((const void *)&font_awesome_brands_compressed_data, sizeof(font_awesome_brands_compressed_data), 0.0f, &icons_config, icons_ranges);
	::icon_font_1 = io.Fonts->AddFontFromMemoryCompressedTTF((const void *)&font_awesome_regular_compressed_data, sizeof(font_awesome_regular_compressed_data), 0.0f, &icons_config, icons_ranges);
	::icon_font_2 = io.Fonts->AddFontFromMemoryCompressedTTF((const void *)&font_awesome_solid_compressed_data, sizeof(font_awesome_solid_compressed_data), 0.0f, &icons_config, icons_ranges);

    io.Fonts->AddFontDefault();
    return zh_font != nullptr;
}
void init_My_drawdata() {
    ImGui::StyleColorsLight(); //白色
    ImGui::My_Android_LoadSystemFont(25.0f); //(加载系统字体 安卓15完美适配)
    M_Android_LoadFont(25.0f); //加载字体(还有图标)
    ImGui::GetStyle().ScaleAllSizes(3.25f);
    ::Aekun_image = graphics->LoadTextureFromMemory((void *)picture_ZhenAiKun_PNG_H, sizeof(picture_ZhenAiKun_PNG_H));

    pid = GetPid("com.ShuiSha.FPS2");//读取游戏包名
    printf("pid:%d\n", pid);
    libUE4 = get_module_base(pid,"libUE4.so");
    while(!libUE4) {
        libUE4 = get_module_base(pid,"libUE4.so");
    }
    printf("libUE4:%p\n", libUE4);
    px = (float) ::abs_ScreenX / 2;
    py = (float) ::abs_ScreenY / 2;
}


void screen_config() {
    ::displayInfo = android::ANativeWindowCreator::GetDisplayInfo();
}

void drawBegin() {
    if (::permeate_record_ini) {
        LastCoordinate.Pos_x = ::g_window->Pos.x;
        LastCoordinate.Pos_y = ::g_window->Pos.y;
        LastCoordinate.Size_x = ::g_window->Size.x;
        LastCoordinate.Size_y = ::g_window->Size.y;

        graphics->Shutdown();
        android::ANativeWindowCreator::Destroy(::window);
        ::window = android::ANativeWindowCreator::Create("test_sysGui", native_window_screen_x, native_window_screen_y, permeate_record);
        graphics->Init_Render(::window, native_window_screen_x, native_window_screen_y);

        ::init_My_drawdata(); //初始化绘制数据
    } 


    static uint32_t orientation = -1;
    screen_config();
    if (orientation != displayInfo.orientation) {
        orientation = displayInfo.orientation;
        Touch::setOrientation(displayInfo.orientation);
        if (g_window != NULL) {
            g_window->Pos.x = 100;
            g_window->Pos.y = 125;        
        }        
        //cout << " width:" << displayInfo.width << " height:" << displayInfo.height << " orientation:" << displayInfo.orientation << endl;
    }
}

void GetPlayerData() {
    if(Settings.Draw.Checked) {
        Matrixaddr = Read<uintptr_t>(Read<uintptr_t>(libUE4 + 0xb006f58) + 0x20) + 0x280;
        UWorld = Read<uintptr_t>(libUE4 + 0xb036900);//获取游戏世界
        Actor = Read<uintptr_t>(Read<uintptr_t>(UWorld + 0x30) + 0x98);//获取数组
        ActorCount = Read<int>(Read<uintptr_t>(UWorld + 0x30) + 0xa0);//获取数组大小

        vm_read(Matrixaddr, Matrix, sizeof(Matrix));
        for (int i = 0; i < ActorCount; i++) {
            auto Objetc = Read<uintptr_t>(Actor + i * 0x8);//获取数组对象
            if(Objetc == 0) continue;
            Vector3 Pos = Read<Vector3>(Read<uintptr_t>(Objetc + 0x130) + 0x1d0);//获取敌人坐标
            if (Pos.x == 0 && Pos.y == 0 && Pos.z == 0) continue;
            // printf("Pos:%f,%f,%f\n", Pos.x, Pos.y, Pos.z);
            Vector4 Screen{0};
            float Camera = 0;
            Screen = WorldToScreen(Pos, &Camera);
            if (Camera > 0) {
                DrawRect(Screen);
                DrawLine(Screen);
            }
        }
    }
}

void Layout_tick_UI() {
    ImGuiIO &io = ImGui::GetIO();
    ImGuiStyle &style = ImGui::GetStyle();
    style.ScrollbarSize = 10.0f;
    style.WindowTitleAlign = ImVec2(0.5, 0.5);
    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_Always);
    if (ImGui::Begin("枪战特训 @by-MilkyTea", &Settings.Draw.OpenMenu, ImGuiWindowFlags_None)) {
                ImGui::Checkbox(u8"开启绘制", &Settings.Draw.Checked);
                ImGui::Spacing();
                ImGui::Checkbox(u8"方框", &Settings.Draw.Box);
                ImGui::SameLine();
                ImGui::Checkbox(u8"射线", &Settings.Draw.Line);
                ImGui::Spacing();
    }
    ImGui::End(); // 结束窗口
    GetPlayerData();
}
