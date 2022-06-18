#pragma once
#include "Object.h"

class Sphere : public Object {
private:
    Mesh mesh;
    Material material;
public:
    Sphere();
    virtual void draw(Matrix matModel);
};