#include "utils.h"

void color_point(Image image, colors color, char width, int x, int y) {
    int i = 0, j = 0;
    for (i = x - width / 2; i <= x + width / 2; i++)
        for (j = y - width / 2; j <= y + width / 2; j++)
            if (i >= 0 && i < image.infoheader.height)
                if (j >= 0 && j < image.infoheader.width)
                    image.mat[i][j] = color;
}

void Line(Image image, colors color, char width,
    int ya, int xa, int yb, int xb) {

    /* ecuatia dreptei: (y-ya) / (yb-ya) = (x-xa) / (xb-xa)
    <=> y * (xb-xa) - x * (yb-ya) = -xa*yb + ya*xb */

    char var = 0;
    int i = 0, dify = maxim(ya, yb) - minim(ya, yb);
    int difx = maxim(xa, xb) - minim(xa, xb);
    if (maxim(dify, difx) == difx)
        var = 'x';
    else
        var = 'y';
    int rez = -xa * yb + ya * xb;
    if (var == 'y') {
        for (i = minim(ya, yb); i <= maxim(ya, yb); i++) {
            rez = -xa * yb + ya * xb;
            rez = i * (xb - xa) - rez;
            rez = rez / (yb - ya);
            color_point(image, color, width,
                image.infoheader.height - i - 1, rez);
        }
    }
    if (var == 'x') {
        for (i = minim(xa, xb); i <= maxim(xa, xb); i++) {
            rez = -xa * yb + ya * xb;
            rez = i * (yb - ya) + rez;
            rez = rez / (xb - xa);
            color_point(image, color, width,
                image.infoheader.height - rez - 1, i);
        }
    }
}

void Rectangle(Image image, colors color, char width,
    int y, int x, int w, int h) {

    Line(image, color, width, x, y, x, y + w);
    Line(image, color, width, x, y + w, x + h, y + w);
    Line(image, color, width, x + h, y + w, x + h, y);
    Line(image, color, width, x + h, y, x, y);
}

void Triangle(Image image, colors color, char width,
    int y1, int x1, int y2, int x2, int y3, int x3) {

    Line(image, color, width, x1, y1, x2, y2);
    Line(image, color, width, x2, y2, x3, y3);
    Line(image, color, width, x3, y3, x1, y1);
}
