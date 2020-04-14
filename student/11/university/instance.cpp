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

Instance::~Instance()
{

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

bool Instance::is_named(std::string name)
{
    return ( instance_name_ == name );
}

