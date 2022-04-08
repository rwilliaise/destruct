#pragma once

typedef unsigned int sh_Entity;

typedef enum { _ } sh_ComponentType;

// represents one component
typedef struct sh_Component {
    struct sh_Component *next;
    struct sh_Component *parent;
    void *data;
    sh_ComponentType type;
    sh_Entity owner;
} sh_Component;

// represents one scene
typedef struct {
    sh_Component *root_comp;
    sh_Component *last_comp;
    sh_Entity next;
} sh_Scene;

// remove a component from the list (won't be searched)
void sh_ComponentDestroy(sh_Component *comp);

// remove an entity from the scene
void sh_EntityDestroy(sh_Scene *scene, sh_Entity entity);

// add new entity
sh_Entity sh_SceneAddEnt(sh_Scene *scene);

// add new component to entity
sh_Component* sh_ScenePushComp(sh_Scene *scene, sh_Entity entity, void *data, sh_ComponentType type);

// reset scene
void sh_SceneDestroy(sh_Scene *scene);
