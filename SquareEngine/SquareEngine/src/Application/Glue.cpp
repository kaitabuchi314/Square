#include "Glue.h"
#include <Debug.h>
#include <ECSManager.h>

// Vector2 implementation

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2 Vector2::operator+(const Vector2& v) const
{
	return Vector2(x + v.x, y + v.y);
}

Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(x - v.x, y - v.y);
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(float scalar) const
{
	return Vector2(x / scalar, y / scalar);
}

float Vector2::operator*(const Vector2& v) const
{
	return x * v.x + y * v.y;
}

void Vector2::print() const
{
	std::cout << "Vector2(" << x << ", " << y << ")\n";
}

// Vector3 implementation

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3 Vector3::operator+(const Vector3& v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator*(float scalar) const
{
	return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator/(float scalar) const
{
	return Vector3(x / scalar, y / scalar, z / scalar);
}

float Vector3::operator*(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

void Vector3::print() const
{
	std::cout << "Vector3(" << x << ", " << y << ", " << z << ")\n";
}

void LSQ_LOG(Coral::String string)
{
	Square::AddMessageToConsole((std::string)string);
}

Vector3 RandVector()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

	return Vector3(dist(mt), dist(mt), dist(mt));
}

void UpdateTransform(Transform t, uint32_t uuid)
{
	Square::GetActiveScene()->UpdateTransform(Square::TransformComponent(t.position, t.rotation, t.scale), uuid);
}

Transform GetTransform(uint32_t id)
{
	Square::TransformComponent tc = Square::GetActiveScene()->GetComponent<Square::TransformComponent>(Square::GetActiveScene()->GetEntityByUUID(id));
	return Transform { GlmVec3ToVec3(tc.position), GlmVec3ToVec3(tc.rotation), GlmVec3ToVec3(tc.scale) };
}
