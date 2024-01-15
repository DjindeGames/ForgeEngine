#pragma once

#include "engine/core/Object.h"

namespace ForgeEngine
{
    class LoadableResource : public Object
    {
        public:
            virtual bool IsValid() const = 0;
    };
}
