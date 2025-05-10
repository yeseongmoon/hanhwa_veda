#define _CRT_SECURE_NO_WARNINGS

#ifndef _MENU_H_
#define _MENU_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct food {
  char food_name[20];
  float price;
  struct food *next;
} food;

void input_menu(food **first, food **end);
void output_menu(food *first);
void search_menu(food *first);
void remove_menu(food **first, food **end);
void load(food **first, food **end);
void save(food *list);

#endif
