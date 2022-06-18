#include "Object.h"

class Cube : public Object {
    private:
        Mesh mesh;
        Material material;
    public:
        Cube();
        virtual void draw(Matrix matModel);
};