#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
    char name[244];
    int breadth, height, channels;
//taking input image
    printf("Enter image filename: ");
    scanf("%s", name);

//assigning the pointer to store the memory address for the intensity matrix of input image
    unsigned char *imgptr = stbi_load(name, &breadth, &height, &channels, 0);
    if (imgptr == NULL) {
        printf("Error:Could not load image %s\n", name);
        return 1;
    }
//printing the above matrix in the file named intensitymatrix.txt
    FILE *outptr = fopen("intensitymatrix.txt", "w");
    if (outptr == NULL) {
        printf("Error:Could not create matrix.txt\n");
        stbi_image_free(imgptr);
        return 1;
    }
//on the  first line,to print number of rows and coloumns which were used in the next code
    fprintf(outptr, "%d %d\n", breadth, height);
//
   int i=0;// to change the matrix into greyscale intensity matrix 
    while (i < height) {
        for (int j = 0; j < breadth; j++) {
            int ind = (i * breadth + j) * channels;
             unsigned char red;
              unsigned char green;
               unsigned char blue;
             red = imgptr[ind];
            if(channels > 1){
             green = imgptr[ind + 1] ;
            }
            else{
            green = red;
            }
           if(channels > 2){
             blue = imgptr[ind + 2] ;
            }
            else{
            blue = red;
            }
            int grey = (0.299 * red + 0.587 * green + 0.114 * blue);

            fprintf(outptr, "%3d ", grey);
        }
        fprintf(outptr, "\n");
        i++;
    }

//to free the pointer space
    stbi_image_free(imgptr);

    printf("Intensity matrix saved to intensitymatrix.txt\n");
    return 0;
}


