#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char name[20];
  int score;
} Student;

double calc_avg(Student *student, const int student_num) {
  int sum = 0;
  for (int i = 0; i < student_num; i++) {
    sum += student[i].score;
  }
  return (double)sum / student_num;
}

Student *add_student(Student *student, int *student_num) {
  Student *new_student = NULL;

  // if there is no student, allocate a new array and store the first input
  if (*student_num == 1 && student == NULL) {
    new_student = (Student *)malloc(sizeof(Student));
    printf("학생 %d의 이름: ", *student_num);
    scanf("%s", new_student[*student_num - 1].name);
    printf("학생 %d의 점수: ", *student_num);
    scanf("%d", &new_student[*student_num - 1].score);
    printf("\n");

    return new_student;
  }

  // if there's a student in the array, expand the array by 1 and store the
  // input
  *student_num += 1;
  new_student = realloc(student, sizeof(Student) * (*student_num));
  printf("학생 %d의 이름: ", *student_num);
  scanf("%s", new_student[*student_num - 1].name);
  printf("학생 %d의 점수: ", *student_num);
  scanf("%d", &new_student[*student_num - 1].score);
  printf("\n");

  return new_student;
}

void print_scores(Student *student, const int student_num) {
  for (int i = 0; i < student_num; i++) {
    printf("%s : %d\n", student[i].name, student[i].score);
  }
  printf("\n");
}

Student *load_data(int *student_num) {
  FILE *fptr = fopen("student.txt", "r");
  Student *temp = NULL;

  if (fptr == NULL) {
    printf("파일이 존재하지 않습니다.\n");
  } else {
    printf("학생 정보가 로드되었습니다.\n");
    fscanf(fptr, "%d", student_num);
    temp = (Student *)malloc(sizeof(Student) * (*student_num));
    for (int i = 0; i < *student_num; i++) {
      fscanf(fptr, "%s %d", temp[i].name, &temp[i].score);
    }
  }
  fclose(fptr);
  return temp;
}

void store_data(Student *student, const int student_num) {
  FILE *fptr = fopen("student.txt", "w");
  if (fptr == NULL) {
    printf("파일이 로드되지 않았습니다.\n");
  } else {
    fprintf(fptr, "%d\n", student_num);
    for (int i = 0; i < student_num; i++) {
      fprintf(fptr, "%s %d\n", student[i].name, student[i].score);
    }
    fclose(fptr);
    printf("학생 정보가 저장되었습니다.\n");
    printf("프로그램을 종료합니다.\n");
  }
}

int main(int argc, char *argv[]) {
  int student_num = 1, data_write = 0, menu_input;
  double avg = 0;
  Student *students = NULL;
  Student *temp = load_data(&student_num);
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
      students = add_student(students, &student_num);
      data_write = 1;
      break;

    case 2:
      printf("학생 목록:\n");
      if (student_num == 1)
        printf("입력된 학생 정보가 없습니다.\n");
      else {
        print_scores(students, student_num);
      }
      break;

    case 3:
      avg = calc_avg(students, student_num);
      printf("평균 점수: %.2lf\n", avg);
      break;

    case 4:
      if (data_write == 0) {
        printf("저장 할 데이터가 존재하지 않습니다.\n");
        printf("프로그램을 종료합니다.\n");
        break;
      }
      store_data(students, student_num);
      break;

    default:
      printf("올바른 옵션이 아닙니다. 다시 시도해주세요.\n");
      break;
    }
  } while (menu_input != 4);
  free(students);

  return 0;
}
