#include "Advanced.h"
#include "Image.h"
 
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>


/* Add noise to an image */
IMAGE *AddNoise(IMAGE *image, int n)
{
	assert(image);
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
	assert(image);
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
	assert(image);
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
	assert(image);
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
  assert(image);
  W = W + x > ImageWidth(image) ? ImageWidth(image) - x : W;
  H = H + y  > ImageHeight(image) ? ImageHeight(image) - y : H;
  IMAGE *newImage = CreateImage(W,H);
  int i;
  int j;
  for (i = 0; i < ImageWidth(newImage); i++){
 	    for (j = 0; j < ImageHeight(newImage) ; j++){
          SetPixelR(newImage,i,j,GetPixelR(image,i+x,j+y));
          SetPixelG(newImage,i,j,GetPixelG(image,i+x,j+y));
          SetPixelB(newImage,i,j,GetPixelB(image,i+x,j+y));
      }
  }
  DeleteImage(image);
  return newImage;

}
IMAGE *Resize(IMAGE *image, int percentage){
	assert(image);
  int newWidth = ImageWidth(image)*(percentage/100.00);
  int newHeight = ImageHeight(image)*(percentage/100.00);
  IMAGE *newImage = CreateImage(newWidth, newHeight);
  int i,j,x1,y1,x2,y2;
  if(percentage >= 100){
	  for (i = 0; i < ImageWidth(newImage); i++){
			for (j = 0; j < ImageHeight(newImage) ; j++){
				SetPixelR(newImage,i,j,GetPixelR(image,i*(100.00/percentage),j * (100.00/percentage)));
				SetPixelG(newImage,i,j,GetPixelG(image,i*(100.00/percentage),j * (100.00/percentage)));
				SetPixelB(newImage,i,j,GetPixelB(image,i*(100.00/percentage),j * (100.00/percentage)));
				
			}
		}
  }else{
	  for (i = 0; i < ImageWidth(newImage); i++){
			for (j = 0; j < ImageHeight(newImage) ; j++){
				x1 = i / (percentage / 100.00);
				y1 = j / (percentage / 100.00);
				x2 = (i + 1) / (percentage / 100.00);
				y2 = (j + 1) / (percentage / 100.00);
				int k,l;
				int tempR = 0;
				int tempG = 0;
				int tempB = 0;
				for (k = x1; k < x2; k++){
					for (l = y1; l < y2 ; l++){
						tempR += GetPixelR(image,k,l);
						tempG += GetPixelG(image,k,l);
						tempB += GetPixelB(image,k,l);
						
					}
				}
				tempR /= (x2 - x1)*(y2-y1);
				tempG /= (x2 - x1)*(y2-y1);
				tempB /= (x2 - x1)*(y2-y1);
				SetPixelR(newImage,i,j,tempR);
				SetPixelG(newImage,i,j,tempG);
				SetPixelB(newImage,i,j,tempB);
			}
		}
  }
  
	DeleteImage(image);
	return newImage;
}
IMAGE *BrightnessAndContrast(IMAGE *image, int brightness, int contrast){
	assert(image);
	int i,j,tempR,tempG,tempB;
	double factor = (double)(259 * (contrast + 255)) / (double)(255 * (259 - contrast));
	for (i = 0; i < ImageWidth(image); i++){
		for (j = 0; j < ImageHeight(image) ; j++){
        		tempR = (int)(factor*(GetPixelR(image,i,j) - 128)) + 128 + brightness;
        		tempG = (int)(factor*(GetPixelG(image,i,j) - 128)) + 128 + brightness;
        		tempB = (int)(factor*(GetPixelB(image,i,j) - 128)) + 128 + brightness;
       	
       	 		tempR = tempR > 255 ? 255 : tempR < 0? 0 : tempR;
        		tempG = tempG > 255 ? 255 : tempG < 0? 0 : tempG;
        		tempB = tempB > 255 ? 255 : tempB < 0? 0 : tempB;
       	
			SetPixelR(image,i,j, tempR);
        		SetPixelG(image,i,j, tempG);
        		SetPixelB(image,i,j, tempB);
		}
	}
	return image;
}       
      
IMAGE *Watermark(IMAGE *image, const IMAGE *watermark_image){
	assert(image);
	int i,j,tempR,tempG,tempB;
	for (i = 0; i < ImageWidth(image); i++){
		for (j = 0; j < ImageHeight(image) ; j++){
			//printf("width: %d\n",ImageWidth(watermark_image));
			//printf("i value: %d\n",i);
			//printf("height: %d\n",ImageHeight(watermark_image));
			//printf("j value: %d\n",j);
			if(GetPixelR(watermark_image,i%ImageWidth(watermark_image),j%ImageHeight(watermark_image)) == 0 &&
			GetPixelG(watermark_image,i%ImageWidth(watermark_image),j%ImageHeight(watermark_image)) == 0 &&
			GetPixelB(watermark_image,i%ImageWidth(watermark_image),j%ImageHeight(watermark_image)) == 0){
				tempR = GetPixelR(image,i,j)*1.45;
				tempG = GetPixelG(image,i,j)*1.45;
				tempB = GetPixelB(image,i,j)*1.45;
				
				tempR = tempR > 255 ? 255 : tempR;
				tempG = tempG > 255 ? 255 : tempG;
				tempB = tempB > 255 ? 255 : tempB;
				
				SetPixelR(image,i,j,tempR);
				SetPixelG(image,i,j,tempG);
				SetPixelB(image,i,j,tempB);
				
			}
		}
	}
	return image;

}


/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
