//
// Created by Emanuel Schimidt on 30/09/16.
//

#include <chrono>
#include <stdexcept>

#include "Window.h"

using namespace std;

// Unfortunatelly, to make our Scene class handle inputs we have to copy
// its pointer to a global variable. Then, it can be accessed in
// static function Window::KeyPressedHandler, which calls the scene
// handler to wherever callbacks. This is need because GLFW is implemented
// in C, which do not have a this 'hidden' as the first parameter as C++.
// So, to work around it, we have to use a static function. But, this function
// cannot access object members, and we need to get a copy of the pointer.
// This is exactly the solution suggested by GLFW in its FAQ, question 2.16.
Scene* scene_copy_for_handlers;

Window::Window(Scene *_scene, int _width, int _height, std::string _title, bool _use_mouse) :
        scene(_scene), width(_width), height(_height), title(_title), use_mouse(_use_mouse)  {
    scene_copy_for_handlers = _scene;
}

Window::Window(Scene *_scene, std::string _title) : Window(_scene, 800, 600, _title, false) {}

Window::Window(Scene *_scene, bool use_mouse) : Window(_scene, 800, 600, "Window", use_mouse) {}

Window::Window(Scene *_scene) : Window(_scene, 800, 600, "Window", false) {}

void Window::init() {

    if (glfwInit() != GLFW_TRUE) {
        throw std::invalid_argument("Error initiating GLFW.");
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (window == NULL) {
        glfwTerminate();
        throw std::invalid_argument("Error creating Window.");
    }

    glfwSetKeyCallback(window, Window::KeyPressedHandler);

    if (use_mouse) {
        glfwSetCursorPosCallback(window, Window::MousePosHandler);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwSetScrollCallback(window, Window::MouseScrollHandler);
    }

    // Get the resolution of the primary monitor
    const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    // Center our window
    glfwSetWindowPos(
            window,
            (vidmode->width - width) / 2,
            (vidmode->height - height) / 2
    );

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwShowWindow(window);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Window::loop() {
    using namespace std::chrono;

    scene->init();

    GLfloat before = glfwGetTime();
    while ( glfwWindowShouldClose(window) == GLFW_FALSE ) {
        GLfloat delta = glfwGetTime() - before;
        before = glfwGetTime();

        scene->update(delta);
        scene->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    scene->deinit();
}

void Window::show() {
    try {
        init();
    }
    catch (std::invalid_argument& ia) {
        std::cerr << "Error scene initialization. " << ia.what() << std::endl;
        exit(1);
    }
    loop();
    glfwDestroyWindow(window);
    delete this;
}

Window::~Window() {
    glfwTerminate();
}

void Window::KeyPressedHandler (GLFWwindow *window, int key, int scancode, int action, int mods) {
    scene_copy_for_handlers->keyPressed(window, key, scancode, action, mods);
}

void Window::MousePosHandler(GLFWwindow* window, double xpos, double ypos) {
    scene_copy_for_handlers->mousePos(window, xpos, ypos);
}

void Window::MouseScrollHandler(GLFWwindow* window, double xpos, double ypos) {
    scene_copy_for_handlers->mouseScroll(window, xpos, ypos);
}
