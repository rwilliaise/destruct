#include <vector>

enum sh_ComponentType { _ };

typedef unsigned int sh_Entity;

typedef struct sh_Component {
    void *data;
    sh_ComponentType type;
    sh_Entity owner;
} sh_Component;

class sh_Scene {
public:
    sh_Scene() = default;

    inline sh_Entity addEntity() {
        return next++;
    }

    sh_Component* addComponent(sh_Entity owner, void *data, sh_ComponentType);

private:
    std::vector<sh_Component*> components;
    sh_Entity next;
};
