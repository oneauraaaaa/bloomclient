#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>

struct blockhit
{
	inline static bool Enabled = false;

	inline static float DelayMs = 200;

	inline static bool ignoreBlocks = true;

	//inline static float ReachDistance = 3.0f;

	static void Update();

	static void RenderMenu();
};

