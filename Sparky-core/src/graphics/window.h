#pragma once

#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace sparky { namespace graphics {

#define MAX_KEYS	1024
#define MAX_BUTTONS 32

	class Window
	{
	private:
		const char *m_Title;
		int m_Width, m_Height;
		GLFWwindow *m_Window;
		bool m_Closed;

		static bool m_Keys[MAX_KEYS];
		static bool m_MouseButtons[MAX_BUTTONS];
		static double m_MX, m_MY;
	public:
		Window(const char *m_Title, int m_Width, int m_Height);
		~Window();
		void clear();
		bool closed() const;
		void update();

		// Getters
		inline int getWidth() const { return m_Width; };
		inline int getHeight() const { return m_Height; };

		bool isKeyPressed(unsigned int keyCode) const { if(keyCode >= 0 && keyCode <= MAX_KEYS) return m_Keys[keyCode]; }
		bool isMouseButtonPressed(unsigned int button) const { if (button >= 0 && button <= MAX_BUTTONS) return m_MouseButtons[button]; }
		void getMousePos(double& x, double& y) const { x = m_MX; y = m_MY; }

	private:
		bool init();
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void cursor_pos_callback(GLFWwindow* window, double xPos, double yPos);
	};

} }