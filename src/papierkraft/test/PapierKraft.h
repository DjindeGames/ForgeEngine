#pragma once

#include "engine/core/CoreEngine.h"

namespace PapierKraft
{
	void Update(float dT);
	bool ShouldTerminate();
	int CoreLoop();
	void BuildMeshes();
	void ProcessInput();
	void PerformTests();
}