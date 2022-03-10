#include "utils.h"

int main() {
    char *task = NULL, *path = NULL, width = 0;;
    task = malloc(task_len * sizeof(char));
    Image image1, image2;
    colors color;
    while (1) {
        fgets(task, task_len, stdin);
        path = strtok(task, " ");
        if (strstr(task, "save") != NULL) {
            // save <path>

            path = strtok(NULL, " \n");
            Save(image1, path);
        } else if (strstr(task, "edit") != NULL) {
            // edit <path>

            path = strtok(NULL, " \n");
            image1 = Edit(path);
        } else if (strstr(task, "insert") != NULL) {
            // insert <path> y x

            char *p = NULL;
            unsigned int x = 0, y = 0;
            path = strtok(NULL, " \n");
            p = strtok(NULL, " \n");
            x = atoi(p);
            p = strtok(NULL, " \n");
            y = atoi(p);
            image2 = Edit(path);
            Insert(image1, image2, y, x);
        } else if (strstr(task, "set") != NULL) {
            char *p = NULL;
            p = strtok(NULL, " \n");
            if (strstr(p, "draw_color") != NULL) {
                // set draw_color R G B

                p = strtok(NULL, " \n");
                color.red = (char)(atoi(p));
                p = strtok(NULL, " \n");
                color.green = (char)(atoi(p));
                p = strtok(NULL, " \n");
                color.blue = (char)(atoi(p));
            } else if (strstr(p, "line_width") != NULL) {
                // set line_width x

                p = strtok(NULL, " \n");
                width = (char)(atoi(p));
            }
        } else if (strstr(task, "draw") != NULL) {
            char *p = NULL;
            p = strtok(NULL, " \n");
            if (strstr(p, "line") != NULL) {
                // draw line y1 x1 y2 x2

                int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
                p = strtok(NULL, " \n");
                y1 = atoi(p);
                p = strtok(NULL, " \n");
                x1 = atoi(p);
                p = strtok(NULL, " \n");
                y2 = atoi(p);
                p = strtok(NULL, " \n");
                x2 = atoi(p);
                Line(image1, color, width, x1, y1, x2, y2);
            } else if (strstr(p, "rectangle") != NULL) {
                // draw rectangle y1 x1 width height

                int y = 0, x = 0, w = 0, h = 0;
                p = strtok(NULL, " \n");
                y = atoi(p);
                p = strtok(NULL, " \n");
                x = atoi(p);
                p = strtok(NULL, " \n");
                w = atoi(p);
                p = strtok(NULL, " \n");
                h = atoi(p);
                Rectangle(image1, color, width, y, x, w, h);
            } else if (strstr(p, "triangle") != NULL) {
                // draw triangle y1 x1 y2 x2 y3 x3

                int y1 = 0, x1 = 0, y2 = 0, x2 = 0, y3 = 0, x3 = 0;
                p = strtok(NULL, " \n");
                y1 = atoi(p);
                p = strtok(NULL, " \n");
                x1 = atoi(p);
                p = strtok(NULL, " \n");
                y2 = atoi(p);
                p = strtok(NULL, " \n");
                x2 = atoi(p);
                p = strtok(NULL, " \n");
                y3 = atoi(p);
                p = strtok(NULL, " \n");
                x3 = atoi(p);
                Triangle(image1, color, width, y1, x1, y2, x2, y3, x3);
            }
        } else if (strstr(task, "fill") != NULL) {
            // fill y x

            int x = 0, y = 0;
            char *p = NULL;
            p = strtok(NULL, " \n");
            y = atoi(p);
            p = strtok(NULL, " \n");
            x = atoi(p);
            Fill(image1, color, image1.infoheader.height - 1 - x, y);
        } else {
            // quit

            free(task);
            int i = 0;
            for (i = 0; i < no_pixels; i++)
                free(image1.mat[i]);
            free(image1.mat);
            return 0;
        }
    }
}
