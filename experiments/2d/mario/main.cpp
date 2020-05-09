
#include <string>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Graphics/Image.h"
#include "Graphics/Texture.h"

#include "Graphics/Viewport.h"

#include "Physics/Force.h"
#include "Physics/Body.h"

#include "Window.h"

class Entity2D : public Body<2> {
    Texture &texture;
    bool fill;

    int facing;
public:
    Entity2D(Texture &texture, bool fill = false) :
        texture(texture), fill(fill), facing(1) {}

    Entity2D(Texture &texture, float x, float y) :
        texture(texture), fill(false), facing(1), Body<2>(x,y) {}

    size_t width() { return texture.width(); }
    size_t height() { return texture.height(); }

    void render(Viewport &vp) {
        glBindTexture( GL_TEXTURE_2D, texture.glId() ); /* Binding of texture name */
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
            if (acceleration().x() < 0) facing = -1;
            else if(acceleration().x() > 0) facing = 1;
            if (facing < 0) {
                /* Draw a quad */
                glBegin(GL_QUADS);
                    glTexCoord2i(1, 0); glVertex2i(x(), y());
                    glTexCoord2i(1, 1); glVertex2i(x(), y() + height());
                    glTexCoord2i(0, 1); glVertex2i(x() + width(), y() + height());
                    glTexCoord2i(0, 0); glVertex2i(x() + width(), y());
                glEnd();
            } else {
                /* Draw a quad */
                glBegin(GL_QUADS);
                    glTexCoord2i(0, 0); glVertex2i(x(), y());
                    glTexCoord2i(0, 1); glVertex2i(x(), y() + height());
                    glTexCoord2i(1, 1); glVertex2i(x() + width(), y() + height());
                    glTexCoord2i(1, 0); glVertex2i(x() + width(), y());
                glEnd();                
            }
        }
    }
};

#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480

int main(int argc, char **argv) {

    Window window(1280, 720, "Mario", false, RangeRGBA(0,0,0,0));

    Texture marioTexture = TextureIO::loadFromFile("assets/mario.png");
    Texture bgTexture = TextureIO::loadFromFile("assets/background.jpg");

    Force<2> gravity = Force2D::down(1.f);

    size_t floor = 625;
    const auto floorY = floor-marioTexture.height();

    Entity2D mario(marioTexture, 10, floorY);
    Entity2D background(bgTexture, true);
    
    auto renderer = [&](Viewport &vp) {
        background.render(vp);
        mario.render(vp);
        mario.move();

        mario.apply(gravity);

        if (mario.x() < 0) mario.x(0);
        if (mario.x() + mario.width() > vp.width())
            mario.x(vp.width()-mario.width());
        
        if (mario.y() > floorY) {
            mario.y(floorY);
            mario.acceleration().y(0);
        }
    };

    window.keyEventHandler = [&](Window &window, int key, int scancode, int action, int mode) -> void {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) window.close();

        switch(key) {
        case GLFW_KEY_RIGHT:
            if (action == GLFW_PRESS) {
                mario.apply(Force2D::right(5));
            }
            if (action == GLFW_RELEASE) {
                mario.apply(Force2D::left(5));
            }
            break;
        case GLFW_KEY_LEFT:
            if (action == GLFW_PRESS) {
                mario.apply(Force2D::left(5));
            }
            if (action == GLFW_RELEASE) {
                mario.apply(Force2D::right(5));
            }            
            break;
        case GLFW_KEY_SPACE:
            if (action == GLFW_PRESS) {
                if (mario.y()==floorY)
                   mario.apply(Force2D::up(20));
            }
            break;
        }
    };
    window.runUntilClosed(renderer);

    marioTexture.release();
    bgTexture.release();
    window.release();
}
