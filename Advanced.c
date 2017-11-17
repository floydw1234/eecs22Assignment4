#include "Advanced.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>


/* Add noise to an image */
IMAGE *Noise(IMAGE *image, int n)
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
			SetPixelR(tempImage,x,y, GetPixelR(image,x,y);
			SetPixelG(tempImage,x,y, GetPixelG(image,x,y);
			SetPixelB(tempImage,x,y, GetPixelB(image,x,y);
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
						tmpR += 9*R_tmp[a][b] ;
						tmpG += 9*G_tmp[a][b] ;
						tmpB += 9*B_tmp[a][b] ;
					}
					else
					{
						tmpR -= R_tmp[a][b] ;
						tmpG -= G_tmp[a][b] ;
						tmpB -= B_tmp[a][b] ;
					}
				}
			}
			R[x][y] = (tmpR>255)? 255: (tmpR<0)? 0: tmpR ;
			G[x][y] = (tmpG>255)? 255: (tmpG<0)? 0: tmpG ;
			B[x][y] = (tmpB>255)? 255: (tmpB<0)? 0: tmpB ;
		  	tmpR = tmpG = tmpB = 0;
		}
	}
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
				R[x][y] |= one;
				one <<= 1;
			}
			one = ~one;
			R[x][y] &= one;

			one = 1;
			for(i=0; i<gbits-1; i++) {
				G[x][y] |= one;
				one <<= 1;
			}
			one = ~one;
			G[x][y] &= one;

			one = 1;
			for(i=0; i<bbits-1; i++) {
				B[x][y] |= one;
				one <<= 1;
			}
			one = ~one;
			B[x][y] &= one;
		}
	}
}

/* add motion blur to the image */
IMAGE *MotionBlur(IMAGE *image, unsigned char BlurAmount)
{
	int x,y,m;
	unsigned int temp_r , temp_g , temp_b;

	for (x = 0; x < ImageWidth(image); x++)
        	for (y = 0; y < ImageHeight(image) ; y++)
		{
			temp_r = R[x][y]/2;
			temp_b = B[x][y]/2;
			temp_g = G[x][y]/2;

			for (m = 1; m<=BlurAmount ; m++)
			{
				if ((x+m) < ImageWidth(image))
				{
					temp_r = temp_r + R[x+m][y] * 0.5/BlurAmount;
					temp_b = temp_b + B[x+m][y] * 0.5/BlurAmount;
					temp_g = temp_g + G[x+m][y] * 0.5/BlurAmount;
				}
			}

			R[x][y]= temp_r;
			B[x][y]= temp_b;
			G[x][y]= temp_g;
		}
}

IMAGE *Crop(IMAGE *image, int x, int y, int W, int H){

}
IMAGE *Resize(IMAGE *image, int percentage){

}
IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast){

}
IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image){

}


/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
