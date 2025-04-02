#include <fstream>
#include <iostream>
#include <map>
#include <string>

int main(int argc, char *argv[]) {
  std::ifstream word_file("교육부지정_고등영단어2200.csv");
  if (!word_file) {
    std::cout << "Faile to open\n";
  }
  std::string words, input;
  int pos, length;
  std::map<std::string, std::string> vocab;
  while (getline(word_file, words)) {
    pos = words.find(",");
    length = words.length();
    vocab.insert({words.substr(0, pos), words.substr(pos + 1, length)});
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

  word_file.close();

  // std::map<std::string, std::string> vocab;
  // std::string eng, kor, input;
  // for (int i = 0; i < 10; i++) {
  //   std::cout << "Enter one word in two languages: (ENG KOR) ";
  //   std::cin >> eng >> kor;
  //   // vocab.insert({eng, kor});
  //   vocab[eng] = kor;
  // }
  //
  // while (1) {
  //   std::cout << "Enter an English word: (x for exit) ";
  //   std::cin >> input;
  //   if (input == "x")
  //     break;
  //   auto it = vocab.find(input);
  //   if (it != vocab.end())
  //     std::cout << input << " in Korean is " << it->second << std::endl;
  //   else
  //     std::cout << "This word not in the list.\n";
  // }

  return 0;
}
