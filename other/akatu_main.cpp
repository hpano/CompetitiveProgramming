#include <iostream>
#include <string>
#include <deque>
using namespace std;

bool calc(deque<int> &stack, string ope) {
  if (ope == "+") {
    if (stack.size() >= 2) {
      int num1 = stack.front();
      stack.pop_front();
      int num2 = stack.front();
      stack.pop_front();

      int ans = num2 + num1;
      stack.push_front(ans);
    } else {
      return false;
    }
  } else if (ope == "-") {
    if (stack.size() >= 2) {
      int num1 = stack.front();
      stack.pop_front();
      int num2 = stack.front();
      stack.pop_front();

      int ans = num2 - num1;
      stack.push_front(ans);
    } else {
      return false;
    }
  } else if (ope == "*") {
    if (stack.size() >= 2) {
      int num1 = stack.front();
      stack.pop_front();
      int num2 = stack.front();
      stack.pop_front();

      int ans = num2 * num1;
      stack.push_front(ans);
    } else {
      return false;
    }
  } else if (ope == "++") {
    if (stack.size() >= 1) {
      int num1 = stack.front();
      stack.pop_front();

      int ans = num1 + 1;
      stack.push_front(ans);
    } else {
      return false;
    }
  } else if (ope == "@") {
    if (stack.size() >= 3) {
      int num1 = stack.front();
      stack.pop_front();
      int num2 = stack.front();
      stack.pop_front();
      int num3 = stack.front();
      stack.pop_front();

      int ans = num1 * num2 + num2 * num3 + num3 * num1;
      stack.push_front(ans);
    } else {
      return false;
    }
  } else {
    return false;
  }

  return true;
}

int main(int argc, char *argv[]) {
  deque<int> stack;
  string s;

  while (!cin.eof()) {
    cin >> s;
    try {
      int num = stoi(s);
      stack.push_front(num);
    } catch (const std::invalid_argument e) {
      if (s == "EOT") continue;
      if (!calc(stack, s)) {
        cout << "invalid" << endl;
        return 0;
      }
    }
  }

  if (stack.size() == 1) {
    cout << stack.front() << endl;
    stack.pop_front();
  } else {
    cout << "invalid" << endl;
  }

  return 0;
}