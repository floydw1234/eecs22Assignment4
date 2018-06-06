/*********************************************************************/
/* PhotoLab.c: assignment 2 for EECS 22 in Fall 2017                 */
/*                                                                   */
/* modifications: (Saeed Karimi Bidhendi)                            */
/* 09/27/17 RD	adjusted for lecture usage                           */
/*********************************************************************/

/*** header files ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <time.h>


/*** global definitions ***/

const int WIDTH  = 600;	/* image width */
const int HEIGHT = 400;	/* image height */
const int SLEN   =  80;	/* max. string length */

/*** function declarations ***/

void PrintMenu();

/* read image from a file */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

/* color filter */
void ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT], int target_r, int target_g,
                 int target_b, int threshold, int replace_r, int replace_g, int replace_b);

/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT]);


/* mirror image vertically */
void VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);

/* change color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT]);


/* sharpen the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);


/* add border */
void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT], char color[SLEN], int border_width);

/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
           unsigned char B[WIDTH][HEIGHT]);

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

/*** main program ***/

int main(void)
{
    unsigned char R[WIDTH][HEIGHT];
    unsigned char G[WIDTH][HEIGHT];
    unsigned char B[WIDTH][HEIGHT];
    int input;
    int target_r;
    int target_g;
    int target_b;
    int threshold;
    int replace_r;
    int replace_g;
    int replace_b;
    int width;
    char color[SLEN];

    while(input != 12){
        printf("--------------------------------\n1: Load a PPM image\n2: Save an image in PPM and JPEG format\n3: Change a color image to Black & White\n4: Make a negative of an image\n5: Color filter an image\n6: Sketch the edge of an image\n7: Shuffle an image\n8: Flip an image vertically\n9: Mirror an image vertically\n10: Add Border to an image\n11: Test all functions\n12: Exit\nplease make your choice: ");
        scanf("%d", &input);
        char Filename[20];
        switch(input){
            case 1:
                printf("Please input the file name to load: ");
                scanf("%s",Filename);
                if (LoadImage(Filename, R, G, B) != 0)
                    continue;
                printf("%s was loaded successfully!\n",Filename);
                break;
            case 2:
                printf("Please input the file name to save: ");
                scanf("%s",Filename);
                SaveImage(Filename,R,G,B);
                printf("%s.jpg was stored for viewing.\n", Filename);


                break;
            case 3:
                printf("Changing the Image to Black and White...\n");
                BlackNWhite(R,G,B);
                break;
            case 4:
                printf("Making the negative of the image...\n");
                Negative(R,G,B);
                break;
            case 5:
                printf("Enter Red component for the target color: ");
                scanf("%d", &target_r);
                printf("Enter Green component for the target color: ");
                scanf("%d", &target_g);
                printf("Enter Blue component for the target color: ");
                scanf("%d", &target_b);
                printf("Enter threshold for the color difference: ");
                scanf("%d", &threshold);

                printf("Enter value for Red component in the target color: ");
                scanf("%d", &replace_r);
                printf("Enter value for Green component in the target color: ");
                scanf("%d", &replace_g);
                printf("Enter value for Blue component in the target color: ");
                scanf("%d", &replace_b);
                printf("Color filtering the imag12e...\n");
                ColorFilter(R,G,B,target_r, target_g, target_b, threshold, replace_r, replace_g, replace_b);
                break;
            case 6:
                printf("Sketching the edge of the image...\n");
                Edge(R,G,B);
                break;
            case 7:
                printf("Shuffling the image...\n");
                Shuffle(R,G,B);
                break;
            case 8:
                printf("Flip the Image vertically...\n");
                VFlip(R,G,B);
                break;
            case 9:
                printf("Mirroring the Image vertically...\n");
                VMirror(R,G,B);
                break;
            case 10:
                printf("Please enter border width: ");
                scanf("%d", &width);
                printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
                printf("Select border color from the options: ");
                scanf("%s", color);
                printf("Adding a border to the image...\n");
                AddBorder(R,G,B,color,width);
                break;
            case 11:
                printf("Testing all of the functoins!\n");
                AutoTest(R,G,B);
                break;
            case 12:
                printf("\nBYE!\n\n");
                break;
            default:
                printf("Please put a int between 1-12");
               break;
        }
    }

    return 0;
} /* end of main */


/*** function definitions ***/

/* read a photo from the specified file into the specified */
/* RGB data structure; returns 0 for success, >0 for error */


int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        FILE           *File;
        char            Type[SLEN];
        int             Width, Height, MaxValue;
        int             x, y;
        char            ftype[] = ".ppm";
        char            fname_tmp[SLEN];
        strcpy(fname_tmp, fname);
        strcat(fname_tmp, ftype);

        File = fopen(fname_tmp, "r");
        if (!File) {
                printf("Cannot open file \"%s\" for reading!\n", fname);
                return 1;
                    }
        fscanf(File, "%79s", Type);
        if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
                printf("\nUnsupported file format!\n");
                return 2;
                                                                }
        fscanf(File, "%d", &Width);
        if (Width != WIDTH) {
                printf("\nUnsupported image width %d!\n", Width);
                return 3;
                             }
        fscanf(File, "%d", &Height);
        if (Height != HEIGHT) {
                 printf("\nUnsupported image height %d!\n", Height);
                 return 4;
                              }
        fscanf(File, "%d", &MaxValue);
        if (MaxValue != 255) {
                 printf("\nUnsupported image maximum value %d!\n", MaxValue);
                 return 5;
                            }
        if ('\n' != fgetc(File)) {
                 printf("\nCarriage return expected!\n");
                 return 6;
                                }
        for (y = 0; y < HEIGHT; y++)
             for (x = 0; x < WIDTH; x++) {
                         R[x][y] = fgetc(File);
                         G[x][y] = fgetc(File);
                         B[x][y] = fgetc(File);
                                         }
        if (ferror(File)) {
             printf("\nFile error while reading from file!\n");
             return 7;
                           }
        printf("%s was read.\n", fname_tmp);
        fclose(File);
        return 0;
}

int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        FILE    *File;
        int x, y;
        char    SysCmd[SLEN * 5];
        char    ftype[] = ".ppm";
        char    fname_tmp[SLEN];  /*avoid to modify on the original pointer, 11/10/10, X.Han*/
        char    fname_tmp2[SLEN];

        strcpy(fname_tmp, fname);
        strcpy(fname_tmp2, fname);
        strcat(fname_tmp2, ftype);

        File = fopen(fname_tmp2, "w");
        if (!File) {
                printf("Cannot open file \"%s\" for writing!\n", fname);
                return 1;
                   }
        fprintf(File, "P6\n");
        fprintf(File, "%d %d\n", WIDTH, HEIGHT);
        fprintf(File, "255\n");
        for (y = 0; y < HEIGHT; y++)
                 for (x = 0; x < WIDTH; x++) {
                               fputc(R[x][y], File);
                               fputc(G[x][y], File);
                               fputc(B[x][y], File);
                                              }
         if (ferror(File)) {
                  printf("\nFile error while writing to file!\n");
                  return 2;
                            }
         fclose(File);
         printf("%s was saved. \n", fname_tmp2);
   /*
     *      * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     *           * and make it world readable
                                   *                */
        sprintf(SysCmd, "/users/grad2/doemer/eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_tmp2);
        if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
                                  }
        printf("%s.jpg was stored.\n", fname_tmp);
        return 0;
}






/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]){
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            R[i][j] = 255 - R[i][j];
            G[i][j] = 255 - G[i][j];
            B[i][j] = 255 - B[i][j];
        }
    }
    printf("Negative of Image was created!\n");

}

/* color filter */
void ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT], int target_r, int target_g,
                 int target_b, int threshold, int replace_r, int replace_g, int replace_b){
    bool r;
    bool g;
    bool b;
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            r = R[i][j] <= target_r + threshold && R[i][j] >= target_r - threshold;
            g = G[i][j] <= target_g + threshold && G[i][j] >= target_g - threshold;
            b = B[i][j] <= target_b + threshold && B[i][j] >= target_b - threshold;
            if(r && g && b){
                R[i][j] = replace_r;
                G[i][j] = replace_g;
                B[i][j] = replace_b;
            }
        }
    }
    printf("Color was filtered!\n");
}

int findPosition(int i,int j){//to make sure that the surrounding 8 pixels are all in the array for Edge
    int output = 2;
    if(i - 1 < 0)
        output = 5;
    else if(i + 1 >= WIDTH)
        output = 6;
    if(j - 1 < 0)
        output = output*2;
    else if(j + 1 >= HEIGHT)
        output = output * 8;
    return output;

}

/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT]){
    int position;
    int v;
    unsigned char colors[3][WIDTH][HEIGHT];
    unsigned char edges[3][WIDTH][HEIGHT];
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            colors[0][i][j] = R[i][j];
            colors[1][i][j] = G[i][j];
            colors[2][i][j] = B[i][j];
            edges[0][i][j] = R[i][j];
            edges[1][i][j] = G[i][j];
            edges[2][i][j] = B[i][j];

        }
    }
    for(int k = 0; k < 3; k++){
        for(int i = 0; i < WIDTH; i++){
            for(int j = 0; j < HEIGHT; j++){

                position = findPosition(i,j);
                switch(position){
                    case 10: //upper left corner
                        v = 8*colors[k][i][j] - colors[k][i+1][j] - colors[k][i+1][j+1] - colors[k][i][j+1];
                        if (v<0)
                            v=0;
                        else if (v>255)
                            v=255;
                        edges[k][i][j] = v;
                        break;
                    case 4: //upper side
                        v = 8*colors[k][i][j] - colors[k][i+1][j] - colors[k][i+1][j+1] - colors[k][i][j+1] - colors[k][i-1][j+1] - colors[k][i-1][j];
                        if (v<0)
                            v=0;
                        else if (v>255)
                            v=255;
                        edges[k][i][j] = v;
                        break;
                    case 12: // upper right corner

                        v = 8*colors[k][i][j] - colors[k][i+1][j] - colors[k][i+1][j-1] - colors[k][i][j-1];
                        if (v<0)
                            v=0;
                        else if (v>255)
                            v=255;
                        edges[k][i][j] = v;
                        break;
                    case 5: // left side
                        v = 8*colors[k][i][j] - colors[k][i][j-1] - colors[k][i][j+1] - colors[k][i+1][j-1] - colors[k][i+1][j+1] - colors[k][i+1][j];
                        if (v<0)
                            v=0;
                        else if (v>255)
                            v=255;
                        edges[k][i][j] = v;
                        break;
                    case 2: // no problems

                        v = 8*colors[k][i][j] - colors[k][i][j-1] - colors[k][i][j+1] - colors[k][i+1][j-1] - colors[k][i+1][j+1] - colors[k][i+1][j] - colors[k][i-1][j-1] - colors[k][i-1][j+1] - colors[k][i-1][j];
                        if (v<0)
                            v=0;
                        else if (v>255)
                            v=255;
                        edges[k][i][j] = v;
                        break;
                    case 6: // right side
                        v = 8*colors[k][i][j] - colors[k][i][j-1] - colors[k][i][j+1] - colors[k][i-1][j-1] - colors[k][i-1][j+1] - colors[k][i-1][j];
                        if (v<0)
                            v=0;
                        else if (v>255)
                            v=255;
                        edges[k][i][j] = v;
                        break;
                    case 40: // left bottom corner
                        v = 8*colors[k][i][j] - colors[k][i][j-1] - colors[k][i+1][j-1] - colors[k][i+1][j];
                        if (v<0)
                            v=0;
                        else if (v>255)
                            v=255;
                        edges[k][i][j] = v;
                        break;
                    case 16: // bottom side
                        v = 8*colors[k][i][j] - colors[k][i][j-1] - colors[k][i+1][j-1] - colors[k][i+1][j] - colors[k][i-1][j-1] - colors[k][i-1][j];
                        if (v<0)
                            v=0;
                        else if (v>255)
                            v=255;
                        edges[k][i][j] = v;
                        break;
                    case 48: // bottom right corner
                        v = 8*colors[k][i][j] - colors[k][i][j-1] - colors[k][i-1][j-1] - colors[k][i-1][j];
                        if (v<0)
                            v=0;
                        else if (v>255)
                            v=255;
                        edges[k][i][j] = v;
                        break;
                    default:
                        printf("get fuked");
                }
            }

        }
    }
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            R[i][j] = edges[0][i][j];
            G[i][j] = edges[1][i][j];
            B[i][j] = edges[2][i][j];
        }
    }
    printf("edges detected");
}


/* mirror image vertically */
void VMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]){
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            if( j > 200){
                R[i][j] = R[i][HEIGHT - j];
                G[i][j] = G[i][HEIGHT - j];
                B[i][j] = B[i][HEIGHT - j];
            }
        }
    }
    printf("image was vertically mirrored\n");
}

/* change color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT]){
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            int avg = (R[i][j] + G[i][j] + B[i][j]) /3;
            R[i][j] = G[i][j] = B[i][j] = avg;
        }
    }
    printf("Image converted to black and white!\n");



}


/* sharpen the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]){
    unsigned char piecesR[16][150][100];
    unsigned char piecesG[16][150][100];
    unsigned char piecesB[16][150][100];
    for(int i = 0; i< 16 ; i++){
        for(int j = 0; j< 150; j++){
            for(int k = 0; k< 100; k++){
                int startingX = i / 4 * 150;
                int startingY = (i % 4 * 100);
                /*
                if(i == 15){
                    printf("starting x: %d\n",startingX);
                    printf("starting y: %d\n",startingY);
                    printf("x = %d; y = %d\n",j, k);
                }
                */

                piecesR[i][j][k] = R[j + startingX][k + startingY];

                piecesG[i][j][k] = G[j + startingX][k + startingY];

                piecesB[i][j][k] = B[j + startingX][k + startingY];


            }
        }
    }

    int usedNumbers[16] = {};
    for(int i= 0; i<16; i++){
        int startingX = i / 4 * 150;
        int startingY = (i % 4 * 100);
        srand((unsigned)time(NULL));
        int r = rand() % 16;

        while( usedNumbers[r] != 0){
            //srand((unsigned)time(NULL));
            r = rand() % 16;

        }
        usedNumbers[r] = 1;

        for(int j = 0; j< 150; j++){
            for(int k = 0; k< 100; k++){

                R[j + startingX][k + startingY] = piecesR[r][j][k];
                G[j + startingX][k + startingY] = piecesG[r][j][k];
                B[j + startingX][k + startingY] = piecesB[r][j][k];

            }
        }

    }




}


/* add border */
void AddBorder(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT], char color[SLEN], int border_width){
    int widthCutoff = border_width * 9 / 16;
    int heightCutoff = border_width;
    int bColor[3];
    if (strcmp(color, "black") == 0){
        bColor[0] = 0;
        bColor[1] = 0;
        bColor[2] = 0;
    }else if (strcmp(color, "white") == 0){

        bColor[0] = 255;
        bColor[1] = 255;
        bColor[2] = 255;
    }else if (strcmp(color, "red") == 0){

        bColor[0] = 255;
        bColor[1] = 0;
        bColor[2] = 0;
    }else if (strcmp(color, "green") == 0){

        bColor[0] = 0;
        bColor[1] = 255;
        bColor[2] = 0;
    }else if (strcmp(color, "blue") == 0){

        bColor[0] = 0;
        bColor[1] = 0;
        bColor[2] = 255;
    }else if (strcmp(color, "yellow") == 0){

        bColor[0] = 255;
        bColor[1] = 255;
        bColor[2] = 0;
    }else if (strcmp(color, "cyan") == 0){

        bColor[0] = 0;
        bColor[1] = 255;
        bColor[2] = 255;
    }else if (strcmp(color, "pink") == 0){

        bColor[0] = 255;
        bColor[1] = 0;
        bColor[2] = 255;
    }else if (strcmp(color, "orange") == 0){
        bColor[0] = 255;
        bColor[1] = 128;
        bColor[2] = 0;
    }else{
        bColor[0] = 0;
        bColor[1] = 0;
        bColor[2] = 0;
        printf("oops you mistyped the color. Now it is black");
    }


    for(int i = 0; i< WIDTH ; i++){
        for(int j = 0; j< HEIGHT; j++){
            if(i < widthCutoff || i > WIDTH - widthCutoff || j < heightCutoff || j > HEIGHT - heightCutoff ){
                R[i][j] = bColor[0];
                G[i][j] = bColor[1];
                B[i][j] = bColor[2];
            }
        }
    }
    printf("Border added");



}

/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
           unsigned char B[WIDTH][HEIGHT]){
    unsigned char temp;

    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT/2; j++){

            temp = R[i][j];
            R[i][j] = R[i][HEIGHT - 1 - j];
            R[i][HEIGHT - 1 - j] = temp;

            temp = G[i][j];
            G[i][j] = G[i][HEIGHT - 1 - j];
            G[i][HEIGHT - 1 - j] = temp;

            temp = B[i][j];
            B[i][j] = B[i][HEIGHT - 1 - j];
            B[i][HEIGHT - 1 - j] = temp;

        }
    }



    printf("Image Flipped!\n");
}

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]){
    LoadImage("HSSOE", R, G, B);
    BlackNWhite(R,G,B);
    SaveImage("bw",R,G,B);
    printf("Black and White tested!\n\n");

    LoadImage("HSSOE", R, G, B);
    Negative(R,G,B);
    SaveImage("negative",R,G,B);
    printf("Negative tested!\n\n");

    LoadImage("HSSOE", R, G, B);
    ColorFilter(R,G,B,130, 130, 250, 70, 255, 0, 0);
    SaveImage("colorfilter",R,G,B);
    printf("Color Filter tested!\n\n");

    LoadImage("HSSOE", R, G, B);
    Edge(R,G,B);
    SaveImage("edge",R,G,B);
    printf("Edge tested!\n\n");

    LoadImage("HSSOE", R, G, B);
    Shuffle(R,G,B);
    SaveImage("shuffle",R,G,B);
    printf("shuffle tested!\n\n");

    LoadImage("HSSOE", R, G, B);
    VFlip(R,G,B);
    SaveImage("vflip",R,G,B);
    printf("Virtical Flip tested!\n\n");

    LoadImage("HSSOE", R, G, B);
    VMirror(R,G,B);
    SaveImage("vmirror",R,G,B);
    printf("Virtical Mirror tested!\n\n");

    LoadImage("HSSOE", R, G, B);
    AddBorder(R,G,B,"yellow",64);
    SaveImage("border",R,G,B);
    printf("Border tested!\n\n");


}





/* EOF */
