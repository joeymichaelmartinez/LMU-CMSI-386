/*
   "It is better to feel good than to feel bad." --Dr. Ray Toal November 2017
   Written by: John Hardy and Jordan Sanders
*/

#include "queue.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <array>
using namespace std;

void test_output_stream() {
  Queue<string> s;
  s.enqueue("Output");
  s.enqueue("stream");
  s.enqueue("test");
  s.enqueue("passed!");
  stringstream strs;
  strs << s;
  assert(strs.str() == "Output stream test passed!");
}

void test_no_copies() {
  Queue<int> p;
  Queue<int> q;
  // No way to test this at run time, but uncomment the following lines
  // and look for compile time errors.
  // p = q;
  // Queue<int> r(p);
}

Queue<int> one_two_three() {
  Queue<int> q;
  for (int i = 1; i <= 3; i++) q.enqueue(i);
  return q;
}

void test_moves() {
  // Assignment of a temporary is a move
  Queue<int> p = Queue<int>();

  // Construction via a function return call is a move
  Queue<int> q = one_two_three();
  assert(q.get_size() == 3);
  assert(q.dequeue() == 1);

  // Test move assignment
  q = one_two_three();
  assert(q.get_size() == 3);
  assert(q.dequeue() == 1);
}

void test_string() {
  Queue<string> test;

  assert(test.get_end_node() == nullptr);
  assert(test.get_start_node() == nullptr);
  assert(test.get_size() == 0);

  test.enqueue("Why ");

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 1);
  assert(test.get_start_node()->get_data() == "Why ");
  assert(test.get_end_node()->get_data() == "Why ");

  test.enqueue("is ");
  test.enqueue("this ");
  test.enqueue("so ");
  test.enqueue("hard?");

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 5);
  assert(test.get_start_node()->get_data() == "Why ");
  assert(test.get_end_node()->get_data() == "hard?");

  test.dequeue();

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 4);
  assert(test.get_start_node()->get_data() == "is ");
  assert(test.get_end_node()->get_data() == "hard?");

  test.dequeue();
  test.dequeue();
  test.dequeue();

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 1);
  assert(test.get_start_node()->get_data() == "hard?");
  assert(test.get_end_node()->get_data() == "hard?");

  test.dequeue();

  assert(test.get_end_node() == nullptr);
  assert(test.get_start_node() == nullptr);
  assert(test.get_size() == 0);

  try {
    test.dequeue();
    assert(false);
  } catch (const underflow_error& ue) {
    assert(true);
  } catch (...) {
    std::cout << "Does not throw an error when I dequeue from an empty string Queue." << '\n';
    assert(false);
  }
}

void test_int() {
  Queue<int> test;

  assert(test.get_end_node() == nullptr);
  assert(test.get_start_node() == nullptr);
  assert(test.get_size() == 0);

  test.enqueue(1);

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 1);
  assert(test.get_start_node()->get_data() == 1);
  assert(test.get_end_node()->get_data() == 1);

  test.enqueue(2);
  test.enqueue(3);
  test.enqueue(4);
  test.enqueue(5);

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 5);
  assert(test.get_start_node()->get_data() == 1);

  test.dequeue();

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 4);
  assert(test.get_start_node()->get_data() == 2);
  assert(test.get_end_node()->get_data() == 5);

  test.dequeue();
  test.dequeue();
  test.dequeue();

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 1);
  assert(test.get_start_node()->get_data() == 5);
  assert(test.get_end_node()->get_data() == 5);

  test.dequeue();

  assert(test.get_end_node() == nullptr);
  assert(test.get_start_node() == nullptr);
  assert(test.get_size() == 0);

  try {
    test.dequeue();
    assert(false);
  } catch (const underflow_error& ue) {
    assert(true);
  } catch (...) {
    std::cout << "Does not throw an error when I dequeue from an empty int Queue." << '\n';
    assert(false);
  }
}

void test_vector() {
  Queue<vector<bool>> test;

  assert(test.get_end_node() == nullptr);
  assert(test.get_start_node() == nullptr);
  assert(test.get_size() == 0);

  test.enqueue({true});

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 1);
  assert(test.get_start_node()->get_data() == vector<bool>{true});
  assert(test.get_end_node()->get_data() == vector<bool>{true});

  test.enqueue({});
  test.enqueue({true});
  test.enqueue({false, true});
  test.enqueue({false, false});

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 5);
  assert(test.get_start_node()->get_data() == vector<bool>{true});
  assert(test.get_end_node()->get_data() == (vector<bool>{false, false}));

  test.dequeue();

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 4);
  assert(test.get_start_node()->get_data() == vector<bool>{});
  assert(test.get_end_node()->get_data() == (vector<bool>{false, false}));

  test.dequeue();
  test.dequeue();
  test.dequeue();

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 1);
  assert(test.get_start_node()->get_data() == (vector<bool>{false, false}));
  assert(test.get_end_node()->get_data() == (vector<bool>{false, false}));

  test.dequeue();

  assert(test.get_end_node() == nullptr);
  assert(test.get_start_node() == nullptr);
  assert(test.get_size() == 0);

  try {
    test.dequeue();
    assert(false);
  } catch (const underflow_error& ue) {
    assert(true);
  } catch (...) {
    std::cout << "Does not throw an error when I dequeue from an empty vector Queue." << '\n';
    assert(false);
  }
}

void test_array() {
  Queue<array<int, 1>> test;

  assert(test.get_end_node() == nullptr);
  assert(test.get_start_node() == nullptr);
  assert(test.get_size() == 0);

  test.enqueue({1});

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 1);
  assert(test.get_start_node()->get_data() == (array<int, 1>{1}));
  assert(test.get_end_node()->get_data() == (array<int, 1>{1}));

  test.enqueue({});
  test.enqueue({3});
  test.enqueue({4});
  test.enqueue({5});

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 5);
  assert(test.get_start_node()->get_data() == (array<int, 1>{1}));
  assert(test.get_end_node()->get_data() == (array<int, 1>{5}));

  test.dequeue();

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 4);
  assert(test.get_start_node()->get_data() == (array<int, 1>{}));
  assert(test.get_end_node()->get_data() == (array<int, 1>{5}));

  test.dequeue();
  test.dequeue();
  test.dequeue();

  assert(test.get_end_node() != nullptr);
  assert(test.get_start_node() != nullptr);
  assert(test.get_size() == 1);
  assert(test.get_start_node()->get_data() == (array<int, 1>{5}));
  assert(test.get_end_node()->get_data() == (array<int, 1>{5}));

  test.dequeue();

  assert(test.get_end_node() == nullptr);
  assert(test.get_start_node() == nullptr);
  assert(test.get_size() == 0);

  try {
    test.dequeue();
    assert(false);
  } catch (const underflow_error& ue) {
    assert(true);
  } catch (...) {
    std::cout << "Does not throw an error when I dequeue from an empty array Queue." << '\n';
    assert(false);
  }
}

int main() {
  test_output_stream();
  test_no_copies();
  test_moves();
  test_string();
  test_int();
  test_vector();
  test_array();

  std::cout << "All tests passed!" << '\n';
}
