#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char name[20];
  int score;
} Student;

double calc_avg(Student *student, const int size) {
  int sum = 0;
  for (int i = 0; i < size - 1; i++) {
    sum += student[i].score;
  }
  return (double)sum / (size - 1);
}

void input_scores(Student *student, const int size) {
  Student new_student;

  printf("학생 %d의 이름: ", size);
  scanf("%s", new_student.name);
  printf("학생 %d의 점수: ", size);
  scanf("%d", &new_student.score);

  student[size - 1] = new_student;

  printf("\n");
}

void print_scores(Student *student, const int size) {
  for (int i = 0; i < size - 1; i++) {
    printf("%s : %d\n", student[i].name, student[i].score);
  }
  printf("\n");
}

Student *load_data(int *size) {
  FILE *fptr = fopen("student.txt", "r");
  Student *temp = NULL;

  if (fptr == NULL) {
    printf("파일이 존재하지 않습니다.\n");
  } else {
    printf("학생 정보가 로드되었습니다.\n");
    fscanf(fptr, "%d", size);
    temp = (Student *)malloc(sizeof(Student) * (*size));
    for (int i = 0; i < *size; i++) {
      fscanf(fptr, "%s %d", temp[i].name, &temp[i].score);
    }
    (*size)++;
  }
  fclose(fptr);
  return temp;
}

int main(int argc, char *argv[]) {
  int size = 1, menu_input, data_write = 0;
  double avg;
  Student *students = (Student *)malloc(sizeof(Student));
  Student *temp = load_data(&size);
  FILE *fptr;
  if (temp != NULL)
    students = temp;

  do {
    printf("---- 메뉴 ----\n");
    printf("1. 학생 추가\n");
    printf("2. 학생 정보 출력\n");
    printf("3. 평균 점수 출력\n");
    printf("4. 종료\n");
    printf("메뉴를 선택하세요(1/2/3/4): ");
    scanf("%d", &menu_input);

    switch (menu_input) {
    case 1:
      if (size == 1) {
        input_scores(students, size);
        ++size;
      } else {
        students = realloc(students, sizeof(Student) * size);
        input_scores(students, size);
        ++size;
      }
      data_write = 1;
      break;

    case 2:
      printf("학생 목록:\n");
      if (size == 1)
        printf("입력된 학생 정보가 없습니다.\n");
      else {
        print_scores(students, size);
      }
      break;

    case 3:
      avg = calc_avg(students, size);
      printf("평균 점수: %.2lf\n", avg);
      break;

    case 4:
      if (data_write == 0) {
        printf("저장 할 데이터가 존재하지 않습니다.\n");
        printf("프로그램을 종료합니다.\n");
        exit(0);
      }

      fptr = fopen("student.txt", "w");
      // checking if the file is created
      if (fptr == NULL) {
        printf("파일이 로드되지 않았습니다.\n");
        exit(0);
      }
      fprintf(fptr, "%d\n", size - 1);
      for (int i = 0; i < size - 1; i++) {
        fprintf(fptr, "%s %d\n", students[i].name, students[i].score);
      }
      fclose(fptr);

      printf("학생 정보가 저장되었습니다.\n");
      printf("프로그램을 종료합니다.\n");
      break;

    default:
      printf("올바른 옵션이 아닙니다. 다시 시도해주세요.\n");
      break;
    }
  } while (menu_input != 4);
  free(students);

  return 0;
}
