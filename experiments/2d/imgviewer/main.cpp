
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Image.h"

#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 480

int width  = DEFAULT_WIDTH;
int height = DEFAULT_HEIGHT;

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
  // Clear color and depth buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  glMatrixMode(GL_MODELVIEW);     // Operate on model-view matrix

  /* Draw a quad */
  glBegin(GL_QUADS);
      glTexCoord2i(0, 0); glVertex2i(0,   0);
      glTexCoord2i(0, 1); glVertex2i(0,   height);
      glTexCoord2i(1, 1); glVertex2i(width, height);
      glTexCoord2i(1, 0); glVertex2i(width, 0);
  glEnd();
/*
  glColor3f(1.0f, 0.3f, 0.3f); //You can set RGB color for you vertex
  glBegin(GL_TRIANGLES);
  glVertex2f(-0.5, 0.5);
  glVertex2f(-0.5, -0.5);
  glVertex2f(0.5, 0.5);
  glVertex2f(0.5, 0.5);
  glVertex2f(-0.5, -0.5);
  glVertex2f(0.5, -0.5);
  glEnd();
*/
} 

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLFWwindow *window, int newwidth, int newheight) { 
    // Set the viewport to cover the new window
    glViewport(0, 0, width=newwidth, height=newheight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, 0.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    //display();
}
 
/* Initialize OpenGL Graphics */
void initGL(int w, int h) {
  glViewport(0, 0, w, h); // use a screen size of WIDTH x HEIGHT
  glEnable(GL_TEXTURE_2D);     // Enable 2D texturing
 
  glMatrixMode(GL_PROJECTION);     // Make a simple 2D projection on the entire window
  glLoadIdentity();
  glOrtho(0.0, w, h, 0.0, 0.0, 100.0);

  glMatrixMode(GL_MODELVIEW);    // Set the matrix mode to object modeling

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
  glClearDepth(0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window
}


int main(int argc, char **argv) {
    if ( argc < 1) {
        /* no image file to  display */
        return -1;
    }

    // start GL context and O/S window using the GLFW helper library
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Image Viewer", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, reshape);

    /* OpenGL 2D generic init */
    initGL(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    Image Img = ImageIO::loadFromFile(argv[1]);
    if ( Img.begin()==nullptr ) {
        printf("Can't load picture file %s\n", argv[1]);
        return -1;
    }

    GLuint texid;
    int pixelFormat = (Img.channels()==4)?GL_RGBA:GL_RGB;

    /* OpenGL texture binding of the image */
    glGenTextures( 1, &texid ); /* Texture name generation */
    glBindTexture( GL_TEXTURE_2D, texid ); /* Binding of texture name */
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    //We will use linear interpolation for magnification filter
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Img.width(), Img.height(), 0,
        pixelFormat, GL_UNSIGNED_BYTE, (GLvoid *) Img.begin() );
   

    while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    display();
    glfwSwapBuffers(window);
    }

    /* Delete used resources and quit */
    glDeleteTextures(1, &texid);
    Img.release();

    glfwTerminate();
    
    return 0;
} 
