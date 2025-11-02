#pragma once
#include "../../../ext/jni/jni.h"

struct ModuleManager
{
	static void Init();

	static void UpdateModules(JNIEnv* env);
};

