#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "Constants.h"
#include "Advanced.h"

void Noise(int percentage, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    srand (time(NULL));
    int randomX;
    int randomY;
    int pixelsToChange = ((double)percentage)/(100.0) * ( WIDTH * HEIGHT);


    int i;
    for(i = 0; i < pixelsToChange ; i++){
        randomX = rand() % WIDTH;
        randomY = rand() % HEIGHT;
        R[randomX][randomY] = 255;
        G[randomX][randomY] = 255;
        B[randomX][randomY] = 255;
    }
}

/* sharpen the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    int             x, y, m, n, a, b;
    unsigned char   tmpR[WIDTH][HEIGHT];
    unsigned char   tmpG[WIDTH][HEIGHT];
    unsigned char   tmpB[WIDTH][HEIGHT];
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++) {
            tmpR[x][y] = R[x][y];
            tmpG[x][y] = G[x][y];
            tmpB[x][y] = B[x][y];
        }
    }
    int sumR = 0;   /* sum of the intensity differences with neighbors */
    int sumG = 0;
    int sumB = 0;
    for (y = 1; y < HEIGHT - 1; y++){
        for (x = 1; x < WIDTH - 1; x++){
            for (n = -1; n <= 1; n++){
                for (m = -1; m <= 1; m++) {
                    a = (x + m >= WIDTH) ? WIDTH - 1 : (x + m < 0) ? 0 : x + m;
                    b = (y + n >= HEIGHT) ? HEIGHT - 1 : (y + n < 0) ? 0 : y + n;
                    sumR += (tmpR[x][y] - tmpR[a][b]);
                    sumG += (tmpG[x][y] - tmpG[a][b]);
                    sumB += (tmpB[x][y] - tmpB[a][b]);
                }
            }
            R[x][y] = (sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < 0) ? 0: sumR;
            G[x][y] = (sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < 0) ? 0: sumG;
            B[x][y] = (sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < 0) ? 0: sumB;
            sumR = sumG = sumB = 0;
        }
    }
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++) {
            R[x][y] = (tmpR[x][y] + R[x][y]  > MAX_PIXEL) ? MAX_PIXEL: tmpR[x][y] + R[x][y];
            G[x][y] = (tmpG[x][y] + G[x][y]  > MAX_PIXEL) ? MAX_PIXEL: tmpG[x][y] + G[x][y];
            B[x][y] = (tmpB[x][y] + B[x][y]  > MAX_PIXEL) ? MAX_PIXEL: tmpB[x][y] + B[x][y];
        }
    }

}

/* posterize the image */
void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits){
    int y;
    int x;
    int temp;
    int rOperator = 1;
    int gOperator = 1;
    int bOperator = 1;
    for(y = 0; y < rbits -1; y++){
        rOperator*=2;
    }
    for(y = 0; y < gbits  -1; y++){
        gOperator*=2;
    }
    for(y = 0; y < bbits  -1; y++){
        bOperator*=2;
    }
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++) {
            R[x][y] = R[x][y] & (255-rOperator) | (rOperator - 1);
            G[x][y] = G[x][y] & (255-gOperator) | (gOperator - 1);
            B[x][y] = B[x][y] & (255-bOperator) | (bOperator - 1);
        }
    }


}

/* Test all functions */


/* motion blur */
void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
int y;
int x;
int b;
int blurR;
int blurG;
int blurB;
for (y = 0; y < HEIGHT; y++){
    for (x = 0; x < WIDTH; x++) {
        for(b = 1; b < BlurAmount && b + x < WIDTH; b++){
            blurR += R[x+b][y];
            blurG += G[x+b][y];
            blurB += B[x+b][y];
        }
        blurR = blurR/(b>0?b:1);
        blurG = blurG/(b>0?b:1);
        blurB = blurB/(b>0?b:1);

        R[x][y] = R[x][y]/2 + blurR/2;
        G[x][y] = G[x][y]/2 + blurG/2;
        B[x][y] = B[x][y]/2 + blurB/2;
    }
}
}
