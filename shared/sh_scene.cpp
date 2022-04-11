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

void Scene::forEach(const std::function<void(Component*)>& cb, int n, ...) {
    va_list args;
    va_start(args, n);

    int i;
    ComponentType val;
    for (i = 0; i < n; i++) {
        val = va_arg(args, ComponentType);
        for (auto c : components) {
            if (c->type == val) {
                cb(c);
            }
        }
    }

    va_end(args);
}

void Scene::forEach(const std::function<void(Component *)> &cb) {
    for (auto c : components) {
        cb(c);
    }
}
