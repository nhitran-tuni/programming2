#include "cards.hh"

using namespace std;
// TODO: Implement the methods here
Cards::Cards(): top_(nullptr), bottom_(nullptr) {
}

Cards::~Cards() {
    while (top_ != nullptr) {
        Card_data* card_release = top_;
        top_ = top_->next;

        delete card_release;
    }
}

void Cards::add(int id) {
    Card_data* new_card = new Card_data{id, nullptr};

    if (top_ == nullptr) {
        top_ = new_card;
        bottom_ = new_card;
    } else {
        bottom_->next = new_card;
        bottom_ = new_card;
    }
}

void Cards::print_from_top_to_bottom(std::ostream &s) {
    Card_data* card_print = top_;
    unsigned int count = 1;

    while (card_print != nullptr) {
        s << count << ": " << card_print->data << endl;
        ++count;
        card_print = card_print->next;
    }
}

bool Cards::remove(int &id) {
    if ( top_ == nullptr ) {
        return false;
    }

    Card_data* card_remove = top_;

    id = card_remove->data;

    if (top_ == bottom_) {
        top_ = nullptr;
        bottom_ = nullptr;
    } else {
        top_ = top_->next;
    }

    delete card_remove;

    return true;
}

bool Cards::bottom_to_top() {
    if ( top_ == nullptr) {
        return false;
    }

    Card_data* card_bottom_to_top = new Card_data{bottom_->data,top_};
    Card_data* card_count = top_;

    top_ = card_bottom_to_top;

    while ( card_count != nullptr ) {
        if ( card_count->next == bottom_ ) {
            card_count->next = nullptr;
            bottom_ = card_count;
            break;
        }else {
            card_count = card_count->next;
        }
    }

    return true;
}

bool Cards::top_to_bottom() {
    if ( top_ == nullptr ) {
        return false;
    }

    Card_data* card_top_to_bottom = new Card_data{top_->data, nullptr};

    bottom_->next = card_top_to_bottom;
    bottom_ = card_top_to_bottom;
    top_ = top_->next;

    return true;
}

void Cards::print_from_bottom_to_top(ostream &s) {
    Card_data* card_print_inverse = bottom_;
    unsigned int count = 1;

    while (card_print_inverse != top_) {
        s << count << ": " << card_print_inverse->data << endl;
        ++count;
        Card_data* card_find = top_;
        while (card_find != nullptr) {
            if (card_find->next == card_print_inverse) {
                card_print_inverse = card_find;
            } else {
                card_find = card_find->next;
            }
        }
    }

    s << count << ": " << top_->data << endl;
}

