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

  int choice;

  do {
    printf("1. Input\n");
    printf("2. Print\n");
    printf("3. Search\n");
    printf("4. Delete\n");
    printf("5. Quit\n");
    printf("Enter your option: ");
    scanf("%d", &choice);

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
    default:
      printf("Wrong input. Try again!\n");
      break;
    }
  } while (choice != 5);
  return 0;
}

void input_menu(food **first, food **end) {
  food *tmp = NULL;
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
    tmp = malloc(sizeof(food));
    strcpy(tmp->food_name, input_name);
    tmp->price = food_price;
    tmp->next = NULL;

    if (*first == NULL) {
      *first = *end = tmp;
    } else {
      (*end)->next = tmp;
      *end = (*end)->next;
    }
  }
}

void output_menu(food *list) {
  // if the head is NULL, stop the printing out process.
  food *tmp = list;
  if (tmp == NULL) {
    printf("The list is empty.\n");
  }
  while (tmp != NULL) {
    printf("Name: %s, price: %.2f\n", tmp->food_name, tmp->price);
    tmp = tmp->next;
  }
}

void search_menu(food *list) {
  char input_name[30];
  int idx, found;
  food *tmp = NULL;
  while (1) {
    tmp = list;

    // if the head is NULL, stop the searching process.
    if (tmp == NULL) {
      printf("The list is empty.\n");
      break;
    }
    found = idx = 0;
    printf("What food are you looking for?(x to exit) ");
    scanf("%s", input_name);
    if (strcmp(input_name, "x") == 0) {
      printf("Finished searching\n");
      break;
    }
    while (tmp != NULL) {
      if (strcmp(tmp->food_name, input_name) == 0) {
        printf("Food is found! #%d on the list\n", idx + 1);
        printf("Its price: %.2f\n", tmp->price);
        found = 1;
      }
      idx++;
      tmp = tmp->next;
    }
    if (found == 0) {
      printf("NUFood not found on the list.\n");
    }
  }
}

void remove_menu(food **first, food **end) {
  food *prev = NULL, *tmp = NULL;
  char input_name[20];
  while (1) {
    prev = tmp = *first;

    // if the head is NULL, stop the removing process.
    if (*first == NULL) {
      printf("The list is empty.\n");
      break;
    }

    printf("Enter the food name you would like to delete:(x to exit) ");
    scanf("%s", input_name);
    if (strcmp(input_name, "x") == 0) {
      printf("Finish removing\n");
      break;
    }
    while (tmp != NULL) {
      if (strcmp(tmp->food_name, input_name) == 0) {
        break;
      }
      prev = tmp;
      tmp = prev->next;
    }

    if (*first == tmp) {
      printf("%s is removed from the list.\n", tmp->food_name);
      *first = tmp->next;
    }

    else if (tmp == *end) {
      *end = prev;
      printf("%s is removed from the list.\n", tmp->food_name);
      prev->next = NULL;
    }

    else if (tmp != NULL) {
      printf("%s is removed from the list.\n", tmp->food_name);
      prev->next = tmp->next;
    }

    else {
      printf("The food name is not existed on the list.\n");
    }
  }
}
