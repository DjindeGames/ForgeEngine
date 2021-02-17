#pragma once

#include "engine/core/Game.h"

using namespace ForgeEngine;

namespace PapierKraft
{
	class PapierKraft : public Game
	{
		using Mother = Game;

		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		public:
			static GLFWwindow* m_Window;

		private:
			int m_CurrentDrawMode;
			int m_Framerate;

		/************************************/
		/**************METHODS***************/
		/************************************/

		protected:
			virtual void OnInit() override;
			virtual void OnUpdate(float dT) override;
			virtual void OnTermination() override;

			virtual bool ShouldTerminate() override;
	};
}