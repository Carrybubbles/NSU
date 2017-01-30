#ifndef _IMAGE_ 
#define _IMAGE_
typedef struct {
  char* name;
  int rows; 
  int cols;
  int** data;
} image;

typedef struct 
{
  int len;
  image** Aimg; // array of images(pgm)
  int** target; // special symbols for recognition
} list;

image* create_img(int Rn, int Cn, char* name);
image* img_open(char* filename);
void free_img(image* img);
void write_img(image* picture, char* filename);
list* create_imgL(void);
void free_list(list* Ilist, int size);
void add_imgL(list* Ilist, image* img);
void load_images_from_file(char* filename, list* Ilist);
void load_data_to_list(list* Ilist, FILE* file, int size);
list* cut_captcha(int num_of_char,char* filename);

#endif