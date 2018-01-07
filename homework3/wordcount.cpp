/*
   "It is better to feel good than to feel bad." --Dr. Ray Toal November 2017
   Written by: John Hardy and Jordan Sanders
*/

#include <iostream>
#include <cassert>
using namespace std;

string remove_nonletters(const string& input) {
  string result = input;
  for (int i = 0; i < (signed int)result.length(); i++) {
    result[i] = tolower(result[i]);
    if (!isalpha(result[i])) {
      if (i == 0 || (i > 0 && isspace(result[i - 1]))) {
        result.replace(i, 1, "");
        i = (i == 0) ? -1 : i - 1;
      } else {
        result.replace(i, 1, " ");
      }
    }
  }
  if (result.length() > 0 && !isspace(result[result.length() - 1])) {
    result.append(" ");
  }
  return result;
}

string group_similar_words(string input) {
  string result;
  int currentWordPosition = 0;

  for (unsigned int i = 0; i < input.length(); i++) {
    if (isspace(input[i])) {
      int numberOfWords = 1;
      int repeatFinderPosition = i + 1;
      string currentWord = input.substr(currentWordPosition, i - currentWordPosition + 1);

      for (unsigned int j = i + 1; j < input.length(); j++) {
        if (isspace(input[j])) {
          if (input.substr(repeatFinderPosition, j - repeatFinderPosition + 1) == currentWord) {
            numberOfWords++;
            input.erase(repeatFinderPosition, j - repeatFinderPosition + 1);
            j = repeatFinderPosition - 1;
          } else {
            repeatFinderPosition = j + 1;
          }
        }
      }
      result += currentWord + to_string(numberOfWords);
      currentWordPosition = i + 1;
    }
  }
  return result;
}

string sort_words_large_to_small(string& input) {
  string result;

  while (input != "") {
    int pivot = 0;
    int largest = 0;
    string largestWord;
    int largestPosition = 0;
    int largestSize = 0;

    for (unsigned int i = 0; i < input.length(); i++) {
      char currentLetter = input[i];

      if (!isalpha(currentLetter) && !isspace(currentLetter)) {
        if (stoi(to_string(currentLetter)) > largest) {
          largest = stoi(to_string(currentLetter));
          largestWord = input.substr(pivot, i - pivot + 1);
          largestPosition = pivot;
          largestSize = i - pivot + 1;
        }
        pivot = i + 1;
      }
    }
    input.erase(largestPosition, largestSize);
    result += largestWord + "\n";
  }
  return result;
}

string wordcount(const string& input) {
  string result = input;
  result = remove_nonletters(result);
  result = group_similar_words(result);
  result = sort_words_large_to_small(result);
  return result;
}

int main() {
  string general_test = "The tests, my lord,have failed! FAILED have   the   tests,   they   have.";
  string test_caps = "   Hello Hello hello HeLlO hELlo   ";
  string test_letter = "G";
  string test_word = "GiT";
  string test_nothing = "";
  string test_space = " ";
  string test_spaces = "   ";
  string test_nonletters = ";:&^$#@!'. .'&*()(*&%%^^){}[{]|,|||}]";
  string test_complex = "(((((((($$$sNEAky$$$))))))))";
  string test_a_couple = "!!!THIS_IS_NOT_A_COUPLE!!!!-*lol_jk*";
  string test_emojis = "😄🍰😞yay!emojis!🐷👩";
  string test_weird = "в聲字вwtfЖ_ЛareЙ_字яtheseЮ_пфthings形?";
  string test_numbers = "4This5is6a5numbers3test2test";

  bool failed = false;
  try {
    assert(wordcount(general_test) == "have 3\nthe 2\ntests 2\nfailed 2\nmy 1\nlord 1\nthey 1\n");
    assert(wordcount(test_caps) == "hello 5\n");
    assert(wordcount(test_letter) == "g 1\n");
    assert(wordcount(test_word) == "git 1\n");
    assert(wordcount(test_nothing) == "");
    assert(wordcount(test_space) == "");
    assert(wordcount(test_spaces) == "");
    assert(wordcount(test_nonletters) == "");
    assert(wordcount(test_complex) == "sneaky 1\n");
    assert(wordcount(test_a_couple) == "this 1\nis 1\nnot 1\na 1\ncouple 1\nlol 1\njk 1\n");
    assert(wordcount(test_emojis) == "yay 1\nemojis 1\n");
    assert(wordcount(test_weird) == "wtf 1\nare 1\nthese 1\nthings 1\n");
    assert(wordcount(test_numbers) == "test 2\nthis 1\nis 1\na 1\nnumbers 1\n");
  } catch (exception &e) {
    cout << e.what() << "\n";
    failed = true;
  }
  if (failed) {
    std::cout << "There was an error!" << '\n';
  } else {
    std::cout << "All tests passed!\n";
  }
}
