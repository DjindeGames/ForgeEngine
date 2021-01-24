#pragma once

#include "engine/core/CoreEngine.h"

namespace PapierKraft
{
	void Update(float dT);
	bool ShouldTerminate();
	int CoreLoop();
	void BuildBlocks();
	void ProcessInput();
	void PerformTests();
	void ReleaseResources();
}