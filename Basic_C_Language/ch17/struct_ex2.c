#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct st {
  char name[22];
  int kor;
  struct st *next;
};

void input(struct st **head, struct st **tail) {
  struct st *st_ptr = NULL, *tmp = NULL;
  char input;
  while (1) {
    printf("Do you want to add a list? y/n: ");
    scanf("%c", &input);
    getchar();
    if (input == 'n')
      break;
    if (input != 'y') {
      continue;
    } else {
      st_ptr = malloc(sizeof(struct st));
      if (st_ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(0);
      }
      printf("Name & score: ");
      scanf("%s%d", st_ptr->name, &st_ptr->kor);
      getchar();
      st_ptr->next = NULL;

      if (*head == NULL) {
        *head = *tail = st_ptr;
      } else {
        (*tail)->next = st_ptr;
        *tail = (*tail)->next;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  struct st *head = NULL, *tail = NULL;
  struct st *st_ptr;
  input(&head, &tail);
  if (head != NULL) {
    st_ptr = head;
    printf("Linked List: \n");
    while (st_ptr != NULL) {
      printf("%s %d\n", st_ptr->name, st_ptr->kor);
      st_ptr = st_ptr->next;
    }
    printf("head : %s, %d\n", head->name, head->kor);
    printf("tail : %s, %d\n", tail->name, tail->kor);
  } else
    printf("Linked list is empty\n");

  printf("Which list would you want to remove?: ");
  int remove_idx, idx = 1;
  scanf("%d", &remove_idx);

  struct st *tmp;
  tmp = st_ptr = head;
  for (int i = 0; i < remove_idx - 1; i++) {
    st_ptr = tmp;
    tmp = st_ptr->next;
  }

  if (head == tmp) {
    head = tmp->next;
  }

  if (tmp == NULL) {
    tail = st_ptr;
    st_ptr->next = NULL;
  } else {
    st_ptr->next = tmp->next;
  }

  st_ptr = head;
  printf("Linked List: \n");
  while (st_ptr != NULL) {
    printf("%s %d\n", st_ptr->name, st_ptr->kor);
    st_ptr = st_ptr->next;
  }
  printf("head : %s, %d\n", head->name, head->kor);
  printf("tail : %s, %d\n", tail->name, tail->kor);

  st_ptr = head;
  while (st_ptr) {
    st_ptr = st_ptr->next;
    free(st_ptr);
  }

  return 0;
}
