#include "utils.h"

signed int max(signed int a, signed int b) {
    if (a > b)
        return a;
    return b;
}

signed int min(signed int a, signed int b) {
    if (a < b)
        return a;
    return b;
}

int maxim(int a, int b) {
    return a > b ? a : b;
}

int minim(int a, int b) {
    return a < b ? a : b;
}

void Insert(Image back, Image front, unsigned int line, unsigned int col) {
    signed int lb = back.infoheader.height,
        cb = back.infoheader.width,
        lf = front.infoheader.height,
        cf = front.infoheader.width;
    int i = 0, j = 0;
    line = lb - line;
    for (i = (int)line - 1; i >= maxim(0, (int)line-lf); i--)
        for (j = (int)col; j <= minim(cb, cf + (int)col) - 1; j++)
            back.mat[i][j] = front.mat[lf - line + i][j - col];
}
