#include "../include/rdr/light.h"

Vector3 Light::AmbientLighting()
{
    float ambientStrength = 0.3f;

    Vector3 ambient = Vector3(1.f, 1.f, 1.f / ambientStrength) * ambientStrength;
    return ambient;
}

Light::Light(Vector3 position, Vector3 ambient, Vector3 diffuse, Vector3 specular)
{
}

Vector3 Light::Reflect(Vector3 LightDir, Vector3 normal)
{
    Vector3 reflect = LightDir - normal.Normalize() * (2 * Vector3::DotProduct(LightDir, normal.Normalize()));
    return reflect;
}

Vector3 Light::DiffuseLighting(Vector3 normal, Vector3 lightDir)
{
    float diffuse = std::max(Vector3::DotProduct(normal, lightDir.Normalize()), 0.0f);
    return diffuse;

}

Vector3 Light::SpecularLighting(Vector3 viewPos, Vector3 normal, Vector3 lightDir, Vector3 FragPos)
{
    Vector3 viewDir = (viewPos - FragPos).Vector3::Normalize();
    Vector3 reflectDir = Reflect(-lightDir, normal);

    float spec = pow(std::max(Vector3::DotProduct(viewDir, reflectDir), 0.0f), 32);
    return spec;
}

Vector3 Light::GlobalLighting(Vector3 normal, Vector3 lightDir, Vector3 objectColor, Vector3 FragPos, Vector3 viewpos)
{
    Vector3 result = (AmbientLighting() + DiffuseLighting(normal, lightDir) /* + SpecularLighting(viewpos, normal, lightDir, FragPos)*/) * objectColor;
    Vector3 FragColor = Vector3(result.x, result.y, result.z);
    return FragColor;
}
