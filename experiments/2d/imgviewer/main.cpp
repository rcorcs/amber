
#include <string>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Image.h"
#include "Texture.h"

#include "Viewport.h"
#include "Window.h"

class Entity2D {
    Vector<float, 2> pos;
    Texture &texture;
    bool fill;
public:
    Entity2D(Texture &texture, bool fill = false) :
        texture(texture), fill(fill) {}

    void position(size_t x, size_t y) {
        pos.x(x);
        pos.y(y);
    }

    void render(Viewport &vp) {
        //glBindTexture( GL_TEXTURE_2D, texture.glId() ); /* Binding of texture name */
        if (fill) {
            int w = vp.width(), h = vp.height();
            /* Draw a quad */
            glBegin(GL_QUADS);
                glTexCoord2i(0, 0); glVertex2i(0,   0);
                glTexCoord2i(0, 1); glVertex2i(0,   h);
                glTexCoord2i(1, 1); glVertex2i(w, h);
                glTexCoord2i(1, 0); glVertex2i(w, 0);
            glEnd();
        } else {
            /* Draw a quad */
            glBegin(GL_QUADS);
                glTexCoord2i(0, 0); glVertex2i(pos.x(), pos.y());
                glTexCoord2i(0, 1); glVertex2i(pos.x(), pos.y() + texture.height());
                glTexCoord2i(1, 1); glVertex2i(pos.x() + texture.width(), pos.y() + texture.height());
                glTexCoord2i(1, 0); glVertex2i(pos.x() + texture.width(), pos.y());
            glEnd();
        }
    }
};

#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480

int main(int argc, char **argv) {
    if ( argc < 1) {
        /* no image file to  display */
        return -1;
    }

    Image image = ImageIO::loadFromFile(argv[1]);
    if ( image.begin()==nullptr ) {
        printf("Can't load picture file %s\n", argv[1]);
        return -1;
    }

    Window window(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Image Viewer", RangeRGBA(1,1,1,1));

    Texture texture(image);
    image.release();

    Entity2D img2d(texture, /*fillwindow=*/true);

    auto renderer = [&](Viewport &vp) {
        img2d.render(vp);
    };

    window.runUntilClosed(renderer);

    texture.release();
    window.release();
}
