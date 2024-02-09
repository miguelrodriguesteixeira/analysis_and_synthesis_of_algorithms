#include <cstdio>

int main () {
  char name[50];
  int age;
    
  printf("Enter your name: ");

  // get user input for name
  scanf("%s", name);

  printf("Enter your age: ");

  // get user input for age
  scanf("%d", &age);

  // print name and age
  printf("Hello %s, you are %d years old.", name, age);

  return 0;
}
