#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Debug.h>
#include <glm/glm.hpp>

namespace Square
{
	class Window
	{
	public:
		Window(int width, int height, const char* title, bool main);

		void EndFrame();
		
		bool ShouldClose();

		double GetTime();

		GLFWwindow* GetWindow();

		void Flush();

	public:
		operator bool();
	public:
		int width = 0;
		int height = 0;
	private:
		GLFWwindow* window;
	};

	inline Window* activeWindow;
	void SetActiveWindow(Window* window);
	Window* GetActiveWindow();

	bool IsKeyDown(int key);
	bool IsKeyUp(int key);

	glm::vec2 GetMousePosition();
	bool IsMouseDown(int button);
	bool IsMouseUp(int button);
}