#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Rectangle.h"
namespace dix
{
	class Camera
	{
	private:
		Vector3f m_position;
		Vector2f m_size;
		IntRect m_viewport;
	public:
		Camera() = default;
		Camera(const Vector3f& _position);
		Camera(const Vector3f& _position, const Vector2f& _size);
		Camera(const Vector3f& _position, const Vector2f& _size, const IntRect& _viewport);

		void setPosition(const Vector3f& _position);
		void setPosition(float _x, float _y, float _z);
		void setSize(const Vector2f& _size);
		void setSize(float _width, float _height);
		void setViewport(const IntRect& _viewport);
		void setViewport(int _x, int _y, int _width, int _height);

		const Vector3f& getPosition() const;
		const Vector2f& getSize() const;
		const IntRect& getViewport() const;
	};
}