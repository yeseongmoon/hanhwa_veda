#include "menu.h"

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
    if (tmp == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      continue;
    }
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
  if (list == NULL)
    printf("The list is empty.\n");

  else {
    food *tmp = list;
    while (tmp != NULL) {
      printf("Name: %s, Price: %.2f\n", tmp->food_name, tmp->price);
      tmp = tmp->next;
    }
  }
}

void search_menu(food *list) {
  // if the head is NULL, stop the searching process.
  if (list == NULL)
    printf("The list is empty.\n");

  else {
    char input_name[20];
    int idx, found;
    food *tmp = NULL;

    while (1) {
      tmp = list;
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
        printf("Food not found.\n");
      }
    }
  }
}

void remove_menu(food **first, food **end) {
  if (*first == NULL)
    printf("The list is empty.\n");

  else {
    food *prev = NULL, *curr = NULL;
    char input_name[20];
    while (1) {
      // if the head is NULL, stop the removing process.
      if (*first == NULL) {
        printf("The list is empty.\n");
        break;
      }

      prev = curr = *first;

      printf("Enter the food name you would like to delete:(x to exit) ");
      scanf("%s", input_name);
      if (strcmp(input_name, "x") == 0) {
        printf("Finish removing\n");
        break;
      }

      while (curr != NULL) {
        if (strcmp(curr->food_name, input_name) == 0) {
          break;
        }
        prev = curr;
        curr = prev->next;
      }

      if (*first == curr) {
        printf("%s is removed from the list.\n", curr->food_name);
        *first = curr->next;
      }

      else if (curr == *end) {
        *end = prev;
        printf("%s is removed from the list.\n", curr->food_name);
        prev->next = NULL;
      }

      else if (curr != NULL) {
        printf("%s is removed from the list.\n", curr->food_name);
        prev->next = curr->next;
      }

      else {
        printf("The food name is not existed on the list.\n");
      }

      // immediate freeing memory to prevent from potential memory leak &
      // wasting memory
      free(curr);
      curr = NULL;

      // for convenience
      food *tmp = *first;
      printf("Updated menu list:\n");
      while (tmp != NULL) {
        printf("Name: %s, Price: %.2f\n", tmp->food_name, tmp->price);
        tmp = tmp->next;
      }
    }
  }
}

void load(food **first, food **end) {
  FILE *fp = fopen("menu.txt", "rb");
  if (fp == NULL) {
    fprintf(stderr, "File is not existed.\n");
  } else {
    while (1) {
      food *tmp = malloc(sizeof(food));
      if (tmp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        break;
      }
      size_t i = fread(tmp, sizeof(food), 1, fp);
      if (i == 0) {
        free(tmp);
        tmp = NULL;
        break;
      }
      if (*first == NULL) {
        *first = *end = tmp;
      } else {
        (*end)->next = tmp;
        *end = (*end)->next;
      }
    }
    fclose(fp);
  }
}

void save(food *list) {
  FILE *fp = fopen("menu.txt", "wb");
  if (fp == NULL) {
    fprintf(stderr, "File is not existed.\n");
  } else {
    food *tmp = list;
    while (tmp != NULL) {
      fwrite(tmp, sizeof(food), 1, fp);
      tmp = tmp->next;
    }
    fclose(fp);
  }
}
