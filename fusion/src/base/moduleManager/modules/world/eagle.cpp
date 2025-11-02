//#include "eagle.h"
//#include "../../../sdk/sdk.h"
//#include "../../../menu/menu.h"
//#include "../../../util/math/math.h" 
//
//void eagle::RenderMenu()
//{
//    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
//    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
//    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
//
//    if (ImGui::BeginChild("eagle", ImVec2(425, 75)))
//    {
//        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
//        Menu::DoToggleButtonStuff(9999, "Toggle Eagle/Ninja Bridge", &eagle::Enabled);
//    }
//    ImGui::EndChild();
//    ImGui::PopStyleVar();
//    ImGui::PopStyleColor();
//}
//
//
//void eagle::Update()
//{
//    if (!eagle::Enabled || !SDK::Minecraft->thePlayer || SDK::Minecraft->IsInGuiState()) {
//        return;
//    }
//
//    auto keyBindSneak = SDK::Minecraft->gameSettings->keyBindSneak;
//    if (keyBindSneak == nullptr) return;
//
//    if (!keyBindSneak->isKeyDown()) {
//        return;
//    }
//
//    Vector3 playerPos = SDK::Minecraft->thePlayer->GetPosition();
//
//    Vector3 blockBelowPos(floor(playerPos.x), floor(playerPos.y - 1), floor(playerPos.z));
//
//    if (SDK::Minecraft->theWorld == nullptr) return;
//
//    auto blockBelow = SDK::Minecraft->theWorld->getBlockState(blockBelowPos);
//
//    if (blockBelow != NULL && blockBelow->isAir()) {
//        keyBindSneak->setPressed(true);
//    }
//}