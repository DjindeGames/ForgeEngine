#pragma once

#include "engine/core/ResourceLoader.h"

namespace ForgeEngine
{
    class Shader;

	class ShaderLoader : public ResourceLoader<Shader>
	{
		using Mother = ResourceLoader<Shader>;

    protected:
        bool AddResource(const std::string& resourcePath) override;
        const char* GetName() { return "Loaded Shaders"; }
	};
}