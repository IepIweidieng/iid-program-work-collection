#include<iostream>
#include"stack.h"
using namespace std;

int main(){
  stack s(3);

  s.push(1);
  s.show();
  s.push(2);
  s.show();
  s.push(3);
  s.show();
  s.push(4);
  s.show();
  cout << s.top() << endl;
  s.pop();
  s.show();
  cout << s.top() << endl;
  s.pop();
  s.show();
  s.push(5);
  s.show();
  cout << s.top() << endl;
  s.pop();
  s.show();
  cout << s.top() << endl;
  s.pop();
  s.show();
  cout << s.top() << endl;
  s.pop();
  s.show();
  return 0;
}
