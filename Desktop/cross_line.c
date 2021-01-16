#include <stdio.h>

enum {height = 21, width = 21, gap = 6, remain = 0};
char pixel_map[height * width];
char *imgptr = pixel_map;

void show_pixel(void *ptr, int w, int h)
{
    for (int c = 0; c < w; ++c) {
        fputs("＝", stdout);
    }
    putc('\n', stdout);
    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            fputs((pixel_map[r*w + c] == 2) ? (pixel_map[r*w + c] = 1, "Ｏ")
                : (pixel_map[r*w + c]) ? "ｘ" : "　", stdout);
        }
        putc('\n', stdout);
    }
    for (int c = 0; c < w; ++c) {
        fputs("＝", stdout);
    }
    putc('\n', stdout);
}

void draw_pixel(void *ptr, int x, int y, int w, int h, int r)
{
    pixel_map[y*w + x] = 2;
    show_pixel(ptr, w, h);
}

int main(void)
{
    int i;
    int j;
    int k;
    for (j = 0; j < height; j += gap) {
        for (k = 0; k < gap; ++k) {
            for (i = 0; i < width; i += gap) {
                if (!(i+k >= width || j+k >= height)) {
                    draw_pixel(imgptr, i+k, j+k, width, height, remain);
                }
                if (!(k == 0 || k == gap-k || i+gap-k >= width || j+k >= height)) {
                    draw_pixel(imgptr, i+gap-k, j+k, width, height, remain);
                }
            }
        }
    }
}
