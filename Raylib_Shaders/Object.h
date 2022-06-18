#pragma once
#include <vector>
#include <raylib.h>

using namespace std;

class Object {
    private:
        vector<Object*> children;
        Vector3 position;
        Vector3 rotation;
        Vector3 size;
    public:
        Object();
        void add(Object* obj);
        void render();
        void render(Matrix matModel);
        virtual void draw(Matrix matModel);
        void translate(float x, float y, float z);
        void rotateX(float value);
        void rotateY(float value);
        void rotateZ(float value);
        void scale(float value);
        Matrix getTransform();
};