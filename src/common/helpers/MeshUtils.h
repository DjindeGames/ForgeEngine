#pragma once

#include "engine/misc/Mesh.h"
#include "system/misc/Color.h"

#include <vector>

namespace ForgeEngine
{
    class Texture;

    namespace MeshUtils
    {
        Mesh MakeCube(float scale = 1.f, const Color& renderColor = COLOR_MAGENTA, const Texture* texture = nullptr);
        Mesh MakePlane(float scale = 1.f, const Color& renderColor = COLOR_MAGENTA, const Texture* texture = nullptr);
        Mesh MakeTriangle(float scale = 1.f, const Color& renderColor = COLOR_MAGENTA, const Texture* texture = nullptr);
        Mesh MakeSphere(float scale = 1.f, const Color& renderColor = COLOR_MAGENTA, const Texture* texture = nullptr);
    }
}
