#pragma once

#include <memory>
#include <vector>

namespace ForgeEngine
{
    #define FORGE_DEBUG_ENABLED

	typedef unsigned int COUNTER;
	typedef unsigned int GL_ID;
	typedef int GL_RESULT;

	#define GL_NULL_ID 0

    template <typename T>
    using Array = std::vector<T>;

    template <typename T>
    using Handle = std::shared_ptr<T>;
    template <typename T>
    using Reference = std::unique_ptr<T>;
}
