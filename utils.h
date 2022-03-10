#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"
#define task_len 200
#define no_pixels 1000

Image Edit(char *path);
void Save(Image image, char *path);
void Insert(Image back, Image front, unsigned int line, unsigned int col);

void Line(Image image, colors color, char width,
    int ya, int xa, int yb, int xb);
void Rectangle(Image image, colors color, char width,
    int y, int x, int w, int h);
void Triangle(Image image, colors color, char width,
    int y1, int x1, int y2, int x2, int y3, int x3);

void Fill(Image image, colors color, int x, int y);

int maxim(int a, int b);
int minim(int a, int b);
