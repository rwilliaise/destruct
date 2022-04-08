#include <malloc.h>
#include "sh_scene.h"

void sh_ComponentDestroy(sh_Component *comp) {
    if (comp->parent != NULL) {
        comp->parent->next = comp->next;
    }
    if (comp->next != NULL) {
        comp->next->parent = comp->parent;
    }

    free(comp);
}

void sh_EntityDestroy(sh_Scene *scene, sh_Entity entity) {
    sh_Component *next = scene->root_comp;
    while (next != NULL) {
        if (next->owner == entity) {
            sh_Component *toDestroy = next;

            next = next->next;
            sh_ComponentDestroy(toDestroy);
        } else {
            next = next->next;
        }
    }
}

sh_Entity sh_SceneAddEnt(sh_Scene *scene) {
    return scene->next++;
}

sh_Component* sh_ScenePushComp(sh_Scene *scene, sh_Entity entity, void *data, sh_ComponentType type) {
    sh_Component* comp = malloc(sizeof(sh_Component));
    if (comp == NULL) {
        return NULL;
    }
    comp->parent = NULL;
    comp->next = NULL;
    comp->data = data;
    comp->type = type;
    comp->owner = entity;

    if (scene->last_comp != NULL) {
        scene->last_comp->next = comp;
        scene->last_comp = comp;
    }
    if (scene->root_comp == NULL) {
        scene->root_comp = comp;
        scene->last_comp = comp;
    }
    return comp;
}

void sh_SceneDestroy(sh_Scene *scene) {
    scene->last_comp = NULL;

    sh_Component *next = scene->root_comp;
    while (next != NULL) {
        sh_Component *almost = next->next;
        free(next);
        next = almost;
    }

    scene->next = 0;
}
