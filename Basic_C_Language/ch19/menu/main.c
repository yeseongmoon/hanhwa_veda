#include "menu.h"

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

  load(&head, &tail);

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
      save(head);
      break;
    default:
      printf("Wrong input. Try again!\n");
      break;
    }
  } while (choice != 5);

  // cleanup the memory
  food *tmp;
  while (head != NULL) {
    tmp = head;
    head = head->next;
    free(tmp);
  }
  head = tail = NULL;
  return 0;
}
