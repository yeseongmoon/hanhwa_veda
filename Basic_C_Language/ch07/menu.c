#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

void input_member(int *korean, int *math, int *english, float *average,
                  int *stduent);
void output_member(const float *average, int *student);
void search_member(const float *average, int *student);
void remove_member(int *korean, int *math, int *english, float *average,
                   int *student_count);

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
  int kor[30] = {0}, math[30] = {0}, eng[30] = {0};
  float avg[30] = {0};
  int student_count = 0;

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
      input_member(kor, math, eng, avg,
                   &student_count); // call the function, edge case: if the
                                    // input is -1, end the function
      break;
    case 2:
      output_member(avg, &student_count); // num, avg
      break;
    case 3:
      search_member(
          avg,
          &student_count); // either the highest score student # and the score
                           // or the lowest score student # and the score
      break;
    case 4:
      remove_member(kor, math, eng, avg, &student_count);
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

void input_member(int *korean, int *math, int *english, float *average,
                  int *student) {
  int k_score, m_score, e_score;
  while (1) {
    printf("Enter the score\n");
    printf("Enter -1 if you want to go back to menu.\n");
    printf("--> ");
    scanf("%d", &k_score);
    if (k_score == -1)
      break;
    scanf("%d%d", &m_score, &e_score);
    if (k_score > 100 || k_score < 0)
      printf("This is not a valid score. Try Again!\n");
    else if (m_score > 100 || m_score < 0)
      printf("This is not a valid score. Try Again!\n");
    else if (e_score > 100 || e_score < 0)
      printf("This is not a valid score. Try Again!\n");
    else {
      korean[*student] = k_score;
      math[*student] = m_score;
      english[*student] = e_score;
      average[*student] = (float)(k_score + m_score + e_score) / 3;
      *student += 1;
    }
  }
}

void output_member(const float *average, int *student) {
  for (int i = 0; i < *student; i++) {
    printf("Student #%d's average score is %.2f\n", i + 1, average[i]);
  }
}

void search_member(const float *average, int *student) {
  int max = average[0], max_idx = 0;
  int min = average[0], min_idx = 0;
  for (int i = 0; i < *student; i++) {
    if (max < average[i]) {
      max = average[i];
      max_idx = i;
    }
  }

  for (int i = 0; i < *student; i++) {
    if (min > average[i]) {
      min = average[i];
      min_idx = i;
    }
  }
  printf("Student #%d got the highest average by %d\n", max_idx + 1, max);
  printf("Student #%d got the lowest average by %d\n", min_idx + 1, min);
}

void remove_member(int *korean, int *math, int *english, float *average,
                   int *student_count) {
  int student_num;
  printf("Enter the Stduent# to remove the student\n");
  printf("--> ");
  scanf("%d", &student_num);
  memcpy(&korean[student_num - 1], &korean[student_num],
         (30 - student_num - 2) * sizeof(int));
  memcpy(&math[student_num - 1], &math[student_num],
         (30 - student_num - 2) * sizeof(int));
  memcpy(&english[student_num - 1], &english[student_num],
         (30 - student_num - 2) * sizeof(int));
  memcpy(&average[student_num - 1], &average[student_num],
         (30 - student_num - 2) * sizeof(float));
  printf("Studnet #%d is successfully removed from the list.\n", student_num);
  *student_count -= 1;
}
