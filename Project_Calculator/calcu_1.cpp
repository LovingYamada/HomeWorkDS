#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

// 判断字符是否是运算符
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 判断字符是否是数字或小数点
bool isNumber(char c) {
    return isdigit(c) || c == '.';
}

// 判断字符是否是左括号
bool isLeftParenthesis(char c) {
    return c == '(';
}

// 判断字符是否是右括号
bool isRightParenthesis(char c) {
    return c == ')';
}

// 判断运算符优先级
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 执行基本运算
double applyOperator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) throw runtime_error("division by zero");
            return a / b;
        default: return 0;
    }
}

// 检查表达式是否合法
bool isValidExpression(const string& expr) {
    if (expr.empty()) return false;
    if ((isOperator(expr[0]) && expr[0] != '-') || isOperator(expr.back())) return false;
    if (expr.back() == 'e') return false;

    int openParenCount = 0;
    for (size_t i = 0; i < expr.size(); ++i) {
        if (isLeftParenthesis(expr[i])) openParenCount++;
        if (isRightParenthesis(expr[i])) openParenCount--;
        if (openParenCount < 0) return false; // 右括号超过左括号
        if (isLeftParenthesis(expr[i]) && isRightParenthesis(expr[i+1])) return false; // ()不合法
        if (isOperator(expr[i])) {
            if ((i == 0 && isOperator(expr[1])) || (i > 0 && expr[i-1] == '(' && isOperator(expr[i+1]))) return false; // --1+1 不合法 (--1) (+-1)不合法
            if (i > 0 && isOperator(expr[i-1]) && expr[i] != '-') return false; // 1++1不合法 这里不会出现首二个都是运算符的情况
            if (i > 1 && isOperator(expr[i-1]) && isOperator(expr[i-2])) return false; // 1---1不合法
            if (i > 0 && expr[i] != '-' && expr[i-1] == '(') return false; // (+1)不合法
            if (i > 0 && expr[i-1] == '(' && expr[i+1] == ')') return false; // (-)不合法
        }
        if (expr[i] == ' ') return false; // 不允许空格
    }
    return openParenCount == 0;
}

double StringToNumber(const std::string& expr, size_t& i) {
    std::string num = "";
    int dotCount = 0; // 用于记录小数点数量
    int eCount = 0;
    if (expr[i] == '-') {
        num += expr[i++];
    }
    while (i < expr.size() && (isdigit(expr[i]) || expr[i] == '.' || expr[i] == 'e' || expr[i] == 'E')
           || (expr[i] == '-' && (expr[i-1] == 'e' || expr[i-1] == 'E'))) {
        if (expr[i] == '.') {
            if (++dotCount > 1) {
                throw std::invalid_argument("Invalid number format: more than one decimal point.");
            }
        }
        if (expr[i] == 'e' || expr[i] == 'E') {
            if (++eCount > 1) {
                throw std::invalid_argument("Invalid number format: more than one exponent.");
            }
        }
        num += expr[i++];
    }
    try {
        return std::stod(num); // 转换为 double
    } catch (const std::exception& e) {
        throw std::invalid_argument("Invalid number format: " + num);
    }
}

// 计算中缀表达式
double evaluateExpression(const string& expr) {
    stack<double> values; // 存储操作数
    stack<char> operators; // 存储运算符

    size_t i = 0;
    while (i < expr.size()) {
        if (isspace(expr[i])) {
            i++;
            continue;
        }
        
        if (isNumber(expr[i])) {
            // 解析数字
            try {
            double value_ = StringToNumber(expr, i);
            values.push(value_);
            } catch (const std::invalid_argument& e) {
                throw std::invalid_argument("Invalid number format");
            }
        } 
        else if (expr[i] == '-' && (i == 0 || expr[i-1] == '(')){
            try{
            double value_ = StringToNumber(expr, i);
            values.push(value_);
            } catch (const std::invalid_argument& e) {
                throw std::invalid_argument("Invalid number format");
            }
        }
        else if(i > 0 && expr[i] == '-' && isOperator(expr[i-1])){
            // 处理负数
            try {
            double value_ = StringToNumber(expr, i);
            values.push(value_);
            } catch (const std::invalid_argument& e) {
                throw std::invalid_argument("Invalid number format");
            }
        }
        else if (isLeftParenthesis(expr[i])) {
            operators.push(expr[i]);
            i++;
        } 
        else if (isRightParenthesis(expr[i])) {
            // 处理右括号，计算括号内的表达式
            while (!operators.empty() && operators.top() != '(') {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperator(a, b, op));
            }
            if (!operators.empty()) operators.pop(); // 弹出左括号
            i++;
        } 
        else if (isOperator(expr[i])) {
            // 处理运算符
            while (!operators.empty() && precedence(operators.top()) >= precedence(expr[i])) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(applyOperator(a, b, op));
            }
            operators.push(expr[i]);
            i++;
        } 
        else {
            throw runtime_error("Invalid character in the expression.");
        }
    }

    // 处理剩余的运算符
    while (!operators.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        values.push(applyOperator(a, b, op));
    }

    return values.top();
}

int main() {
    int n = 1;
    while (n){
    string expr;
    cout << "Enter a mathematical expression to evaluate, or type 's' to exit" << endl
         << "Do NOT use spaces in the expression." << endl;
    getline(cin, expr);

    if (expr == "s") {break;}
    if (!isValidExpression(expr)) {
        cout << "ILLEGAL" << endl;
        continue;
    }

    try {
        double result = evaluateExpression(expr);
        // 输出结果，保留 5 位小数
        if(result == 0) printf("0.00000\n");
        else printf("%.5f\n", result);
    } catch (const runtime_error& e) {
        cout << "ILLEGAL" << endl;
    } catch (const invalid_argument& e) {
        cout << "ILLEGAL" << endl;
    }

    }
    return 0;
}
