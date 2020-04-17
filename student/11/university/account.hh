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

    /**
     * @brief complete_instance
     * @param complete_inst
     * remove the instance that account complete in current study
     * add course to completed course
     * print error if account did not sign up for instance
     * @return false if account did not sign up for instance of course,
     *         true otherwise
     */
    bool complete_instance(Instance *complete_inst);

    /**
     * @brief print_study_state
     * prints curent course instance(s) account signed up,
     * course account completed and credits account gained
     */
    void print_study_state();

    /**
     * @brief print_complete_course
     * print all complete course(s) and credits of student
     */
    void print_complete_course();

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
