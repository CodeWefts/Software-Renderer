#include "rdr/Vertex.h"

Vertex::Vertex(const Vector3& position)
	: vPosition(position)
{
}

Vertex::Vertex(const Vector3& position, const Vector3& color)
	: vPosition(position),vColor(color)
{
}

Vertex::Vertex(const Vector3& position, const Vector3& color, const Vector3& normal, const Vector2 uv)
	: vPosition(position),vColor(color), vNormal(normal), vUvs(uv)
{
}

void Vertex::SetPosition(const Vector3& position)
{
	vPosition = position;
}

void Vertex::SetColor(const Vector3& color)
{
	vColor = color;
}

void Vertex::SetNormal(const Vector3& normal)
{
	vNormal = normal;
}

void Vertex::SetUv(const Vector2 uv)
{
	vUvs = uv;
}

void Vertex::SetPositionAndNormal(const Vector3& position)
{
	vPosition = position;
	vNormal = position.Normalize();
}
