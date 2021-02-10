#pragma once

#include "engine/core/CoreEngine.h"

namespace ForgeEngine
{
	class Entity;
}


namespace PapierKraft
{
	void Update(float dT);
	bool ShouldTerminate();
	int CoreLoop();
	void Init();
	void ProcessInput();
	void PerformTests();
	void ReleaseResources();
	ForgeEngine::Entity* BuildChunk();
}