#include <iostream>
#include <map>

int main(int argc, char *argv[]) {
  std::map<std::string, std::string> vocab;
  std::string eng, kor, input;
  for (int i = 0; i < 10; i++) {
    std::cout << "Enter one word in two languages: (ENG KOR) ";
    std::cin >> eng >> kor;
    // vocab.insert({eng, kor});
    vocab[eng] = kor;
  }

  while (1) {
    std::cout << "Enter an English word: (x for exit) ";
    std::cin >> input;
    if (input == "x")
      break;
    auto it = vocab.find(input);
    if (it != vocab.end())
      std::cout << input << " in Korean is " << it->second << std::endl;
    else
      std::cout << "This word not in the list.\n";
  }

  return 0;
}
