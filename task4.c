#include "utils.h"
#define N 2000

int color_check(colors a, colors b) {
    if (a.blue == b.blue)
        if (a.green == b.green)
            if (a.red == b.red)
                return 1;
    return 0;
}

void Fill(Image image, colors color, int x, int y) {
    colors bgColor;
    int *posx = malloc(N * sizeof(int));
    int *posy = malloc(N * sizeof(int));
    int first = 0, last = 1, xNow = 0, yNow = 0;
    posx[0] = x;
    posy[0] = y;
    bgColor = image.mat[x][y];
    while (first != last) {
        xNow = posx[first];
        yNow = posy[first];
        first++;
        if (first == N)
            first = 0;
        if ((xNow - 1) >= 0) {
            if (color_check(image.mat[xNow - 1][yNow], bgColor) == 1) {
                image.mat[xNow - 1][yNow] = color;
                posx[last] = xNow - 1;
                posy[last] = yNow;
                last++;
                if (last == N)
                    last = 0;
            }
        }
        if ((xNow + 1) < image.infoheader.height) {
            if (color_check(image.mat[xNow + 1][yNow], bgColor) == 1) {
                image.mat[xNow + 1][yNow] = color;
                posx[last] = xNow + 1;
                posy[last] = yNow;
                last++;
                if (last == N)
                    last = 0;
            }
        }
        if ((yNow + 1) < image.infoheader.width) {
            if (color_check(image.mat[xNow][yNow + 1], bgColor) == 1) {
                image.mat[xNow][yNow + 1] = color;
                posx[last] = xNow;
                posy[last] = yNow + 1;
                last++;
                if (last == N)
                    last = 0;
            }
        }
        if ((yNow - 1) >= 0) {
            if (color_check(image.mat[xNow][yNow - 1], bgColor) == 1) {
                image.mat[xNow][yNow - 1] = color;
                posx[last] = xNow;
                posy[last] = yNow - 1;
                last++;
                if (last == N)
                    last = 0;
            }
        }
    }
}
