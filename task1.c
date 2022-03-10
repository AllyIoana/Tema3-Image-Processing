#include "utils.h"

Image Edit(char *path) {
    int i = 0, j = 0, padding = 0;
    char *p = (char *)malloc(task_len * sizeof(char));
    strncpy(p, path, strlen(path) - 1);
    Image image;
    FILE *in = NULL;
    in = fopen(path, "rb");

    // citim fileheader

    fread(&image.fileheader.fileMarker1, 1, 1, in);
    fread(&image.fileheader.fileMarker2, 1, 1, in);
    fread(&image.fileheader.bfSize, 4, 1, in);
    fread(&image.fileheader.unused1, 2, 1, in);
    fread(&image.fileheader.unused2, 2, 1, in);
    fread(&image.fileheader.imageDataOffset, 4, 1, in);

    // citim infoheader

    fread(&image.infoheader.biSize, 4, 1, in);
    fread(&image.infoheader.width, 4, 1, in);
    fread(&image.infoheader.height, 4, 1, in);
    fread(&image.infoheader.planes, 2, 1, in);
    fread(&image.infoheader.bitPix, 2, 1, in);
    fread(&image.infoheader.biCompression, 4, 1, in);
    fread(&image.infoheader.biSizeImage, 4, 1, in);
    fread(&image.infoheader.biXPelsPerMeter, 4, 1, in);
    fread(&image.infoheader.biYPelsPerMeter, 4, 1, in);
    fread(&image.infoheader.biClrUsed, 4, 1, in);
    fread(&image.infoheader.biClrImportant, 4, 1, in);

    // alocam memorie si citim matricea de pixeli
    image.mat = malloc(no_pixels * sizeof(colors *));
    for (i = 0; i < no_pixels; i++)
        image.mat[i] = calloc(no_pixels, sizeof(colors));

    padding = 3 * image.infoheader.width;
    padding = padding % 4;
    padding = (4 - padding) % 4;

    for (i = image.infoheader.height - 1; i >= 0; i--) {
        for (j = 0; j < image.infoheader.width; j++) {
            fread(&image.mat[i][j].blue, sizeof(char), 1, in);
            fread(&image.mat[i][j].green, sizeof(char), 1, in);
            fread(&image.mat[i][j].red, sizeof(char), 1, in);
        }
        fseek(in, padding, SEEK_CUR);
    }
    fclose(in);
    return image;
}

void Save(Image image, char *path) {
    int i = 0, j = 0, padding = 0;
    unsigned char zero = 0;
    FILE *out = NULL;
    out = fopen(path, "wb");

    // scriem fileheader

    fwrite(&image.fileheader.fileMarker1, 1, 1, out);
    fwrite(&image.fileheader.fileMarker2, 1, 1, out);
    fwrite(&image.fileheader.bfSize, 4, 1, out);
    fwrite(&image.fileheader.unused1, 2, 1, out);
    fwrite(&image.fileheader.unused2, 2, 1, out);
    fwrite(&image.fileheader.imageDataOffset, 4, 1, out);

    // scriem infoheader

    fwrite(&image.infoheader.biSize, 4, 1, out);
    fwrite(&image.infoheader.width, 4, 1, out);
    fwrite(&image.infoheader.height, 4, 1, out);
    fwrite(&image.infoheader.planes, 2, 1, out);
    fwrite(&image.infoheader.bitPix, 2, 1, out);
    fwrite(&image.infoheader.biCompression, 4, 1, out);
    fwrite(&image.infoheader.biSizeImage, 4, 1, out);
    fwrite(&image.infoheader.biXPelsPerMeter, 4, 1, out);
    fwrite(&image.infoheader.biYPelsPerMeter, 4, 1, out);
    fwrite(&image.infoheader.biClrUsed, 4, 1, out);
    fwrite(&image.infoheader.biClrImportant, 4, 1, out);

    // scriem matricea de pixeli; bitii de padding sunt 0

    padding = 3 * image.infoheader.width;
    padding = padding % 4;
    padding = (4 - padding) % 4;
    for (i = image.infoheader.height - 1; i >= 0; i--) {
        for (j = 0; j < image.infoheader.width; j++) {
            fwrite(&image.mat[i][j].blue, sizeof(char), 1, out);
            fwrite(&image.mat[i][j].green, sizeof(char), 1, out);
            fwrite(&image.mat[i][j].red, sizeof(char), 1, out);
        }
        for (j = 0; j < padding; j++)
            fwrite(&zero, sizeof(unsigned char), 1, out);
    }
    fclose(out);
}
