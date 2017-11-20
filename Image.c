#include <stdlib.h>
#include "Image.h"

unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y){
    return *(image->R + x + y*ImageWidth(image));
}

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y){
    return *(image->B + x + y*ImageWidth(image));
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y){
    return *(image->G + x + y*ImageWidth(image));
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r){
    *(image->R + x + y*ImageWidth(image)) = r;
}

/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g){
    *(image->R + x + y*ImageWidth(image)) = g;
}

/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b){
    *(image->B + x + y*ImageWidth(image)) = b;
}

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height){
    IMAGE *image = malloc(sizeof(IMAGE));
    image->W = Width;
    image->H = Height;
    image->R =  malloc(Width * Height);
    image->G =  malloc(Width * Height);
    image->B =  malloc(Width * Height);
	return image;
}

/* Free the memory for the R/G/B values and IMAGE structure */
void DeleteImage(IMAGE *image){
    free(image->R);
    free(image->G);
    free(image->B);
    free(image);
}

/* Return the image's width in pixels */
unsigned int ImageWidth(const IMAGE *image){
    return image->W;
}

/* Return the image's height in pixels */
unsigned int ImageHeight(const IMAGE *image){
    return image->H;
}
