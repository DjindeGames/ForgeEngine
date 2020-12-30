#pragma once

#include "engine/core/CoreEngine.h"

namespace PapierKraft
{
	void Update(float dT);
	bool ShouldTerminate(GLFWwindow* window);
	int CoreLoop();
	void BuildMeshes();
	void ProcessInput();
	void PerformTests();
}