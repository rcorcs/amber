#pragma once

#include <GL/glew.h>

#include "Image.h"

class Texture : public Dimentional<size_t, 3> {
  using Dim = Dimentional<size_t, 3>;
  GLuint id;

  using Dim::resize;
  using Dim::size;
  using Dim::volume;

public:
    Texture(Image image) : Dim(image.width(),image.height(),image.depth()) {
        int pixelFormat = (image.depth()==4)?GL_RGBA:GL_RGB;

        /* OpenGL texture binding of the image */
        glGenTextures( 1, &id ); /* Texture name generation */
        glBindTexture( GL_TEXTURE_2D, id ); /* Binding of texture name */
        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
        //We will use linear interpolation for magnification filter
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexImage2D( GL_TEXTURE_2D, 0, pixelFormat, image.width(), image.height(), 0, pixelFormat, GL_UNSIGNED_BYTE, (GLvoid *) image.begin() );
    }

    GLuint glId() { return id; }

    void release() {
      /* Delete used resources and quit */
      glDeleteTextures(1, &id);
    }
};

class TextureIO {
public:
    static Texture loadFromFile(const char *filepath) {
        Image image = ImageIO::loadFromFile(filepath);
        Texture texture(image);
        image.release();
        return texture;
    }
};