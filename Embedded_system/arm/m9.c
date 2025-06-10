int factorial(int n) {
  int y;
  for (y = 1; n > 1; n--) {
    y *= n;
  }
  return y;
}

int main() { factorial(5); }
