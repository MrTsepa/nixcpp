#include <iostream>
#include <string>
#include <map>
#include <cmath>

using namespace std;

class CalculateableI {
public:
	string expr_str;
	virtual double calc() = 0;
};

class Operand : public CalculateableI {
public:
	virtual double calc() {
	}
};

class Bracket : public CalculateableI {
public:
	Operand *operand;
	double calc() {
		return operand->calc();
	}
};

class Operator : public CalculateableI {
public:
	Operand *operand_left, *operand_right;
	virtual double calc() = 0;
};

class OperatorAdd : public Operator {
public:
	double calc() {
		return operand_left->calc() + operand_right->calc();
	}
};

class OperatorSub : public Operator {
public:
	double calc() {
		return operand_left->calc() - operand_right->calc();
	}
};

class OperatorMult : public Operator {
public:
	double calc() {
		return operand_left->calc() * operand_right->calc();
	}
};

class OperatorDiv : public Operator {
public:
	double calc() {
		return operand_left->calc() / operand_right->calc();
	}
};

class OperatorPow : public Operator {
public:
	double calc() {
		return pow(operand_left->calc(), operand_right->calc());
	}
};

map<char, int> oper_prior;

double calc(string str) {
	size_t max_operator_pos = 0;
	int max_priority = 0;
	int right_bracket = 0;
	int right_digit = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '-' and str[i+1] >= '0' and str[i+1] <= '9')
			str[i] = '~';
		if (oper_prior[str[i]] != 0) {
			if (oper_prior[str[i]] > max_priority) {
				max_operator_pos = i;
				max_priority = oper_prior[str[i]];
				if (str[i] == '(') {
					int bracket_counter = 1;
					while(bracket_counter > 0) {
						i++;
						if (str[i] == '(')
							bracket_counter++;
						if (str[i] == ')')
							bracket_counter--;
					}
					right_bracket = i;
				}
				if (str[i] == '~') {
					while(true) {
						if (str[i] < '0' or str[i] > '9')
							break;
						i++;
					}
					right_digit = i;
					i--;
				}
			}
		}
	}
	if (max_priority == 0) {
		return stod(str);
	}
	else {
		if (str[max_operator_pos] != '(' and str[max_operator_pos] != '~') {
			string left = str.substr(0, max_operator_pos - 1);
			string right = str.substr(max_operator_pos + 2);
			if (str[max_operator_pos] == '+') {
				return calc(left) + calc(right);
			}
			if (str[max_operator_pos] == '*') {
				return calc(left) * calc(right);
			}
			if (str[max_operator_pos] == '/') {
				return calc(left) / calc(right);
			}
			if (str[max_operator_pos] == '^') {
				return pow(calc(left),calc(right));
			}
			if (str[max_operator_pos] == '-') {
				return calc(left) - calc(right);
			}
		}
		if (str[max_operator_pos] == '(') {
			return calc(str.substr(max_operator_pos + 1, right_bracket - max_operator_pos - 1));
		}
		if (str[max_operator_pos] == '~') {
			return -1 * stod(str.substr(max_operator_pos + 1, right_digit - max_operator_pos));
		}
	}
}

int main() {
	oper_prior['('] = 1;
	oper_prior['~'] = 2; // унарный минус
	oper_prior['^'] = 3;
	oper_prior['*'] = oper_prior['/'] = 4;
	oper_prior['+'] = oper_prior['-'] = 5;
	string expr_string;
	getline(cin, expr_string);
	cout << calc(expr_string);
}
