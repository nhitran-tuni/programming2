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
    Instance(Course *cour, std::string instance_name, const Date& start_date);

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

    /**
     * @brief sign_up_student
     * @param new_student sign up
     * add student to course implement
     * print error if student has already signed up for course implement
     * print error if student has not been in instance but sign up after
     * starting date of course implement
     * @param sign_up_date the date student signed up
     * @return true if student had not been in the courese implement yet
     * and student signed up in time (same date or before the starting date
     * of course implement), false otherwise
     */
    bool sign_up_student(Account* new_student, const Date& sign_up_date);

    /**
     * @brief get_course
     * @return course having instance
     * @note the existence of both course and instance checked before,
     * thus course existence does not needed to be checked.
     */
    Course *get_course();

    /**
     * @brief complete_student
     * @param complete_stud
     * remove the account completing instance
     */
    void complete_student(Account* complete_stud);

    /**
     * @brief print_current_course
     * print course information student current studying in one line
     * including instance
     */
    void print_current_course();

private:
    // pointer to course instance belongs to
    Course* cour_;
    // name of instance
    std::string instance_name_;

    // contain all signups
    std::vector<Account*> signup_account_;

    // Date instances added
    const Date start_date_;
};

#endif // INSTANCE_HH
