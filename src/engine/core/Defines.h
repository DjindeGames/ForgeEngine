#pragma once

#include <memory>
#include <vector>

namespace ForgeEngine
{
	typedef unsigned int COUNTER;
	typedef unsigned int GL_ID;
	typedef int GL_RESULT;

	#define GL_NULL_ID 0

    template <typename T>
    using Array = std::vector<T>;

    template <typename T>
    using Shared = std::shared_ptr<T>;
    template <typename T>
    using Unique = std::unique_ptr<T>;
}
