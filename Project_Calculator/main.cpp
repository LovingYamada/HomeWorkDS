#include "expression_evaluator.h"

int main() {
    int c = 1;
    cout << "Please select a mode:" << endl;
    cout << "1. Test mode" << endl;
    cout << "2. Interactive mode" << endl;
    cin >> c;
    cin.ignore();
    if(c == 1) runTests();
    else if(c == 2){
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
    } catch (const std::exception& e) {
        cout << "ILLEGAL" << endl;
    }
    }
    } else cout << "Invalid input" << endl;
    return 0;
}
