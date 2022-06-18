#include "Object.h"

class ModelObject : public Object {
    private:
        Model model;
    public:
        ModelObject(Model model);
        virtual void draw(Matrix matModel);
};