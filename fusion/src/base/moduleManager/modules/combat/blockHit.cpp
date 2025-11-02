#include "blockhit.h"
#include "../../../sdk/sdk.h"
#include "../../commonData.h"
#include "../../../util/logger.h"
#include "../../../java/java.h"
#include "../../../util/math/math.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../../../patcher/patcher.h"

#include <chrono>

long lastBlockhitTime = 0;

bool isHoldingSword()
{
	static jclass swordClass = NULL;
	if (swordClass == NULL) {
		Java::AssignClass("net.minecraft.item.ItemSword", swordClass);
	}

	if (swordClass == NULL) {
		return false;
	}

	auto player = SDK::Minecraft->thePlayer;
	if (player == NULL) return false;

	auto inventory = player->GetInventory();
	if (inventory.GetInstance() == NULL) return false;

	auto itemStack = inventory.GetCurrentItem();
	if (itemStack.GetInstance() == NULL) return false;

	return Java::Env->IsInstanceOf(itemStack.GetItem(), swordClass);
}

void blockhit::Update()
{
	if (!blockhit::Enabled) {
		return;
	}
	if (!SDK::Minecraft->thePlayer || SDK::Minecraft->IsInGuiState()) {
		return;
	}

	if (ignoreBlocks && SDK::Minecraft->GetMouseOver().IsTypeOfBlock()) {
		return;
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {

		if (isHoldingSword()) {

			long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			if (lastBlockhitTime == 0) lastBlockhitTime = milli;

			if ((milli - lastBlockhitTime) < blockhit::DelayMs) {
				return;
			}

			POINT pos_cursor;
			GetCursorPos(&pos_cursor);
			SendMessage(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
			SendMessage(Menu::HandleWindow, WM_RBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));

			lastBlockhitTime = milli;
		}
	}
}



void blockhit::RenderMenu()
{

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("blockhit", ImVec2(425, 75)))
	{

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(230044, "Toggle Blockhit", &blockhit::Enabled);

		//ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		//ImGui::Separator();
		Menu::DoSliderStuff(191919, "Blockhit Delay (ms)", &blockhit::DelayMs, 50, 500); 

	}
	ImGui::EndChild();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

}
