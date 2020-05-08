
#pragma once

#include <GL/glew.h>

#include "Pixel.h"


class Window {
    std::string titleStr;
    GLFWwindow* glfwWindowPtr;
    Viewport vp;
public:
    Window(size_t width, size_t height, std::string name, RangeRGBA bgColor) : glfwWindowPtr(nullptr), titleStr(name) {
        // start GL context and O/S window using the GLFW helper library
        if (!glfwInit()) {
            return;
        }

        glfwWindowPtr = glfwCreateWindow(width, height, titleStr.c_str(), NULL, NULL);

        glfwMakeContextCurrent(glfwWindowPtr);

        GLFWwindowsizefun reshapeFn = [](GLFWwindow *window, int width, int height) -> void {
            // Set the viewport to cover the new window
            glViewport(0, 0, width, height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0.0, width, height, 0.0, 0.0, 100.0);
            glMatrixMode(GL_MODELVIEW);
            //display();
        };
        glfwSetWindowSizeCallback(glfwWindowPtr, reshapeFn);

        vp.create(width, height, bgColor);
    }

    std::string title() { return titleStr; }

    void title(std::string name) {
        titleStr = name;
        glfwSetWindowTitle(glfwWindowPtr, titleStr.c_str());
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
