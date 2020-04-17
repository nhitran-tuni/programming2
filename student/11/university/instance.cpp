/* University project
 *
 * Class: Instance
 *
 * Program author
 * Name: Thuy Phuong Nhi Tran
 * Student number: 291937
 * UserID: mpthtr
 * E-Mail: thuyphuongnhi.tran@tuni.fi
 *
 * Notes: add implements to all exist functions corresponding  to instance
 *
 * */
#include "instance.hh"
#include "course.hh"

Instance::Instance(Course *cour, std::string instance_name, Date start_date):
    cour_(cour),
    instance_name_(instance_name),
    start_date_(start_date)
{

}

bool Instance::is_named(std::string name)
{
    return ( instance_name_ == name );
}

void Instance::print()
{
    std::cout << instance_name_ << std::endl;

    std::cout << INDENT << "Starting date: ";
    start_date_.print();
    std::cout << std::endl;

    std::cout << INDENT << "Amount of students: "
              << signup_account_.size() << std::endl;
}

void Instance::print_students()
{
    for ( Account* acc : signup_account_ ){
        acc->print();
    }
}

bool Instance::sign_up_student(Account *new_student, const Date &sign_up_date)
{
    /** checking if the student has already been in course implement first
     * if true print error and return
    */
    for ( Account* acc : signup_account_ ){
        if ( acc == new_student ){
            std::cout << ALREADY_REGISTERED << std::endl;
            return false;
        }
    }
    /** continue check if student signed in time
     * if true print error and return
     * if false add student to course implement
    */
    if ( start_date_ < sign_up_date ){
        std::cout << LATE << std::endl;
        return false;
    }

    signup_account_.push_back(new_student);

    return true;
}

Course *Instance::get_course()
{
    return cour_;
}

void Instance::complete_student(Account *complete_stud)
{
    std::vector<Account*>::iterator iter = std::find(signup_account_.begin(),
                                                     signup_account_.end(),
                                                     complete_stud);
    signup_account_.erase(iter);
}

void Instance::print_current_course()
{
    // parameter false for printing instance in line with course information
    cour_->print_info(false);
    std::cout << " " << instance_name_ << std::endl;
}
