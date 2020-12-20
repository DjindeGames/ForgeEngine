#pragma once

#include "../engine/CoreEngine.h"

namespace PapierKraft
{
	void Update(float dT);
	bool ShouldTerminate(GLFWwindow* window);
	int CoreLoop();
	bool CompileShaders();
	void BuildTriangle();
	void ClearResources();
}