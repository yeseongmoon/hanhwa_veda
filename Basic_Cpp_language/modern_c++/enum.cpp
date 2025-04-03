#include <iostream>

enum class Color {
  RED = 10,
  ORANGE,
  YELLOW,
  GREEN,
  BLUE,
  NAVY,
  PURPLE,
};

enum class Traffic_light {
  GREEN,
  RED,
  YELLOW,
};

int main(int argc, char *argv[]) {
  Traffic_light light = Traffic_light::RED;
  Color color = Color::RED;
  std::cout << "Traffic_light: " << static_cast<int>(light)
            << " Color : " << static_cast<int>(color) << std::endl;
  return 0;
}
