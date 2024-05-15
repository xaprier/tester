#include "test.hpp"
#include <stdexcept>

void exampleTestFunction() {
  int result = 2 + 2;
  if (result != 4) {
    throw std::runtime_error("Result is not 4!");
  }
}

int main(int argc, char *argv[]) {
  Tester tester;

  // add tests
  tester.addTest("Example Test", exampleTestFunction);

  // add test case
  tester.addTestCase("expected", "excepted");

  // tests will gonna run on destructor of object.
  return 0;
}