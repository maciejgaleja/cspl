#include <iostream>

#include <hunspell.hxx>

void check_word(Hunspell& hs, const std::string& word) {
  bool ok = hs.spell(word.c_str());
  if (ok) {
    std::cout << word << "\n";
  } else {
    auto alternatives = hs.suggest(word);
    for (const auto& s : alternatives) {
      std::cout << word << " -> " << s << "\n";
    }
  }
}

int main(int argc, char** argv) {
  std::cout << "cspl\n";
  Hunspell hs("C:\\Hunspell\\en_US.aff", "C:\\Hunspell\\en_US.dic");

  std::string word = "waitign";
  check_word(hs, word);
}