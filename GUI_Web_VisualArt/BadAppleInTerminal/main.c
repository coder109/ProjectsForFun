/*
 * Author: CoderLock
 * Time: 2024-1-23
 * Comment: Use libpng and ncurses.
 */

#include <png.h>
#include <pngconf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ncurses.h>
#include <math.h>
#include <unistd.h>

#define PNG_DIR "./pngs"
#define K 0.547373141f
#define THRESHOLD 200

// Output-related params
WINDOW *window;
int window_height = 0, window_width = 0;

void InitWindow() {
  window = initscr();
  refresh();
  getmaxyx(window, *&window_height, *&window_width);
  start_color();
  // Hide cursor
  curs_set(0);
  refresh();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_WHITE);
  init_pair(3, COLOR_BLACK, COLOR_BLACK);
  wbkgd(window, COLOR_PAIR(1));
  attron(A_BOLD);
}

unsigned int RGB2Gray(unsigned int R, unsigned int G, unsigned int B) {
  return (R+G+B)/3;
}

int GetPNGNums(const char* path) {
    DIR* directory = NULL;
    int total_num = 0;
    if ((directory = opendir(path)) == NULL) {
        fprintf(stderr, "Can't open %s\n", path);
        return EXIT_FAILURE;
    }

    struct dirent* entry = NULL;
    while ((entry = readdir(directory)) != NULL) {
        if (entry->d_type != DT_DIR) {
	  ++total_num;
        }
    }
    closedir(directory);
    return total_num;
}

png_bytepp ReadPNG(char* file_name, int* height, int* width) {
  // Read file
  FILE* fp = fopen(file_name, "rb");
  if(fp == NULL) {
    printf("Unable to read!\n");
    exit(-1);
  }
  // Initialize
  png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_infop info_ptr = png_create_info_struct(png_ptr);
  png_init_io(png_ptr, fp);
  // Read Info of a picture
  png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
  png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
  // Get height and width of a png picture
  *height = png_get_image_height(png_ptr, info_ptr);
  *width = png_get_image_width(png_ptr, info_ptr);
  png_destroy_read_struct(&png_ptr, NULL, NULL);
  // Deinitalize
  fclose(fp);
  return row_pointers;
}

int main(int argc, char **argv) {
  InitWindow();
  int png_num = GetPNGNums(PNG_DIR);
  int height = 0, width = 0;
  char file_name[50] = {'\0'};
  char final_name[50] = {'\0'};
  for(int i = 1; i <= png_num; i++) {
    // Get File Name
    snprintf(file_name, 50, "/%04d.png", i);
    strcpy(final_name, PNG_DIR);
    strcat(final_name, file_name);
    // Read Picture
    png_bytepp row_pointers = ReadPNG(final_name, &height, &width);
    // Output
    int curr_row = 0, curr_col = 0;
    for(int h = 0; h < height; h+=3) {
      curr_col = 0;
      for(int w = 0; w < width; w+=2) {
	unsigned int r = row_pointers[h][w*3+0],
	  g = row_pointers[h][w*3+1],
	  b = row_pointers[h][w*3+2];
	unsigned int gray = RGB2Gray(r, g, b);
	if(gray >= THRESHOLD) {
	  attron(COLOR_PAIR(2));
	  mvaddch(curr_row, curr_col, ' ');
	  attroff(COLOR_PAIR(2));
	} else {
	  attron(COLOR_PAIR(3));
	  mvaddch(curr_row, curr_col, ' ');
	  attroff(COLOR_PAIR(3));
	}
	curr_col++;
      }
      curr_row++;
    }
    refresh();
    // Hohoho, magic number!!!!!!
    // Try to figure it out yourself!
    usleep(42172);
    free(row_pointers);
  }
  return 0;
}
