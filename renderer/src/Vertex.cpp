#include "rdr/Vertex.h"

Vertex::Vertex(const Vector3& position)
	: m_Position(position)
{
}

Vertex::Vertex(const Vector3& position, const Vector3& color)
	: m_Position(position), m_Color(color)
{
}

Vertex::Vertex(const Vector3& position, const Vector3& color, const Vector3& normal, const Vector2 uv)
	: m_Position(position), m_Color(color), m_Normal(normal), m_Uvs(uv)
{
}

void Vertex::SetPosition(const Vector3& position)
{
	m_Position = position;
}

void Vertex::SetColor(const Vector3& color)
{
	m_Color = color;
}

void Vertex::SetNormal(const Vector3& normal)
{
	m_Normal = normal;
}

void Vertex::SetUv(const Vector2 uv)
{
	m_Uvs = uv;
}

void Vertex::SetPositionAndNormal(const Vector3& position)
{
	m_Position = position;
	m_Normal = position.Normalize();
}
