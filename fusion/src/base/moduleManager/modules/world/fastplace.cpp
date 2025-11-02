//#include "fastplace.h"
//#include "../../../sdk/sdk.h"
//#include "../../../menu/menu.h"
//#include "../../../../../ext/jni/jni.h"
//
//void rightClickDelayTimer(JNIEnv* env, int max) {
//	jclass minecraftClass = env->FindClass("ave");
//	jmethodID getMinecraft = env->GetStaticMethodID(minecraftClass, "A", "()Lave;");
//	jobject mc_instance = env->CallStaticObjectMethod(minecraftClass, getMinecraft);
//
//	jfieldID field = env->GetFieldID(minecraftClass, "ap", "I");
//	int delay = env->GetIntField(mc_instance, field);
//
//	if (delay > max)
//		env->SetIntField(mc_instance, field, max);
//
//	env->DeleteLocalRef(minecraftClass);
//	env->DeleteLocalRef(mc_instance);
//}
//
//void fastplace::Update(JNIEnv* env)
//{
//	if (!fastplace::Enabled || !SDK::Minecraft->thePlayer || SDK::Minecraft->IsInGuiState()) {
//		return;
//	}
//
//	rightClickDelayTimer(env, 0);
//}
//
//void fastplace::RenderMenu()
//{
//	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
//	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
//	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
//
//	if (ImGui::BeginChild("fastplace", ImVec2(425, 75)))
//	{
//		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
//		Menu::DoToggleButtonStuff(8888, "Toggle Fastplace", &fastplace::Enabled);
//	}
//	ImGui::EndChild();
//	ImGui::PopStyleVar();
//	ImGui::PopStyleColor();
//}
//
//
