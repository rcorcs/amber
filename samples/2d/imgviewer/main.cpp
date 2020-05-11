
#include <string>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Graphics/Image.h"
#include "Graphics/Texture.h"

#include "Graphics/Viewport.h"
#include "Window.h"

class Entity2D {
    Texture &texture;
public:
    Entity2D(Texture &texture) : texture(texture) {}
    void render(Viewport &vp) {
        int w = vp.width(), h = vp.height();
        /* Draw a quad */
        glBegin(GL_QUADS);
            glTexCoord2i(0, 0); glVertex2i(0,   0);
            glTexCoord2i(0, 1); glVertex2i(0,   h);
            glTexCoord2i(1, 1); glVertex2i(w, h);
            glTexCoord2i(1, 0); glVertex2i(w, 0);
        glEnd();
    }
};

#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480

int main(int argc, char **argv) {
    if ( argc < 1) {
        /* no image file to  display */
        return -1;
    }

    Window window(DEFAULT_HEIGHT, DEFAULT_WIDTH, "Image Viewer", true, RangeRGBA(1,1,1,1));

    Texture image = TextureIO::loadFromFile(argv[1]);
    if ( image.empty() ) {
        printf("Can't load image file %s\n", argv[1]);
        return -1;
    }

    window.resize(image.height(),image.width());

    Entity2D img2d(image);

    auto renderer = [&](Viewport &vp) {
        img2d.render(vp);
    };

    window.runUntilClosed(renderer);

    image.release();
    window.release();
}
