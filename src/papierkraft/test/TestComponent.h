#pragma once

#include "engine/core/Component.h"

namespace PapierKraft
{
	using namespace ForgeEngine;

	class TestComponent : public Component
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/


		/************************************/
		/**************METHODS***************/
		/************************************/
		public:
			virtual void OnUpdate(float dT) override;
	};

}