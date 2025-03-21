#define _CRT_SECURE_NO_WARNINGS

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

int main(int argc, char *argv[]) {
  /*
   * menu program
   * 1. input
   * 2. print
   * 3. search
   * 4. delete
   * 5. quit
   * */

  food *head = NULL, *tail = NULL;

  int choice, food_num = 0;

  while (1) {
    printf("1. Input\n");
    printf("2. Print\n");
    printf("3. Search\n");
    printf("4. Delete\n");
    printf("5. Quit\n");
    printf("Enter your option: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 5) {
      printf("Invalid input\n");
      break;
    }
    if (choice == 5) {
      printf("Quitting...\n");
      break;
    }

    switch (choice) {
    case 1:
      input_menu(&head, &tail);
      break;
    case 2:
      output_menu(head);
      break;
    case 3:
      search_menu(head);
      break;
    case 4:
      remove_menu(&head, &tail);
      break;
    case 5:
      printf("Quitting...\n");
      break;
    }
  }
  return 0;
}

void input_menu(food **first, food **end) {
  food *st_ptr = NULL;
  char input_name[20];
  float food_price;
  while (1) {
    printf("Please enter a food name(x to exit): ");
    scanf("%s", input_name);
    if (strcmp(input_name, "x") == 0) {
      break;
    }
    printf("Please enter the price: ");
    scanf("%f", &food_price);
    st_ptr = malloc(sizeof(food));
    strcpy(st_ptr->food_name, input_name);
    st_ptr->price = food_price;
    st_ptr->next = NULL;

    if (*first == NULL) {
      *first = *end = st_ptr;
    } else {
      (*end)->next = st_ptr;
      *end = (*end)->next;
    }
  }
}

void output_menu(food *list) {
  food *tmp = list;
  if (tmp == NULL) {
    printf("There is no food on the list.\n");
  }
  while (tmp != NULL) {
    printf("Name: %s, price: %.2f\n", tmp->food_name, tmp->price);
    tmp = tmp->next;
  }
}

void search_menu(food *list) {
  char input_name[30];
  int found = 0;
  while (1) {
    food *tmp = list;
    int i = 0;
    printf("What food are you looking for?(x to exit) ");
    scanf("%s", input_name);
    getchar();
    if (strcmp(input_name, "x") == 0) {
      printf("Finished searching\n");
      break;
    }
    while (tmp != NULL) {
      if (strcmp(tmp->food_name, input_name) == 0) {
        printf("Food is found! %dth on the list\n", i + 1);
        printf("Its price: %.2f\n", tmp->price);
        found = 1;
      }
      i++;
      tmp = tmp->next;
    }
    if (found == 0) {
      printf("Food not found on the list.\n");
    }
  }
}

void remove_menu(food **first, food **end) {
  char input_name[20];
  int found = 0;
  while (1) {
    food *prev = NULL;
    food *prev_prev = NULL;
    food *tmp = NULL;
    int count = 0;
    prev = prev_prev = tmp = *first;
    if (*first == NULL) {
      printf("The food list is empty.\n");
      break;
    }
    printf("Enter the food name you would like to delete:(x to exit) ");
    scanf("%s", input_name);
    if (strcmp(input_name, "x") == 0) {
      printf("Finish removing\n");
      break;
    }
    while (1) {
      if (strcmp(tmp->food_name, input_name) == 0) {
        found = 1;
        break;
      }
      prev = tmp;
      tmp = prev->next;
    }
    // delete head
    if (*first == tmp) {
      *first = tmp->next;
    }

    if (tmp != NULL) {
      prev->next = tmp->next;
      free(tmp);
    }

    // delete tail
    if (tmp == *end) {
      *end = prev;
      prev->next = NULL;
    }
  }
}
