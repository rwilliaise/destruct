#include <vector>

enum ComponentType { _ };

typedef unsigned int Entity;

typedef struct {
    void *data;
    ComponentType type;
    Entity owner;
} Component;

class Scene {
public:
    Scene() = default;

    inline Entity addEntity() {
        return next++;
    }

    Component* addComponent(Entity owner, void *data, ComponentType type);

private:
    std::vector<Component*> components;
    Entity next = 0;
};
