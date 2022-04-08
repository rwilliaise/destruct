
#include "r_shared.h"

class r_Window {
public:
    ~r_Window();

    int initWindow();

private: 
    GLFWwindow *window;
};
