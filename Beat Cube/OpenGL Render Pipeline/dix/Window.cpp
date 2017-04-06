#include "Window.h"
#include <iostream>
namespace dix
{
	Window::Window()
	{
		m_window = nullptr;
	}

	Window::~Window()
	{
		cleanup();
	}

	void Window::initialise(const char * _title, unsigned int _width, unsigned int _height, LibMonitor * _monitor, LibWindow * _share)
	{
		if (!glfwInit())
		{
			std::cout << "GLFW failed to init\n";
		}
		m_window = glfwCreateWindow(_width, _height, _title, _monitor, _share);
		if (!m_window)
		{
			std::cout << "Something went wrong when creating the window\n";
		}
		m_defaultCamera = Camera(Vector3f(0, 0, 0), Vector2f(_width, _height), IntRect(0, 0, _width, _height));
		setActiveCamera(nullptr);
	}

	void Window::cleanup()
	{
		if (m_window)
		{
			glfwDestroyWindow(m_window);
			m_window = nullptr;
		}
		if (glfwInit())
		{
			glfwTerminate();
		}
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}

	void Window::setAsCurrentContext()
	{
		glfwMakeContextCurrent(m_window);
	}

	void Window::setVsync(bool _enable)
	{
		if (_enable)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
	}

	void Window::setActiveCamera(Camera * _camera)
	{
		if (_camera)
		{
			m_camera = _camera;
		}
		else
		{
			m_camera = &m_defaultCamera;
		}
	}

	void Window::pollEvents()
	{
		glfwPollEvents();
	}

	bool Window::shouldClose()
	{
		return glfwWindowShouldClose(m_window);
	}

	void Window::getSize(unsigned int * _width, unsigned int * _height) const
	{
		int width, height;
		glfwGetWindowSize(m_window, &width, &height);
		*_width = width;
		*_height = height;
	}

	unsigned int Window::getHeight() const
	{
		int height;
		glfwGetWindowSize(m_window, NULL, &height);
		return height;
	}

	unsigned int Window::getWidth() const
	{
		int width;
		glfwGetWindowSize(m_window, &width, NULL);
		return width;
	}

	LibWindow * Window::getWindowPointer() const
	{
		return m_window;
	}

	Camera* Window::getActiveCamera()
	{
		return m_camera;
	}

	Camera* Window::getDefaultCamera()
	{
		return &m_defaultCamera;
	}
}