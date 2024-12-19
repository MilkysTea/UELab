#include <iostream>

#include "draw.h"    //绘制套
#include "AndroidImgui.h"     //创建绘制套
#include "GraphicsManager.h" //获取 当前渲染模式



int main(int argc, char *argv[]) {
    std::cout << "免责声明：" << std::endl << std::endl;
    std::cout << "此软件是一款用于逆向分析和测试游戏功能的工具，旨在帮助开发者理解游戏的内部工作原理以及进行相关测试。然而，请注意以下几点：" << std::endl << std::endl;

    std::cout << "1. 本软件的使用仅限于合法的研究和测试目的。任何将此软件用于非法活动、侵犯版权或其他违法行为的用户将承担相应的法律责任。" << std::endl;
    std::cout << "2. 本软件可能会影响游戏的正常运行，甚至可能导致游戏崩溃、数据损坏或其他不可预测的问题。使用本软件可能会对游戏的稳定性和功能性产生不利影响。" << std::endl;
    std::cout << "3. 本软件可能会涉及游戏厂商的知识产权和利益，因此使用本软件可能会引起游戏厂商的不满甚至法律纠纷。" << std::endl;
    std::cout << "4. 用户对使用本软件所产生的一切后果和风险负全部责任。软件开发者及其关联方不承担任何直接或间接的责任，包括但不限于因软件使用造成的损失、损害、法律纠纷或其他不良后果。" << std::endl;
    std::cout << "5. 本软件仅用于自己开发的UE4程序进行调试，禁止调试其他任何游戏厂商的程序。" << std::endl;
    std::cout << "6. 本软件的发布和使用可能受到不同国家和地区的法律法规的限制。用户应当遵守当地的法律法规，确保在合法范围内使用本软件。" << std::endl << std::endl;

    std::cout << "请在使用本软件前详细阅读并理解上述免责声明。一旦您开始使用本软件，即代表您同意遵守上述声明，并愿意承担因此产生的一切风险和责任。" << std::endl;
    std::cout << "对于任何因使用本软件所引起的问题，我们将不负有任何法律或经济责任。" << std::endl << std::endl;
    std::cout << "（https://t.me/naicha9188）" << std::endl;

    ::graphics = GraphicsManager::getGraphicsInterface(GraphicsManager::VULKAN);

    //获取屏幕信息    
    ::screen_config(); 

    ::native_window_screen_x = (::displayInfo.height > ::displayInfo.width ? ::displayInfo.height : ::displayInfo.width);
    ::native_window_screen_y = (::displayInfo.height > ::displayInfo.width ? ::displayInfo.height : ::displayInfo.width);
    ::abs_ScreenX = (::displayInfo.height > ::displayInfo.width ? ::displayInfo.height : ::displayInfo.width);
    ::abs_ScreenY = (::displayInfo.height < ::displayInfo.width ? ::displayInfo.height : ::displayInfo.width);

    ::window = android::ANativeWindowCreator::Create("test", native_window_screen_x, native_window_screen_y, permeate_record);
    graphics->Init_Render(::window, native_window_screen_x, native_window_screen_y);
    
    Touch::Init({(float)::abs_ScreenX, (float)::abs_ScreenY}, false); //最后一个参数改成true 只监听
    Touch::setOrientation(displayInfo.orientation);

    
    ::init_My_drawdata(); //初始化绘制数据

    while (true) {
        drawBegin();
        graphics->NewFrame();
        
        Layout_tick_UI();

        graphics->EndFrame();        
    }
    
    // graphics->DeleteTexture(image);
    graphics->Shutdown();
    android::ANativeWindowCreator::Destroy(::window);
    return 0;
}
