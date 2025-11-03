#include <iostream>

using namespace std;


class Stack {
	char arr[100];
	int top;

public:

	Stack() {
		top = -1;
	}

	void push(char c) {
		if(top < 99) {
			arr[++top] = c;
		}
	}

	void pop() {
		if(top >= 0) {
			top--;
		}
	}

	char peek() {
		if(top >= 0) {
			return arr[top];
		}
		return '\0';
	}

	bool isEmpty() {
		return top == -1;
	}

	string toString() {
		string s = "";
		for(int i = 0; i <= top; i++) s += arr[i];
		return s;
	}
};

int precedence(char op) {
	if(op == '+' || op == '-') {
		return 1;
	}

	if(op == '*' || op == '/') {
		return 2;
	}
	return 0;
}

int main() {
	string infix;
	cout << "Enter infix expression: ";
	cin >> infix;
	Stack s;
	string postfix;

	cout << left << "" << "Character" << "\t" << "Stack" << "\t" << "Postfix" << endl;

	for(char c : infix) {
		if(isalpha(c) || isdigit(c)) {
			postfix += c;
		}
		else if(c == '(') {
			s.push(c);
		}
		else if(c == ')') {
			while(!s.isEmpty() && s.peek() != '(') {
				postfix += s.peek();
				s.pop();
			}
			if(!s.isEmpty()) {
				s.pop();
			}
		}
		else {
			while(!s.isEmpty() && precedence(s.peek()) >= precedence(c)) {
				postfix += s.peek();
				s.pop();
			}
			s.push(c);
		}
		cout << left << "   " << c << "\t\t" << s.toString() << "\t" << postfix << endl;
	}

	while(!s.isEmpty()) {
		postfix += s.peek();
		s.pop();
		cout << left << "   " << "\t\t" << s.toString() << "\t" << postfix << endl;
	}

	cout << "\nPostfix Expression: " << postfix << endl;
}
