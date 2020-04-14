/* Class: Instance
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represent a single instance.
 *
 * Program author
 * Name: Thuy Phuong Nhi Tran
 * Student number: 291937
 * UserID: mpthtr
 * E-Mail: thuyphuongnhi.tran@tuni.fi
 *
 * Note: Define course instances in the university system.
 *
 * Note: Students should make changes to this class, and add their info and
 * specifics of the class to this comment.
 * */
#ifndef INSTANCE_HH
#define INSTANCE_HH

#include "account.hh"
#include "date.hh"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

// Forward-declaration of Course, so that instance can point to the course it belongs to.
class Course;

const std::string ALREADY_REGISTERED = "Error: Student has already registered on this course.";
const std::string LATE = "Error: Can't sign up on instance after the starting date.";
const std::string INDENT = "    ";

class Instance
{
public:
    /**
     * @brief Instance constructor
     * @param cour - pointer to the course instance bbelongs to
     * @param instance_name
     * @param start_date
     */
    Instance(Course *cour, std::string instance_name, Date start_date);

    // destructor
    ~Instance();

    /**
     * @brief print
     * print starting date, date course added, and number of students signed up
     */
    void print();

    /**
     * @brief print_students
     * print all the signups information in each line
     */
    void print_students();

    /**
     * @brief is_named
     * @param name
     * check if the the course has instance named the same as given name
     * @return true if the instance name is the same as given name,
     * false otherwise
     */
    bool is_named(std::string name);
private:
    // pointer to course instance belongs to
    Course* cour_;
    // name of instance
    std::string instance_name_;

    // contain all signups
    std::vector<Account*> signup_account_;

    // Date instances added
    Date start_date_;
};

#endif // INSTANCE_HH
