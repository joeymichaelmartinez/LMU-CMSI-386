/*
   "It is better to feel good than to feel bad." --Dr. Ray Toal November 2017
   Written by: John Hardy and Jordan Sanders
*/

#include <iostream>
#include <cassert>
using namespace std;

struct Sayer {
private:
  string current_words = "";
public:
  explicit Sayer (const string& word): current_words(word) {}

  Sayer operator() (const string& next_word) {
    current_words += " " + next_word;
    return Sayer(current_words);
  }

  string operator() () {
    return current_words;
  }

};

Sayer say(const string& start_word) {
  return Sayer(start_word);
}

string say() {
  return "";
}

int main() {
  assert (say() == "");
  assert (say("")() == "");
  assert (say("hi")() == "hi");
  assert (say("hi")("there")() == "hi there");
  assert (say("hello")("my")("name")("is")("Colette")() == "hello my name is Colette");
  assert (say("😄")("🍰")("😞")("🐷")("👩")() == "😄 🍰 😞 🐷 👩");
  assert (say("в聲字в")("Ж_Л")("Ю_пф")() == "в聲字в Ж_Л Ю_пф");

  std::cout << "All tests passed!" << "\n";
}
