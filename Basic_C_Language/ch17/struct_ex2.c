#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct st {
  char name[22];
  int kor;
  struct st *next;
};

int main(int argc, char *argv[]) {
  struct st *st_ptr = NULL, *head = NULL, *tail = NULL;
  char input, empty = 1, count = 1;
  while (1) {
    printf("Do you want to add a list? y/n: ");
    scanf("%c", &input);
    getchar();
    if (input == 'n')
      break;
    if (input != 'y') {
      continue;
    } else {
      empty = 0;
      st_ptr = malloc(sizeof(struct st));
      if (st_ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
      }
      printf("Name & score: ");
      scanf("%s%d", st_ptr->name, &st_ptr->kor);
      getchar();
      st_ptr->next = NULL;

      if (head == NULL) {
        head = tail = st_ptr;
      } else {
        tail->next = st_ptr;
        tail = tail->next;
      }
      count++;
    }
  }
  if (empty == 0) {
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
  st_ptr = head;

  if (remove_idx == 1) {
    st_ptr = st_ptr->next;
    head = st_ptr;
  }

  while (st_ptr != NULL) {
    if (st_ptr->next->next == NULL) {
      st_ptr->next = NULL;
      tail = st_ptr;
    }
    if ((idx + 1) == remove_idx)
      st_ptr->next = st_ptr->next->next;
    st_ptr = st_ptr->next;
    idx++;
  }

  st_ptr = head;
  printf("Linked List: \n");
  while (st_ptr != NULL) {
    printf("%s %d\n", st_ptr->name, st_ptr->kor);
    st_ptr = st_ptr->next;
  }
  printf("head : %s, %d\n", head->name, head->kor);
  printf("tail : %s, %d\n", tail->name, tail->kor);

  return 0;
}
