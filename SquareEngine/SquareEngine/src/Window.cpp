#include "Window.h"
#include <Texture2D.h>

namespace Square
{
	Window::Window(int width, int height, const char* title, bool main)
	{
		this->width = width;
		this->height = height;

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		
		window = glfwCreateWindow(width, height, title, NULL, NULL);
		
		if (window == NULL)
		{
			Log("Failed to create GLFW window");
			glfwTerminate();
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			Log("Failed to initialize GLAD");
		}
		
		glViewport(0, 0, width, height);

		if (main)
			activeWindow = this;

		glfwSetScrollCallback(window, scroll_callback);
	}

	void Window::EndFrame()
	{
		glfwGetWindowSize(window, &width, &height);

		glViewport(0, 0, width, height);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(window);
	}

	double Window::GetTime()
	{
		return glfwGetTime();
	}

	GLFWwindow* Window::GetWindow()
	{
		return window;
	}

	void Window::Flush()
	{
		glfwTerminate();
	}

	Window::operator bool()
	{
		return !ShouldClose();
	}

	void SetActiveWindow(Window* window)
	{
		activeWindow = window;
	}

	Window* GetActiveWindow()
	{
		return activeWindow;
	}

	bool IsKeyDown(int key)
	{
		return glfwGetKey(activeWindow->GetWindow(), key) == GLFW_PRESS;
	}

	bool IsKeyUp(int key)
	{
		return glfwGetKey(activeWindow->GetWindow(), key) == GLFW_RELEASE;
	}

	glm::vec2 GetMousePosition()
	{
		double xpos, ypos;
		glfwGetCursorPos(activeWindow->GetWindow(), &xpos, &ypos);

		return glm::vec2(xpos, ypos);
	}

	bool IsMouseDown(int button)
	{
		return glfwGetMouseButton(activeWindow->GetWindow(), button) == GLFW_PRESS;
	}

	bool IsMouseUp(int button)
	{
		return glfwGetMouseButton(activeWindow->GetWindow(), button) == GLFW_RELEASE;
	}

	float GetMouseScroll()
	{
		return scroll;
	}

	void ReceivedScroll()
	{
		scroll = 0;
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		scroll += yoffset;
	}
}

