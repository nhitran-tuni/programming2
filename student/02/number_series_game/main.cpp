#include <iostream>

using namespace std;
int main()
{
    cout << "How many numbers would you like to have? ";
    int number;
    cin >> number;

    int i =1;

    while (i < number +1) {
        if (i % 3 == 0 && i % 7 == 0) {
        cout << "zip boing" << endl;
}       else if (i % 3 == 0) {
            cout << "zip" << endl;
}       else if (i % 7 == 0) {
            cout << "boing" << endl;
}       else {
            cout << i << endl;
}
        i ++;
}
    return 0;
}
