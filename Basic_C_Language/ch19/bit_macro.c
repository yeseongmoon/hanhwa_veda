#include <stdio.h>

// define bit macro function
#define bitSet(data, pos) ((data) | (1 << pos))
#define bitClear(data, pos) ((data) & ~(1 << pos))
#define bitToggle(data, pos) ((data) ^ (1 << pos))

int main(void) {
  unsigned short data;
  int pos, menu;
  printf("Input a short integer data => ");
  scanf("%hd", &data);
  while (1) {
    do {
      printf("Bit Test(1.Bit Set, 2.Bit Clear, 3.Bit Toggle, 4:Quit) => ");
      scanf("%d", &menu);
    } while (menu < 1 || menu > 4);
    if (menu == 4)
      break;
    do {
      printf("Bit Position(0~15, -1:Quit) => ");
      scanf("%d", &pos);
    } while (menu < -1 || menu > 15);
    if (pos == -1)
      continue;
    switch (menu) {
    case 1:
      printf("Bit_%d Set of 0x%04X => 0x%04X\n", pos, data, bitSet(data, pos));
      break;
    case 2:
      printf("Bit_%d Clear of 0x%04X => 0x%04X\n", pos, data,
             bitClear(data, pos));
      break;
    case 3:
      printf("Bit_%d Toggle of 0x%04X => 0x%04X\n", pos, data,
             bitToggle(data, pos));
      break;
    }
  }
  return 0;
}
