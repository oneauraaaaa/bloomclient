#include "base.h"
#include "sdk/sdk.h"

#include "moduleManager/modules/visual/esp.h"
#include "moduleManager/modules/combat/aimAssist.h"

#include "../../ext/imgui/imgui.h"
#include "menu/menu.h"
#include <string>

#include <chrono>
#include <ctime>

#pragma warning(disable : 4996) 

void Base::RenderLoop()
{
    if (!Base::Running) return;

    auto& io = ImGui::GetIO();
    auto* drawList = ImGui::GetForegroundDrawList();

    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    char date_buf[16]; 
    strftime(date_buf, sizeof(date_buf), "%d.%m.%Y", std::localtime(&time));

    char watermark_buf[128];
    snprintf(watermark_buf, sizeof(watermark_buf), "bloom private | %.0f fps | %s", io.Framerate, date_buf);
    const char* watermark_text = watermark_buf;

    float font_size = 18.0f;
    float padding = 8.0f;
    float rounding = 4.0f;
    ImVec2 screen_size = io.DisplaySize;

    ImVec2 text_size = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, watermark_text);

    ImVec2 box_pos = ImVec2(
        screen_size.x - text_size.x - padding * 2.0f,
        screen_size.y - text_size.y - padding * 2.0f
    );
    ImVec2 text_pos = ImVec2(box_pos.x + padding, box_pos.y + padding);

    ImU32 bg_color = IM_COL32(20, 20, 20, 180);
    ImU32 border_color = IM_COL32(255, 255, 255, 50);
    ImU32 text_color = IM_COL32(255, 255, 255, 255);
    ImU32 shadow_color = IM_COL32(0, 0, 0, 150);

    drawList->AddRectFilled(box_pos, ImVec2(box_pos.x + text_size.x + padding * 2.0f, box_pos.y + text_size.y + padding * 2.0f), bg_color, rounding);
    drawList->AddRect(box_pos, ImVec2(box_pos.x + text_size.x + padding * 2.0f, box_pos.y + text_size.y + padding * 2.0f), border_color, rounding, 0, 1.0f);

    drawList->AddText(Menu::Font, font_size, ImVec2(text_pos.x + 1, text_pos.y + 1), shadow_color, watermark_text);
    drawList->AddText(Menu::Font, font_size, text_pos, text_color, watermark_text);

    Esp::RenderUpdate();
    AimAssist::RenderUpdate();
}