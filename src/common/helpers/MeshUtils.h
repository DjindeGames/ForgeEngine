#pragma once

#include "engine/misc/Mesh.h"
#include "system/misc/Color.h"

#include <vector>

namespace ForgeEngine
{
    class Material;
    class Texture;

    namespace MeshUtils
    {
        Mesh MakeCube(float scale = 1.f, const Material* material = nullptr);
        Mesh MakePlane(float scale = 1.f, const Material* material = nullptr);
        Mesh MakeTriangle(float scale = 1.f, const Material* material = nullptr);
        Mesh MakeSphere(float scale = 1.f, const Material* material = nullptr);
    }
}
