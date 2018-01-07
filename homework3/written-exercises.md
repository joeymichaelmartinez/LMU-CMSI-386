>   "It is better to feel good than to feel bad." --Dr. Ray Toal November 2017
   Answered by: John Hardy and Jordan Sanders

### 1. (5 pts) Given the C++ declaration:
```c++
struct {
  int n;
  char c;
} A[10][10];
```
On your machine, find the address of A[0][0] and A[3][7]. Explain why these values are what you found them to be.

> It seems that the addresses grow in increments of 8. My assumption here is that even though the size of an int is larger than a char, the data must remain aligned inside memory, so the char is given the same amount of space as the int. This explains why everything is stored in  increments of 8. This means we could stuff an int and 4 chars into our struct (in that order) and we would still see the same amount of memory allocated since the computer tries to conserve memory whenever possible.

### 2. (5 pts) Explain the meaning of the following C++ declarations:
```c++
double *a[n];
double (*b)[n];
double (*c[n])();
double (*d())[n];
```
> The first declaration is an array of pointers to doubles, with the double n being accessed. The second is a pointer to an array of doubles, with the value n being accessed from the array. The third declaration is a pointer to an array of functions that return a double, with the function n being accessed and then called. The last declaration is a pointer to a function, which is then called. This returns an array of doubles, with the double n being accessed from the array.

### 3. (5 pts) Consider the following declaration in C++:
```c++
double (*f(double (*)(double, double[]), double)) (double, ...);
```
Describe rigorously, in English, the type of f.

> The best way to answer this question is to start on the outside an peel away the layers. We know for a fact that what must be returned from all of this is a double. On the far right we see what looks like a set of arguments being supplied to a function so the first set of parenthesis must be a function that accepts a double and then an arbitrary number of arguments afterwards. Inside the first group of parenthesis, we see what looks like a pointer to a function. This function accepts a pointer to another function and a double as its arguments. This final innermost function accepts a double, and an array of doubles, returning a double. To summarize, f is a pointer to a function with two doubles as it arguments, returning yet another function after being called.

### 4. (5 pts) What happens when we “redefine” a field in a C++ subclass? For example, suppose we have:
```c++
class Base {
public:
  int a;
  std::string b;
};

class Derived: public Base {
public:
  float c;
  int b;
};
```
Does the representation of a Derived object contain one b field or two? If two, are both accessible, or only one? Under what circumstances? Tell the story of how things are.
> Only one field is accessible, and that is the b field defined by the Derived object. In C++, whenever you inherit information from a parent class, if you change the parent classes fields, then the changes you made OVERWRITE the parent classes fields. This is to avoid confusion between multiple fields.

### 5. (5 pts) What does the following C++ program output?
```c++
#include <iostream>
int x = 2;
void f() {
  std::cout << x << '\n';
}
void g() {
  int x = 5;
  f();
  std::cout << x << '\n';
}
int main() {
  g();
  std::cout << x << '\n';
}
```
Verify that the answer you obtained is the same that would be inferred from applying the rules of static scoping. If C++ used dynamic scoping, what would the output have been?
> Just as I had predicted, the output was 2, 5, 2 since f only references the GLOBAL (to the class) x, not the local x in g(). Ditto for the main() function. If C++ used dynamic scoping, then the output would have been 5, 5, 2 since f() would have accessed the local x dynamically, once we leave the scope of g(), the main() function then accesses the global x.

### 6. (5 pts) Suppose you were asked to write a function to scramble (shuffle) a given array, in a mutable fashion. Give the function signature for a shuffle function for (a) a raw array, and (b) a std::array.
> (a) void scramble(int arr[n]) {//no need to include a reference
        ...
      }

> (b) void shuffle(array<int, n>& arr) {//reference required
        ...
      }
