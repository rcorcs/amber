
#include "Graphics/Image.h"

#include <setjmp.h>
#include <png.h>

#include <jpeglib.h>    
#include <jerror.h>

#include <cstdlib>
#include <string>

/*
Image::Image(size_t width, size_t height, size_t numChannels) {
  create(width,height,numChannels);
}

bool Image::create(size_t w, size_t h, size_t d) {
  if (data!=nullptr) return false;
  data = new PixelRef::value_type[w*h*d];
  width = w;
  height = h;
  numChannels = d;
  return data!=nullptr;
}

void Image::releaseMemory() {
  delete []data;
  data = nullptr;
}
*/

Image ImageIO::loadFromFile(const char *filepath, Image::FileFormat fmt) {
  FILE* file = fopen(filepath, "r");
  if(!file) {
     return Image();
  }

  Image img;
  switch(fmt) {
  case Image::FileFormat::PNG:
    readPNG(file, img);
    break;
  case Image::FileFormat::JPEG:
    readJPEG(file, img);
    break;
  }

  fclose(file);
  return img;
}

Image ImageIO::loadFromFile(const char *filepath) {
  FILE* file = fopen(filepath, "rb");
  if(!file) {
     return Image();
  }

  Image img;
  if (isPNG(file)) readPNG(file, img);
  if (isJPEG(file)) readJPEG(file, img);

  fclose(file);
  return img;
}

bool ImageIO::isPNG(FILE *file) {
  png_byte header[8];
  fread( header, 1, 8, file );
  rewind(file);
  return !png_sig_cmp( header, 0, 8 );;
}

bool ImageIO::readPNG(FILE *file, Image &img) {
    int is_png, bit_depth, color_type, row_bytes, i;
    png_infop info_ptr, end_info;
    png_uint_32 t_width, t_height;
    png_byte header[8];
    png_bytepp row_pointers;
    png_structp png_ptr;

    fread( header, 1, 8, file );
    is_png = !png_sig_cmp( header, 0, 8 );
    if ( !is_png ) return false;

    png_ptr = png_create_read_struct( PNG_LIBPNG_VER_STRING, NULL,
        NULL, NULL );
    if ( !png_ptr ) return false;
    
    info_ptr = png_create_info_struct( png_ptr );
    if ( !info_ptr ) {
        png_destroy_read_struct( &png_ptr, (png_infopp) NULL, 
            (png_infopp) NULL );
        return false;
    }
    end_info = png_create_info_struct( png_ptr );
    if ( !end_info ) {
        png_destroy_read_struct( &png_ptr, (png_infopp) NULL,
            (png_infopp) NULL );
        return false;
    }
    if ( setjmp( png_jmpbuf( png_ptr ) ) ) {
        png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
        return false;
    }
    png_init_io( png_ptr, file );
    png_set_sig_bytes( png_ptr, 8 );
    png_read_info( png_ptr, info_ptr );
    png_get_IHDR( png_ptr, info_ptr, &t_width, &t_height, &bit_depth, 
        &color_type, NULL, NULL, NULL );

    png_read_update_info( png_ptr, info_ptr );
    row_bytes = png_get_rowbytes( png_ptr, info_ptr );

    const png_uint_32 t_channels = row_bytes/(t_width*sizeof(png_byte));
    if ( !img.allocate(t_height, t_width, t_channels) ) {
        png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
        return false;
    }
    row_pointers = (png_bytepp) malloc( t_height * sizeof(png_bytep) );
    if ( !row_pointers ) {
        png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
        img.release();
        return false;
    }
    //map row_pointers to the appropriate pointer offset in Image::data
    for ( i = 0; i < t_height; ++i )
        row_pointers[i] = img.begin() + i * row_bytes;

    png_read_image( png_ptr, row_pointers );
    switch ( png_get_color_type( png_ptr, info_ptr ) ) {
        /*
        color_type     - describes which color/alpha channels
                         are present.
                     PNG_COLOR_TYPE_GRAY
                        (bit depths 1, 2, 4, 8, 16)
                     PNG_COLOR_TYPE_GRAY_ALPHA
                        (bit depths 8, 16)
                     PNG_COLOR_TYPE_PALETTE
                        (bit depths 1, 2, 4, 8)
                     PNG_COLOR_TYPE_RGB
                        (bit_depths 8, 16)
                     PNG_COLOR_TYPE_RGB_ALPHA
                        (bit_depths 8, 16)
        */
        case PNG_COLOR_TYPE_RGBA:
        case PNG_COLOR_TYPE_RGB:
            break;
        default: // Color type %d not supported!
            png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
            img.release();
            return false;
    }

    png_destroy_read_struct( &png_ptr, &info_ptr, &end_info );
    free( row_pointers );

    return true;
}

bool ImageIO::isJPEG(FILE *file) {
  unsigned char header[2];
  fread(header, sizeof(unsigned char), 2, file);
  rewind(file);
  const bool hasJPEGMarker = header[0]==0xFF && header[1]==0xD8;
  return hasJPEGMarker;
}

bool ImageIO::readJPEG(FILE *file, Image &img) {
  struct jpeg_decompress_struct info; //for our jpeg info
  struct jpeg_error_mgr err;          //the error handler

  info.err = jpeg_std_error(& err);     
  jpeg_create_decompress(& info);   //fills info structure

  jpeg_stdio_src(&info, file);    
  jpeg_read_header(&info, true);   // read jpeg file header

  jpeg_start_decompress(&info);    // decompress the file

  //set width and height
  size_t width = info.output_width;
  size_t height = info.output_height;

  //ignore number of channels
  //info.num_components; // 3=RGB, 4=RGBA 

  img.allocate(height,width,3);
  
  
  while (info.output_scanline < info.output_height) {
    //point to the next row in Image::data
    const size_t rowSize = 3 * info.output_width * info.output_scanline;
    unsigned char * rowptr = img.begin() + rowSize;

    const int readNumRows = 1; //read a single row
    jpeg_read_scanlines(&info, &rowptr, readNumRows);
  }

  //clean up
  jpeg_finish_decompress(&info); 
  jpeg_destroy_decompress(&info);

  return true;
}





/*
 * Sample routine for JPEG compression.  We assume that the target file name
 * and a compression quality factor are passed in.
 */

void ImageIO::writeJPEG(Image &img, const char *filepath, int quality) {
  /* This struct contains the JPEG compression parameters and pointers to
   * working space (which is allocated as needed by the JPEG library).
   * It is possible to have several such structures, representing multiple
   * compression/decompression processes, in existence at once.  We refer
   * to any one struct (and its associated working data) as a "JPEG object".
   */
  struct jpeg_compress_struct cinfo;
  /* This struct represents a JPEG error handler.  It is declared separately
   * because applications often want to supply a specialized error handler
   * (see the second half of this file for an example).  But here we just
   * take the easy way out and use the standard error handler, which will
   * print a message on stderr and call exit() if compression fails.
   * Note that this struct must live as long as the main JPEG parameter
   * struct, to avoid dangling-pointer problems.
   */
  struct jpeg_error_mgr jerr;
  /* More stuff */
  FILE * outfile;		/* target file */
  JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
  int row_stride;		/* physical row width in image buffer */

  /* Step 1: allocate and initialize JPEG compression object */

  /* We have to set up the error handler first, in case the initialization
   * step fails.  (Unlikely, but it could happen if you are out of memory.)
   * This routine fills in the contents of struct jerr, and returns jerr's
   * address which we place into the link field in cinfo.
   */
  cinfo.err = jpeg_std_error(&jerr);
  /* Now we can initialize the JPEG compression object. */
  jpeg_create_compress(&cinfo);

  /* Step 2: specify data destination (eg, a file) */
  /* Note: steps 2 and 3 can be done in either order. */

  /* Here we use the library-supplied code to send compressed data to a
   * stdio stream.  You can also write your own code to do something else.
   * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
   * requires it in order to write binary files.
   */
  if ((outfile = fopen(filepath, "wb")) == NULL) {
    fprintf(stderr, "can't open %s\n", filepath);
    exit(1);
  }
  jpeg_stdio_dest(&cinfo, outfile);

  /* Step 3: set parameters for compression */

  /* First we supply a description of the input image.
   * Four fields of the cinfo struct must be filled in:
   */
  cinfo.image_width = img.width(); 	/* image width and height, in pixels */
  cinfo.image_height = img.height();
  cinfo.input_components = img.channels();		/* # of color components per pixel */
  switch(img.channels()) {
  case 4:
    cinfo.in_color_space = JCS_EXT_RGBA; 	/* colorspace of input image */
    break;
  default:
    cinfo.in_color_space = JCS_RGB; 	/* colorspace of input image */
    break;
  }

  /* Now use the library's routine to set default compression parameters.
   * (You must set at least cinfo.in_color_space before calling this,
   * since the defaults depend on the source color space.)
   */
  jpeg_set_defaults(&cinfo);
  /* Now you can set any non-default parameters you wish to.
   * Here we just illustrate the use of quality (quantization table) scaling:
   */
  jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

  /* Step 4: Start compressor */

  /* TRUE ensures that we will write a complete interchange-JPEG file.
   * Pass TRUE unless you are very sure of what you're doing.
   */
  jpeg_start_compress(&cinfo, TRUE);

  /* Step 5: while (scan lines remain to be written) */
  /*           jpeg_write_scanlines(...); */

  /* Here we use the library's state variable cinfo.next_scanline as the
   * loop counter, so that we don't have to keep track ourselves.
   * To keep things simple, we pass one scanline per call; you can pass
   * more if you wish, though.
   */
  row_stride = img.width() * img.channels();	/* JSAMPLEs per row in image_buffer */

  while (cinfo.next_scanline < cinfo.image_height) {
    /* jpeg_write_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could pass
     * more than one scanline at a time if that's more convenient.
     */
    row_pointer[0] = img.begin() + cinfo.next_scanline * row_stride;
    (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
  }

  /* Step 6: Finish compression */

  jpeg_finish_compress(&cinfo);
  /* After finish_compress, we can close the output file. */
  fclose(outfile);

  /* Step 7: release JPEG compression object */

  /* This is an important step since it will release a good deal of memory. */
  jpeg_destroy_compress(&cinfo);

  /* And we're done! */
}
