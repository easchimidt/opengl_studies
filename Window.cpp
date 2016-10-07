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

Window::Window(Scene *_scene, int _width, int _height, std::string _title) :
        scene(_scene), width(_width), height(_height), title(_title)  {
    scene_copy_for_handlers = _scene;
}

Window::Window(Scene *_scene, std::string _title) : Window(_scene, 800, 600, _title) {}

Window::Window(Scene *_scene) : Window(_scene, 800, 600, "Window") {}

void Window::init() {

    if (glfwInit() != GLFW_TRUE) {
        throw std::invalid_argument("Error initiating GLFW." );
        exit(1);
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (window == NULL) {
        throw std::invalid_argument("Error creating Window." );
        glfwTerminate();
        exit(1);
    }

    glfwSetKeyCallback(window, Window::KeyPressedHandler);

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

    typedef high_resolution_clock Time;
    typedef duration<float> fsec;

    auto before = Time::now();
    while ( glfwWindowShouldClose(window) == GLFW_FALSE ) {
        auto fs = Time::now() - before;
        before = Time::now();
        float time = duration_cast<fsec>(fs).count();
        scene->update(time);
        scene->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    scene->deinit();
}

void Window::show() {
    init();
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
