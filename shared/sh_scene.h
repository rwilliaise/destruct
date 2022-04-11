#include <vector>
#include <functional>
#include <cstdarg>

enum ComponentType { RigidBody, Mesh };

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

    void forEach(const std::function<void (Component*)>& cb, int n, ...);
    void forEach(const std::function<void (Component*)>& cb);

private:
    std::vector<Component*> components;
    Entity next = 0;
};
