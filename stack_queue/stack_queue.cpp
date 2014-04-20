#include <stack>
#include <queue>
#include <iostream>

using namespace std;
int main(void){
	
	stack<int> stk;
	stk.push(100);
	stk.push(200);
	cout << stk.top() << endl;
	stk.pop();
	cout << stk.top() << endl;
	stk.pop();

	queue<int> que;
	que.push(100);
	que.push(200);
	cout << que.front() << endl;
	que.pop();
	cout << que.front() << endl;


	return 0;
}