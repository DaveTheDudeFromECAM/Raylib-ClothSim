#include "ModelObject.h"
#include <raylib.h>

ModelObject::ModelObject(Model model) {
    this->model = model;
}

void ModelObject::draw(Matrix matModel) {
    model.transform = matModel;
    DrawModel(model, {0.0f, 0.0f, 0.0f}, 1.0f, WHITE);
}