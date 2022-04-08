#include <GL/glew.h>
#include <GLFW/glfw3.h>

class r_State {
public:
    r_State();
    ~r_State();

    void loop();

private:
    GLFWwindow *window;
};
