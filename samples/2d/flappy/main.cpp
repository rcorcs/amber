
#include <cmath>
#include <cstdlib>
#include <time.h>

#include <string>
#include <list>
#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Graphics/Image.h"
#include "Graphics/Texture.h"

#include "Graphics/Viewport.h"

#include "Physics/Force.h"
#include "Physics/Body.h"

#include "Window.h"

class Entity2D : public BoxBody<2> { 
public:
    Entity2D() {}

    RangeRGBA color;

    void boundInside(Viewport &vp) {
        float marginWidth = width()/2.f;
        float marginHeight = height()/2.f;

        if (x() - marginWidth < 0) x(marginWidth);
        if (x() + marginWidth > vp.width())
            x(vp.width()-marginWidth);

        if (y() - marginHeight < 0) y(marginHeight);
        if (y() + marginHeight > vp.height())
            y(vp.height()-marginHeight);
    }

    void render(Viewport &vp) {
        float marginWidth = width()/2.f;
        float marginHeight = height()/2.f;
        glColor4f(color.red(),color.green(),color.blue(),color.alpha());
        /* Draw a quad */
        glBegin(GL_QUADS);
            glVertex2i(x()-marginWidth, y()-marginHeight);
            glVertex2i(x()-marginWidth, y()+marginHeight);
            glVertex2i(x()+marginWidth, y()+marginHeight);
            glVertex2i(x()+marginWidth, y()-marginHeight);
        glEnd();
    }
};

#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480

int main(int argc, char **argv) {
    srand (time(NULL));

    Window window(640, 480, "Flappy", false, RangeRGBA(0,0,0,0));

    Force<2> gravity = Force2D::down(0.25f);

    Entity2D flappy;
    flappy.resize(10,10);
    flappy.x(100);
    flappy.y(50);
    flappy.color = RangeRGBA(0.9f,0.9f,0.9f,1.f);

    std::list<Entity2D> walls;
    
    size_t points = 0;
    bool dead = false;

    int Count = 10;
    auto renderer = [&](Viewport &vp) {
        flappy.render(vp);

        for (auto &wall : walls) wall.render(vp);

        if (dead) return;
        flappy.move();
        for (auto it = walls.begin(), e = walls.end(); it!=e; ) {
            auto last = it;
            it++;
            (*last).move();

            dead = dead || flappy.collision(*last);

            if ( (*last).x() + (*last).width() < 0) {
                walls.erase(last);
                points++;
                printf("Points: %ld\n", points);
            }
        }
        if (dead) {
            flappy.color = RangeRGBA(1.f,0.2f,0.2f,1.f);
        }

        if (flappy.y() < flappy.height()/2.f) {
            flappy.acceleration().y(0);
        }
        if (flappy.y() > vp.height()-flappy.height()/2.f) {
            flappy.acceleration().y(0);
        }

        flappy.apply(gravity);

        flappy.boundInside(vp);

        Count--;
        if (!Count) {
            float wallHeight = rand()%420;
            Entity2D wall;
            wall.resize(wallHeight,25);
            wall.x(vp.width());
            if (rand()%2)
                wall.y(wallHeight/2);
            else wall.y(vp.height() - wallHeight/2);
            wall.apply(Force2D::left(2.5f));
            wall.color = RangeRGBA(0.8f,0.5f,0.5f,1.f);
            walls.push_back(wall);

            Count = 100;
        }
    };

    window.keyEventHandler = [&](Window &window, int key, int scancode, int action, int mode) -> void {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) window.close();

        switch(key) {
        case GLFW_KEY_RIGHT:
            break;
        case GLFW_KEY_LEFT:
            break;
        case GLFW_KEY_SPACE:
            if (action == GLFW_PRESS) {
                if ( std::abs(flappy.acceleration().y()) < 15.f )
                    flappy.apply(Force2D::up(5));
            }
            break;
        case GLFW_KEY_ENTER:
            if (action == GLFW_PRESS && dead) {
                flappy.x(100);
                flappy.y(50);
                flappy.color = RangeRGBA(0.9f,0.9f,0.9f,1.f);
                flappy.acceleration().y(0);
                walls.clear();
                dead = false;
                points = 0;
            }
            break;
        }
    };
    window.runUntilClosed(renderer);

    window.release();
}
