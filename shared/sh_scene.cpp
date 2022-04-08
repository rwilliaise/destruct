#include "sh_scene.h"
#include <cstdlib>

sh_Component* sh_Scene::addComponent(sh_Entity owner, void *data, sh_ComponentType type) {
    sh_Component *comp = (sh_Component*) malloc(sizeof(sh_Component));
    comp->data = data;
    comp->owner = owner;
    comp->type = type;
    components.push_back(comp);
    return comp;
}
