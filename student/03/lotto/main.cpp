#include <iostream>

using namespace std;

unsigned long int factor( int x)
{
    unsigned long int i = x - 1;
    unsigned long int result = x;
    while (i != 0) {
        result *= i;
        i -= 1;
    }
    return result;
}

int main()
{
    unsigned long int ball, drawn;
    cout << "Enter the total number of lottery balls: ";
    cin >> ball;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn;

    if (ball <=0 || drawn <0) {
        cout << "The number of balls must be a positive number." << endl;
    }
    else {
        unsigned long int result1, result2, result3, result;
        result1 = factor(ball);
        result2 = factor(ball - drawn);
        result3 = factor(drawn);
        result = result1 / (result2 * result3);
        cout << "The probability of guessing all 4 balls correctly is 1/" << result << endl;
    }

    return 0;
}
