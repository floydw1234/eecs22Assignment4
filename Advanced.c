#include "Advanced.h"
#include "Image.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>


/* Add noise to an image */
IMAGE *AddNoise(IMAGE *image, int n)
{
	int x, y, i;
	int num; /* number of noise added */
	num = ( n*ImageHeight(image)*ImageWidth(image) )/100;
	srand(time(NULL));

	for ( i = 0; i < num; i++ ) {
		x = ( (double)rand()/RAND_MAX )*(ImageWidth(image)-1);
		y = ( (double)rand()/RAND_MAX )*(ImageHeight(image)-1);
		SetPixelR(image, x,y,MAX_PIXEL);
		SetPixelG(image, x,y,MAX_PIXEL);
		SetPixelB(image, x,y,MAX_PIXEL);
	}
	return image;
}


/* sharpen the image */
IMAGE *Sharpen(IMAGE *image)
{
	int		x, y, m, n, a, b;
	int		tmpR = 0;
	int		tmpG = 0;
	int		tmpB = 0;

	IMAGE *tempImage = CreateImage(ImageWidth(image), ImageHeight(image));

	for (y = 0; y < ImageHeight(image); y++){
		for (x = 0; x < ImageWidth(image); x++) {
			SetPixelR(tempImage,x,y, GetPixelR(image,x,y));
			SetPixelG(tempImage,x,y, GetPixelG(image,x,y));
			SetPixelB(tempImage,x,y, GetPixelB(image,x,y));
		}
	}

	for (y = 0; y < ImageHeight(image); y++){
		for (x = 0; x < ImageWidth(image); x++){
			for (n = -1; n <= 1; n++){
				for (m = -1; m <= 1; m++) {
					a = x + m;
					b = y + n;
					if (a > ImageWidth(image) - 1)
						a = ImageWidth(image) - 1;
					if (a < 0)
						a = 0;
					if (b > ImageHeight(image) - 1)
						b = ImageHeight(image) - 1;
					if (b < 0)
						b = 0;

					if ((n==0)&&(m==0))
					{
						tmpR += 9*GetPixelR(tempImage,a,b);
						tmpG += 9*GetPixelG(tempImage,a,b) ;
						tmpB += 9*GetPixelB(tempImage,a,b) ;
					}
					else
					{
						tmpR -= GetPixelR(tempImage,a,b) ;
						tmpG -= GetPixelG(tempImage,a,b) ;
						tmpB -= GetPixelB(tempImage,a,b) ;
					}
				}
			}
			SetPixelR(image,x,y,(tmpR>255)? 255: (tmpR<0)? 0: tmpR );
			SetPixelG(image,x,y,(tmpG>255)? 255: (tmpG<0)? 0: tmpG );
			SetPixelB(image,x,y,(tmpB>255)? 255: (tmpB<0)? 0: tmpB );
		  	tmpR = tmpG = tmpB = 0;
		}
	}
  DeleteImage(tempImage);
	return image;
}

/* make the image posterized */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits)
{
	int x, y;
	for(x=0; x<ImageWidth(image); x++) {
		for(y=0; y<ImageHeight(image); y++) {
			unsigned char one = 1;
			int i;
			for(i=0; i<rbits-1; i++) {
				SetPixelR(image,x,y,GetPixelR(image,x,y)| one);
				one <<= 1;
			}
			one = ~one;
			SetPixelR(image,x,y,GetPixelR(image,x,y) & one);

			one = 1;
			for(i=0; i<gbits-1; i++) {
				SetPixelG(image,x,y,GetPixelG(image,x,y)| one);
				one <<= 1;
			}
			one = ~one;
			SetPixelG(image,x,y,GetPixelG(image,x,y) & one);

			one = 1;
			for(i=0; i<bbits-1; i++) {
				SetPixelB(image,x,y,GetPixelB(image,x,y)| one);
				one <<= 1;
			}
			one = ~one;
			SetPixelB(image,x,y,GetPixelB(image,x,y) & one);
		}
	}
	return image;
}

/* add motion blur to the image */
IMAGE *MotionBlur(IMAGE *image, unsigned char BlurAmount)
{
	int x,y,m;
	unsigned int temp_r , temp_g , temp_b;

	for (x = 0; x < ImageWidth(image); x++)
        	for (y = 0; y < ImageHeight(image) ; y++)
		{
			temp_r = GetPixelR(image,x,y)/2;
			temp_b = GetPixelB(image,x,y)/2;
			temp_g = GetPixelG(image,x,y)/2;

			for (m = 1; m<=BlurAmount ; m++)
			{
				if ((x+m) < ImageWidth(image))
				{
					temp_r = temp_r + GetPixelR(image,x+m,y) * 0.5/BlurAmount;
					temp_b = temp_b + GetPixelB(image,x+m,y) * 0.5/BlurAmount;
					temp_g = temp_g + GetPixelG(image,x+m,y) * 0.5/BlurAmount;
				}
			}

			SetPixelR(image,x,y, temp_r);
			SetPixelB(image,x,y, temp_b);
			SetPixelG(image,x,y, temp_g);
		}
	return image;
}

IMAGE *Crop(IMAGE *image, int x, int y, int W, int H){
	return image;

}
IMAGE *Resize(IMAGE *image, int percentage){
	return image;
}
IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast){
	return image;

}
IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image){
	return image;

}


/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
