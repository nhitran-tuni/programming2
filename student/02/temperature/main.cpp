#include <iostream>

using namespace std;

int main()
{
    float temperature;
    cout << "Enter a temperature: ";
    cin >> temperature;

    cout << temperature << " degrees Celsius is " << 1.8 * temperature + 32 << " degrees Fahrenheit" << "\n";
    cout << temperature << " degrees Fahrenheit is " << (temperature - 32)/1.8 << " degrees Celsius" << endl;

    return 0;
}
