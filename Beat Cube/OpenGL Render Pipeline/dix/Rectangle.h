#pragma once
#include "Vector2.h"
namespace dix
{
	template <class Type>
	class Rectangle
	{
	public:
		Vector2<Type> m_position;
		Vector2<Type> m_size;

		Rectangle() = default;
		Rectangle(const Vector2<Type>& _position, const Vector2<Type>& _size)
		{
			m_position = _position;
			m_size = _size;
		}
		Rectangle(const Type& _x, const Type& _y, const Type& _width, const Type& _height)
		{
			m_position = Vector2<Type>(_x, _y);
			m_size = Vector2<Type>(_width, _height);
		}

		Type getX() const
		{
			return m_position.m_x;
		}
		Type getY() const
		{
			return m_position.m_y;
		}
		Type getWidth() const
		{
			return m_size.m_x;
		}
		Type getHeight() const
		{
			return m_size.m_y;
		}
	};

	typedef Rectangle<float> FloatRect;
	typedef Rectangle<double> DoubleRect;
	typedef Rectangle<int> IntRect;
	typedef Rectangle<unsigned int> UIntRect;
}