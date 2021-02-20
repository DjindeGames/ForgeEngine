#pragma once

#include "engine/core/Object.h"

#include <string>

struct GLFWwindow;

namespace ForgeEngine
{
	class GameHandler : Object
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

		public:
			static GLFWwindow* m_Window;

		/************************************/
		/**************METHODS***************/
		/************************************/

		public:
			/*** Following methods should always be called, and always in the following order ***/
			//Creates a window
			bool Init(std::string name, unsigned int width, unsigned int height);
			//Handles the main loop
			void HandleProcess();

		protected:
			virtual void OnInit();
			virtual void OnUpdate(float dT) {}
			virtual void OnTermination();

			virtual bool ShouldTerminate();
	};
}