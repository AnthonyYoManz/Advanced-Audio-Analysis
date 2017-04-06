#include "Camera.h"
namespace dix
{
	Camera::Camera(const Vector3f& _position)
	{
		m_position = _position;
	}

	Camera::Camera(const Vector3f& _position, const Vector2f& _size)
	{
		m_position = _position;
		m_size = _size;
	}

	Camera::Camera(const Vector3f& _position, const Vector2f& _size, const IntRect& _viewport)
	{
		m_position = _position;
		m_size = _size;
		m_viewport = _viewport;
	}

	void Camera::setPosition(const Vector3f& _position)
	{
		m_position = _position;
	}

	void Camera::setPosition(float _x, float _y, float _z)
	{
		m_position = Vector3f(_x, _y, _z);
	}

	void Camera::setSize(const Vector2f& _size)
	{
		m_size = _size;
	}

	void Camera::setSize(float _width, float _height)
	{
		m_size = Vector2f(_width, _height);
	}

	void Camera::setViewport(const IntRect& _viewport)
	{
		m_viewport = _viewport;
	}

	void Camera::setViewport(int _x, int _y, int _width, int _height)
	{
		m_viewport = IntRect(_x, _y, _width, _height);
	}

	const Vector3f& Camera::getPosition() const
	{
		return m_position;
	}

	const Vector2f& Camera::getSize() const
	{
		return m_size;
	}

	const IntRect& Camera::getViewport() const
	{
		return m_viewport;
	}
}