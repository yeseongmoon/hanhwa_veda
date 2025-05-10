#include <iostream>

const int MAX_SIZE = 999;
int arr[MAX_SIZE * MAX_SIZE];

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  int arr_size, target_num;
  std::cin >> arr_size >> target_num;

  int last_num = arr_size * arr_size;
  int row = -1, col = 0, arr_length = arr_size;

  while (1) {
    // Down
    for (int i = 0; i < arr_length; i++)
      arr[++row * arr_size + col] = last_num--;

    if (--arr_length == 0)
      break;

    // Right
    for (int i = 0; i < arr_length; i++)
      arr[row * arr_size + (++col)] = last_num--;

    // Up
    for (int i = 0; i < arr_length; i++)
      arr[--row * arr_size + col] = last_num--;
    if (--arr_length == 0)
      break;

    // Left
    for (int i = 0; i < arr_length; i++)
      arr[row * arr_size + (--col)] = last_num--;
  }

  // Print matrix
  for (int i = 0; i < arr_size; i++) {
    for (int j = 0; j < arr_size; j++) {
      std::cout << arr[i * arr_size + j] << " ";
    }
    std::cout << "\n";
  }

  // Find target number
  for (int i = 0; i < arr_size * arr_size; i++) {
    if (arr[i] == target_num) {
      std::cout << (i / arr_size) + 1 << " " << (i % arr_size) + 1 << std::endl;
      break;
    }
  }

  return 0;
}
