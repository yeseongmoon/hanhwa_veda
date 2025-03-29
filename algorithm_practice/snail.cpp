#include <iostream>
#include <vector>

int main() {
  int arr_size, target_num;
  std::cin >> arr_size >> target_num;

  std::vector<std::vector<int>> arr(arr_size, std::vector<int>(arr_size));

  int last_num = arr_size * arr_size;
  int row = -1, col = 0, arr_length = arr_size;

  while (1) {
    // Down
    for (int i = 0; i < arr_length; i++)
      arr[++row][col] = last_num--;
    if (--arr_length == 0)
      break;

    // Right
    for (int i = 0; i < arr_length; i++)
      arr[row][++col] = last_num--;

    // Up
    for (int i = 0; i < arr_length; i++)
      arr[--row][col] = last_num--;
    if (--arr_length == 0)
      break;

    // Left
    for (int i = 0; i < arr_length; i++)
      arr[row][--col] = last_num--;
  }

  // Print matrix
  for (int i = 0; i < arr_size; i++) {
    for (int j = 0; j < arr_size; j++) {
      std::cout << arr[i][j] << " ";
    }
    std::cout << std::endl;
  }

  // Find target number
  for (int i = 0; i < arr_size; i++) {
    for (int j = 0; j < arr_size; j++) {
      if (arr[i][j] == target_num) {
        std::cout << i + 1 << " " << j + 1 << std::endl;
      }
    }
  }

  return 0;
}
