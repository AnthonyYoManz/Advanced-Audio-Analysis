#pragma once
#include "Vector2.h"
namespace dix
{
	template <class Type>
	class Vector3
	{
	public:
		Type m_x;
		Type m_y;
		Type m_z;

		Vector3() = default;
		Vector3(const Type& _x, const Type& _y, const Type& _z)
		{
			m_x = _x;
			m_y = _y;
			m_z = _z;
		}

		Vector2<Type> xy() const
		{
			return Vector2<Type>(m_x, m_y);
		}
		Vector2<Type> xz() const
		{
			return Vector2<Type>(m_x, m_y);
		}
		Vector2<Type> yx() const
		{
			return Vector2<Type>(m_y, m_x);
		}
		Vector2<Type> yz() const
		{
			return Vector2<Type>(m_y, m_z);
		}
		Vector2<Type> zx() const
		{
			return Vector2<Type>(m_z, m_x);
		}
		Vector2<Type> zy() const
		{
			return Vector2<Type>(m_z, m_y);
		}
		Vector3<Type> xyz() const
		{
			return *this;
		}
		Vector3<Type> xzy() const
		{
			return Vector3<Type>(m_x, m_z, m_y);
		}
		Vector3<Type> yxz() const
		{
			return Vector3<Type>(m_y, m_x, m_z);
		}
		Vector3<Type> yzx() const
		{
			return Vector3<Type>(m_y, m_z, m_x);
		}
		Vector3<Type> zxy() const
		{
			return Vector3<Type>(m_z, m_x, m_y);
		}
		Vector3<Type> zyx() const
		{
			return Vector3<Type>(m_z, m_y, m_x);
		}
	};

	typedef Vector3<float> Vector3f;
	typedef Vector3<double> Vector3d;
	typedef Vector3<int> Vector3i;
	typedef Vector3<unsigned int> Vector3u;
}