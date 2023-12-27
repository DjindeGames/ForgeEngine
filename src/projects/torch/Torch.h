#pragma once

#include "engine/core/GameHandler.h"

using namespace ForgeEngine;

namespace Torch
{
    class Torch : public GameHandler
    {
        using Mother = GameHandler;

        public:
            Torch(std::string name, unsigned int width, unsigned int height);

        protected:
            virtual void OnInit() override;
            virtual void OnUpdate(float dT) override;
            virtual void OnTermination() override;

            virtual bool ShouldTerminate() override;
    };
}