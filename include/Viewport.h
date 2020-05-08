
#pragma once

#include <GL/glew.h>

#include "Pixel.h"

class Viewport {
    RangeRGBA bgColor;
public:
    Viewport() {}
    
    Viewport(size_t width, size_t height, RangeRGBA bgColor) : bgColor(bgColor) {
        create(width,height,bgColor);
    }

    void create(size_t width, size_t height, RangeRGBA bgColor) {
        this->bgColor.red(bgColor.red());
        this->bgColor.green(bgColor.green());
        this->bgColor.blue(bgColor.blue());
        this->bgColor.alpha(bgColor.alpha());

        glViewport(0, 0, width, height); // use a screen size of WIDTH x HEIGHT
        glEnable(GL_TEXTURE_2D);     // Enable 2D texturing
        
        glMatrixMode(GL_PROJECTION);     // Make a simple 2D projection on the entire window
        glLoadIdentity();
        glOrtho(0.0, width, height, 0.0, 0.0, 100.0);

        glMatrixMode(GL_MODELVIEW);    // Set the matrix mode to object modeling

        glClearColor(bgColor.red(),bgColor.green(),bgColor.blue(),bgColor.alpha()); 
        glClearDepth(0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window
    }

    size_t x() {
        GLint data[4]; //x,y,width,height
        glGetIntegerv(GL_VIEWPORT,data);
        return data[0];
    }

    size_t y() {
        GLint data[4]; //x,y,width,height
        glGetIntegerv(GL_VIEWPORT,data);
        return data[1];
    }

    size_t width() {
        GLint data[4]; //x,y,width,height
        glGetIntegerv(GL_VIEWPORT,data);
        return data[2];
    }

    size_t height() {
        GLint data[4]; //x,y,width,height
        glGetIntegerv(GL_VIEWPORT,data);
        return data[3];
    }

    void clear() {
        glClearColor(bgColor.red(),bgColor.green(),bgColor.blue(),bgColor.alpha()); 
        glClearDepth(0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};
