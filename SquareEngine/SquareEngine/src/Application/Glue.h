#pragma once

#include "../../Coral.Native/Include/Coral/Core.hpp"
#include <iostream>
#include "../../Coral.Native/Include/Coral/String.hpp"
#include <random>
#include <glm/glm.hpp>

struct Vector2
{
	float x, y;

	// Constructor
	Vector2(float x = 0, float y = 0);

	// Overload + operator
	Vector2 operator+(const Vector2& v) const;

	// Overload - operator
	Vector2 operator-(const Vector2& v) const;

	// Overload * operator (scalar multiplication)
	Vector2 operator*(float scalar) const;

	// Overload / operator (scalar division)
	Vector2 operator/(float scalar) const;

	// Overload * operator (dot product)
	float operator*(const Vector2& v) const;

	inline operator glm::vec2()
	{
		return glm::vec2(x, y);
	}

	// Print the vector (for debugging)
	void print() const;
};

struct Vector3
{
	float x, y, z;

	// Constructor
	Vector3(float x = 0, float y = 0, float z = 0);

	// Overload + operator
	Vector3 operator+(const Vector3& v) const;

	// Overload - operator
	Vector3 operator-(const Vector3& v) const;

	// Overload * operator (scalar multiplication)
	Vector3 operator*(float scalar) const;

	// Overload / operator (scalar division)
	Vector3 operator/(float scalar) const;

	// Overload * operator (dot product)
	float operator*(const Vector3& v) const;

	inline operator glm::vec3()
	{
		return glm::vec3(x, y, z);
	}

	// Print the vector (for debugging)
	void print() const;
};

struct Transform
{
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
};

inline Vector3 GlmVec3ToVec3(glm::vec3 v) { return Vector3(v.x, v.y, v.z); }
inline Vector2 GlmVec2ToVec2(glm::vec2 v) { return Vector2(v.x, v.y); }

void LSQ_LOG(Coral::String string);
Vector3 RandVector();
void UpdateTransform(Transform t, uint32_t id);
Transform GetTransform(uint32_t id);