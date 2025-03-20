#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void input_member(char (*name)[30], char (*addr)[100], int *count);
void output_member(char (*name)[30], char (*addr)[100], int *count);
void search_member(char (*name)[30], char (*addr)[100], int *count);
void remove_member(char (*name)[30], char (*addr)[100], int *count);

int main(int argc, char *argv[]) {
  /*
   * menu program
   * 1. input
   * 2. print
   * 3. search
   * 4. delete
   * 5. quit
   * */

  int choice;
  char names[20][30], address[20][100];
  void (*fp[4])(char(*name)[30], char(*addr)[100], int *count) = {
      input_member, output_member, search_member, remove_member};
  int ppl_count = 0;

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

    fp[choice - 1](names, address, &ppl_count);
  }
  return 0;
}

void input_member(char (*name)[30], char (*addr)[100], int *count) {
  char input_name[30], input_addr[100];
  while (1) {
    printf("Please enter a person's name and their address: ");
    scanf("%s", input_name);
    if (strcmp(input_name, "x") == 0) {
      break;
    }
    scanf("%s", input_addr);
    strcpy(name[*count], input_name);
    strcpy(addr[*count], input_addr);
    *count += 1;
  }
}

void output_member(char (*name)[30], char (*addr)[100], int *count) {
  for (int i = 0; i < *count; i++) {
    printf("Name: %s, Addr: %s\n", name[i], addr[i]);
  }
}

void search_member(char (*name)[30], char (*addr)[100], int *count) {
  char input_name[30];
  while (1) {
    printf("What name are you looking for? ");
    scanf("%s", input_name);
    if (strcmp(input_name, "x") == 0) {
      printf("Finished searching\n");
      break;
    }
    for (int i = 0; i < *count; i++) {
      if (strcmp(name[i], input_name) == 0)
        printf("Name found on %dth on the list, and his/her address is %s\n",
               i + 1, addr[i]);
    }
  }
}

void remove_member(char (*name)[30], char (*addr)[100], int *count) {
  char *input_name;
  while (1) {
    printf("Enter the name you would like to delete: ");
    scanf("%s", input_name);
    if (strcmp(input_name, "x") == 0) {
      printf("Finish removing\n");
      break;
    }
    for (int i = 0; i < *count; i++) {
      if (strcmp(name[i], input_name) == 0) {
        memcpy(name[i], name[i + 1], (*count - (i + 1)) * sizeof(name[0]));
        memcpy(addr[i], addr[i + 1], (*count - (i + 1)) * sizeof(addr[0]));
        *count -= 1;
        printf("Done removing\n");
        break;
      }
    }
  }
}
