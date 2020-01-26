#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cout << "Enter a number: ";

    int base;
    cin >> base;

    int exponent = 3;
    int result = pow(base, exponent);

    if (result > 0) {
      cout << "The cube of " << base << " is " << result << "." << endl;
    }
    else {
      cout << "Error! The cube of " << base << " is not " << result << "." << endl;
    }

    return 0;
}
