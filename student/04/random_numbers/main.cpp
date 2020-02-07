#include <iostream>
#include <random>
#include <string>
#include <ctime>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    // Implement your function here
    string seed, command;
    cout<< "Enter a seed value or an empty line: " <<endl;
    getline(cin, seed);
    cout << "" <<endl;
    if (seed == "") {
        default_random_engine number(time(0));
        uniform_int_distribution<int> randomNumber(lower, upper);

        cout << "Your drawn random number is " << randomNumber(number) << endl;
        cout << "Press enter to continue or q to quit: ";
        getline(cin,command);
        cout << "" <<endl;

        while (command != "q"){
            cout << "Your drawn random number is " << randomNumber(number) << endl;
            cout << "Press enter to continue or q to quit: ";
            getline(cin,command);
            cout <<""<< endl;
        }
    }
    else
    {
        default_random_engine number(stoi(seed));
        uniform_int_distribution<int> randomNumber(lower, upper);

        cout << "Your drawn random number is " << randomNumber(number) << endl;
        cout << "Press enter to continue or q to quit: ";
        getline(cin,command);
        cout << "" <<endl;

        while (command != "q"){
            cout << "Your drawn random number is " << randomNumber(number) << endl;
            cout << "Press enter to continue or q to quit: ";
            getline(cin,command);
            cout <<""<< endl;
        }
    }
}
int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    // Reading the line feed, which was left unread by >> operator above.
    // This is necessary since the seed value will be read by getline
    // in the function produce_random_numbers.
    string line_feed = "";
    getline(cin, line_feed);

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound" << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
