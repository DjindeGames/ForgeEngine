#pragma once

#include <string>

struct GLFWwindow;

namespace ForgeEngine
{
	class Game
	{
		/************************************/
		/************ATTRIBUTES**************/
		/************************************/

	public:
		GLFWwindow* m_Window{};

	private:
		void (*m_UpdateCallback)(float) {};
		bool (*m_TerminationConditionCallback)(GLFWwindow*) {};

		int m_CurrentDrawMode;

		/************************************/
		/**************METHODS***************/
		/************************************/

	public:
		Game();

		/*** Following methods should always be called, and always in the following order ***/
		//Creates a window
		bool Init(std::string name, unsigned int width, unsigned int height);
		//Binds the update callback to the current game
		void SetUpdateCallback(void (*callback)(float)) { m_UpdateCallback = callback; }
		//Optional: Sets the termination check condition
		void SetTerminationConditionCallback(bool (*callback)(GLFWwindow*)) { m_TerminationConditionCallback = callback; }
		//Handles the main loop
		void StartLoop();

	private:
		//Checks whether the game should terminate
		void CheckTermination();
		//Called by default if no TerminationConditionCallback is set
		bool DefaultTerminationCondition();
		//Checks debug related input
		void ProcessDebugInput();
		void ToggleWireframeMode();
	};
}