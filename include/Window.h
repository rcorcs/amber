
#pragma once

#include "Graphics/Pixel.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>

class Window;

class Context {
public:
  Window *window;
  Context() {}
  Context(Window *window) : window(window) {}
};

static std::map<GLFWwindow*,Context> globalContexts;

class Window {
    std::string titleStr;
    GLFWwindow* glfwWindowPtr;
    Viewport vp;
public:
    std::function<void (Window &, int, int, int, int)> keyEventHandler;
    Window(size_t width, size_t height, std::string name, RangeRGBA bgColor) : glfwWindowPtr(nullptr), titleStr(name) {
        // start GL context and O/S window using the GLFW helper library
        if (!glfwInit()) {
            return;
        }

        glfwWindowPtr = glfwCreateWindow(width, height, titleStr.c_str(), NULL, NULL);
        globalContexts[glfwWindowPtr] = Context(this);

        glfwMakeContextCurrent(glfwWindowPtr);

        auto reshapeFn = [](GLFWwindow *window, int width, int height) -> void {
            // Set the viewport to cover the new window
            glViewport(0, 0, width, height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0.0, width, height, 0.0, 0.0, 100.0);
            glMatrixMode(GL_MODELVIEW);
            //display();
        };
        glfwSetWindowSizeCallback(glfwWindowPtr, reshapeFn);

        auto keyEvent = [](GLFWwindow* glfwWindowPtr, int key, int scancode, int action, int mode) {
          Window *window = globalContexts[glfwWindowPtr].window;
          window->keyEventHandler(*window, key, scancode, action, mode);
        };
        glfwSetKeyCallback(glfwWindowPtr, keyEvent);

        vp.create(width, height, bgColor);
    }

    std::string title() { return titleStr; }

    void title(std::string name) {
        titleStr = name;
        glfwSetWindowTitle(glfwWindowPtr, titleStr.c_str());
    }

    void close() {
      glfwSetWindowShouldClose(glfwWindowPtr, GL_TRUE);
    }

    size_t width() {
        int w, h;
        glfwGetWindowSize(glfwWindowPtr, &w, &h);
        return w;
    }

    size_t height() {
        int w, h;
        glfwGetWindowSize(glfwWindowPtr, &w, &h);
        return h;
    }

    void runUntilClosed(std::function<void (Viewport &)> fn) {
        while(!glfwWindowShouldClose(glfwWindowPtr)) {
            glfwPollEvents();
            vp.clear();
            fn(vp);
            glfwSwapBuffers(glfwWindowPtr);
        }
    }

    void release() {
      glfwTerminate();
    }
};
