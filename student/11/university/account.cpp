/* Class: Account
  * ----------
  *  Adds implemments to defined functions
  *
  * Program author
  * Name: Thuy Phuong Nhi Tran
  * Student number: 291937
  * UserID: mpthtr
  * E-Mail: thuyphuongnhi.tran@tuni.fi
  *
  * */
#include "account.hh"
#include "utils.hh"
#include "instance.hh"
#include "course.hh"

Account::Account(std::string full_name, std::string email, int account_number):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    email_(email),
    credit_(0),
    account_number_(account_number)
{
    std::vector<std::string> name = utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();
}

void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email()
{
    return email_;
}

void Account::add_instance(Instance *new_instance)
{
    current_.push_back(new_instance);
    std::cout << SIGNED_UP << std::endl;
}

void Account::complete_instance(Instance *complete_inst)
{
    /** find if student signed up for instance
     *  if not print error and return false
     */
    std::vector<Instance*>::iterator iter = std::find(current_.begin(),
                                                      current_.end(),
                                                      complete_inst);
    if ( iter == current_.end() ){
        std::cout << NO_SIGNUPS << std::endl;
        return;
    }

    // find course contained instance and add it to complete
    std::vector<Course*>::iterator it = std::find(completed_.begin(),
                                                  completed_.end(),
                                                  complete_inst->get_course());
    if ( it == completed_.end() ){
        completed_.push_back(complete_inst->get_course());
    }

    current_.erase(iter);
    credit_ += complete_inst->get_course()->get_credits();
    std::cout << COMPLETED << std::endl;
}

void Account::print_study_state()
{
    std::cout << "Current:" << std::endl;
    for ( Instance* inst: current_ ){
        inst->print_current_course();
    }

    std::cout << "Completed:" << std::endl;
    print_complete_course();
}

void Account::print_complete_course()
{
    for ( Course* cour : completed_ ){
        cour->print_info(true);
    }

    std::cout << "Total credits: " << credit_ << std::endl;
}
