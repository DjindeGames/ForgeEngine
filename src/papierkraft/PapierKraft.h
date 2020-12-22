#pragma once

#include "../engine/CoreEngine.h"

namespace PapierKraft
{
	void Update(float dT);
	bool ShouldTerminate(GLFWwindow* window);
	int CoreLoop();
	bool CompileShaders();
	void BuildMesh();
	void ClearResources();
	void ProcessInput();
	void PerformTests();
}