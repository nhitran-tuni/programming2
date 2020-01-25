#include <iostream>
using namespace std;

void mean ( int count_number)
{
  int i = 1;
  float sum = 0.0;

  while ( i < count_number + 1) {
    cout << "Input " << i << ". Number: ";
    float num;
    cin >> num;
    sum = sum + num;
    i ++;
  }
  if (count_number <= 0) {
      cout << "Cannot count mean value from 0 numbers" << endl;
  }
  else {
      cout << "Mean value of the given numbers is " << sum / count_number << endl;
  }
}
// Write here a function counting the mean value

int main()
{
    cout << "From how many integer numbers you want to count the mean value? ";

    int count_number;
    cin >> count_number;

    mean (count_number);
    return EXIT_SUCCESS;
}
