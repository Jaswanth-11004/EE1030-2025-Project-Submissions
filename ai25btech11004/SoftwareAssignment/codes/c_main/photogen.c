#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main() {
    FILE *inptr;
    int breadth, height;
//to take data from 
    inptr = fopen("matrix.txt", "r");
    if (inptr == NULL) {
        printf("Error: Cannot open matrix.txt \n");
        return 1;
    }

    //taking number of rows and coloumns which were there in the first  line of matrix.txt
    if (fscanf(inptr, "%d %d", &breadth, &height) != 2) {
        printf("Error: Invalid matrix.txt format \n");
        fclose(inptr);
        return 1;
    }

    //allocate the memory for image pointer
    unsigned char *image = (unsigned char *)malloc(breadth * height);
    if (image == NULL) {
        printf("Error: Memory allocation failed \n ");
        fclose(inptr);
        return 1;
    }
     int i=0;
     while( i < height) {
    for (int j = 0; j < breadth; j++) {
        float grey;
        if (fscanf(inptr, "%f", &grey) != 1) {
            printf("Invalid matrix data \n");
            fclose(inptr);
            return 1;
        }//taking entries of input matrix from matrix.txt
        if (grey < 0) {//grey is nothing but pixels
        grey = 0;
        }
        if (grey > 255){
        grey = 255;
        }
        image[i * breadth + j] = (unsigned char)(grey+0.5f);
    }
    i++;
}

    fclose(inptr);//creating the image of pointer created above using the stb_image_write
    if (!stbi_write_png("output.png", breadth, height, 1, image, breadth)) {
        printf("Failed to write output.png \n");
        return 1;
    }

    printf("Image successfully created: output.png \n");
    return 0;
}

