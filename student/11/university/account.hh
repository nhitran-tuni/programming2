/* Class: Account
  * ----------
  * Defines a student or a staff account in the university system.
  *
  * Program author
  * Name: Thuy Phuong Nhi Tran
  * Student number: 291937
  * UserID: mpthtr
  * E-Mail: thuyphuongnhi.tran@tuni.fi
  *
  * In the project, this class should be expanded to
  * include study history of the account.
  * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include "date.hh"
#include <string>
#include <vector>
#include <map>
#include <iostream>

class Instance;
class Course;

const std::string NO_SIGNUPS = "No signups found on this instance.";
const std::string SIGNED_UP = "Signed up on the course instance.";
const std::string COMPLETED = "Course completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "frontname lastname"
     * @param email
     * @param account_number
     */
    Account(std::string full_name, std::string email, int account_number);

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email();

    /**
     * @brief add_instance
     * @param new_instance to be added
     * add instance that account had sign up for
     * print message that account successfully signed up
     */
    void add_instance(Instance *new_instance);

private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    // number of credits of student
    int credit_;
    const int account_number_;
    std::vector<Instance*> current_;
    std::vector<Course*> completed_;
};

#endif // ACCOUNT_HH
