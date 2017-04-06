#pragma once
namespace dix
{
	template <class Type>
	class Vector2
	{
	public:
		Type m_x;
		Type m_y;

		Vector2() = default;
		Vector2(const Type& _x, const Type& _y)
		{
			m_x = _x;
			m_y = _y;
		}

		Vector2<Type> xy() const
		{
			return *this;
		}
		Vector2<Type> yx() const
		{
			return Vector2<Type>(m_y, m_x);
		}
	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<double> Vector2d;
	typedef Vector2<int> Vector2i;
	typedef Vector2<unsigned int> Vector2u;
}