#include <iostream>
using namespace std;

float mean ( int count_number)
{
  int i = 1;
  int sum = 0;
  while ( i < count_number + 1) {
    cout << "Input " << i << ". Number: ";
    float num;
    cin >> num;
    sum = sum + num;
    i ++;
  }
  return sum;
}
// Write here a function counting the mean value

int main()
{
    cout << "From how many integer numbers you want to count the mean value? ";

    int count_number;
    cin >> count_number;

    if (count_number == 0) {
      cout << "Cannot count mean value from 0 numbers" << endl;
    }
    else {
      float sum = 0;
      sum = mean (count_number);
      cout << "Mean value of the given numbers is " << sum / count_number << endl;
    }
    return 0;
}
