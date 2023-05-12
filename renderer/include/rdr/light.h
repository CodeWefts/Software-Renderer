#pragma once
#include "../include/ToolBox/Vector3.hpp"
#include "../include/ToolBox/Vector4.hpp"
#include <cmath>

class Light
{
public:
    Vector3 Ambient;
    Vector3 Diffuse;
    Vector3 Specular;

    Light(Vector3 position, Vector3 ambient, Vector3 diffuse, Vector3 specular);

    Vector3 Reflect(Vector3 LightDir, Vector3 normal);
    Vector3 AmbientLighting();
    Vector3 DiffuseLighting(Vector3 normal, Vector3 lightDir);
    Vector3 SpecularLighting(Vector3 viewPos, Vector3 normal, Vector3 lightDir, Vector3 FragPos);
    Vector3 GlobalLighting(Vector3 normal, Vector3 lightDir, Vector3 objectColor, Vector3 FragPos, Vector3 viewpos);
};