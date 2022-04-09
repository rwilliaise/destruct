#include "sh_scene.h"
#include <cstdlib>

Component* Scene::addComponent(Entity owner, void *data, ComponentType type) {
    auto *comp = (Component*) malloc(sizeof(Component));
    comp->data = data;
    comp->owner = owner;
    comp->type = type;
    components.push_back(comp);
    return comp;
}
