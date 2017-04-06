#pragma once
#include <GLFW/glfw3.h>
#include "Camera.h"

namespace dix
{
	using LibWindow = GLFWwindow;
	using LibMonitor = GLFWmonitor;

	class Window
	{
	private:
		LibWindow* m_window;
		Camera m_defaultCamera;
		Camera* m_camera;
	public:
		Window();
		~Window();
		void initialise(const char* _title, unsigned int _width, unsigned int _height, LibMonitor* _monitor, LibWindow* _share);
		void cleanup();
		void pollEvents();
		void swapBuffers();
		void setAsCurrentContext();
		void setVsync(bool _enable);
		void setActiveCamera(Camera* _camera);

		bool shouldClose();
		void getSize(unsigned int* _width, unsigned int* _height) const;
		unsigned int getHeight() const;
		unsigned int getWidth() const;
		LibWindow* getWindowPointer() const;
		Camera* getActiveCamera();
		Camera* getDefaultCamera();
	};
}