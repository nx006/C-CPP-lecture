#include "my_stack.hpp"
#include <iostream>

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    MyStack mStack(1);
    int n;
    cout << "스택에 삽입할 5개의 정수를 입력하라>> ";
    for (int i = 0; i < 5; i++)
    {
        cin >> n;
        mStack.push(n); // 스택에 푸시
    }
    cout << "스택 용량:" << mStack.capacity() << ", 스택 크기:" << mStack.length() << endl;
    cout << "스택의 모든 원소를 팝하여 출력한다>> ";
    while (mStack.length() > 0)
    {
        int k = mStack.pop();
        cout << k << ' '; // 스택에서 팝
    }
    cout << "\n스택 용량:" << mStack.capacity() << ", 스택 크기:" << mStack.length() << endl;
}
