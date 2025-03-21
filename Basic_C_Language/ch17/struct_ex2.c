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
  char input, empty = 1;
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
    }
  }
  if (empty == 0) {
    struct st *temp = head;
    while (temp != NULL) {
      printf("%s %d\n", temp->name, temp->kor);
      temp = temp->next;
    }
    printf("head : %s, %d\n", head->name, head->kor);
    printf("tail : %s, %d\n", tail->name, tail->kor);
  } else
    printf("Linked list is empty\n");

  return 0;
}
