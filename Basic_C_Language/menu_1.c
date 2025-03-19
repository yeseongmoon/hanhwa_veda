#include <stdio.h>

int main(int argc, char *argv[]) {
  /*
   * menu program
   * 1. select
   * 2. print
   * 3. search
   * 4. delete
   * 5. quit
   * */
  int choice;

  do {
    printf("1.select\n");
    printf("2.print\n");
    printf("3.search\n");
    printf("4.delete\n");
    printf("5.quit\n");
    printf("Enter your option: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("you select option #1\n");
      break;
    case 2:
      printf("you select option #2\n");
      break;
    case 3:
      printf("you select option #3\n");
      break;
    case 4:
      printf("you select option #4\n");
      break;
    case 5:
      printf("Quitting...\n");
      return 0;
    default:
      printf("you select the wrong option\n");
      break;
    }
  } while (choice != 5);
  return 0;
}
