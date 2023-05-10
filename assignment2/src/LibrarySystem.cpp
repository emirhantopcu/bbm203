#include <iostream>
#include "LibrarySystem.h"
using namespace std;

struct FilmNode{
    FilmNode(int id, const string &title, int year) : id(id), title(title), year(year) {}
    int id;
    string title;
    int year;
    int status = -1;
    FilmNode* next;
};
FilmNode* film_list_head = nullptr;
FilmNode* film_list_last = nullptr;

struct UserNode{
    UserNode(int id, const string &title) : id(id), title(title) {}
    UserNode* prev;
    int id;
    string title;
    FilmNode* checkedout_head = nullptr;
    FilmNode* checkedout_last = nullptr;
    UserNode* next;
};
UserNode* user_head = nullptr;
UserNode* user_last = nullptr;


void LibrarySystem::addMovie(const int id, const string title, const int year) {
    FilmNode* current = film_list_head;
    bool id_check = true;
    if (current != nullptr){
        while (true){
            if (current->id == id){
                id_check = false;
            }
            if (current == film_list_last){
                break;
            }
            current = current->next;
        }
    }
    if (id_check){
        if (film_list_head == nullptr){
            film_list_head = new FilmNode(id,title,year);
            film_list_last = film_list_head;
            film_list_head->next = film_list_last;
        }else{
            film_list_last->next = new FilmNode(id,title,year);
            film_list_last = film_list_last->next;
            film_list_last->next = film_list_head;
        }
        cout << "Movie " << id << " has been added" << endl;
    }else{
        cout << "Movie " << id << " already exist" << endl;
    }
}

void LibrarySystem::deleteMovie(const int id) {
    FilmNode* current = film_list_head;
    if (current == nullptr){
        cout << "Movie " << id << " does not exist"<<endl;
        return;
    }
    while(true){
        if (current->id == id){
            if (current->status != -1){                                                 //this function firstly checkes if the movie has been checked out and if so
                cout << "Movie " << id << " has been checked out" << endl;              //deletes it from the list of that user. then deletes the movie from the main movie list
                UserNode* current_user = user_head;
                while (true){
                    if (current->status == current_user->id){
                        FilmNode* current_mov = current_user->checkedout_head;
                        while (true){
                            if (current_mov->id == id){
                                FilmNode* current_prev = current_user->checkedout_head;
                                while (true){
                                    if (current_prev->next == current_mov){
                                        break;
                                    }
                                    current_prev = current_prev->next;
                                }
                                if (current_mov == current_mov->next){
                                    delete current_mov;
                                    current_user->checkedout_head = nullptr;
                                    current_user->checkedout_last = nullptr;
                                    break;
                                }else if (current_mov == current_user->checkedout_last){
                                    current_prev->next = current_mov->next;
                                    current_user->checkedout_last = current_prev;
                                    delete current_mov;
                                    break;
                                }else if (current_mov == current_user->checkedout_head){
                                    current_user->checkedout_head = current_mov->next;
                                    current_user->checkedout_last->next = current_mov->next;
                                    delete current_mov;
                                    break;
                                }else{
                                    current_prev->next = current_mov->next;
                                    delete current_mov;
                                    break;
                                }
                            }
                            current_mov = current_mov->next;
                        }
                        break;
                    }
                    current_user = current_user->next;
                }
            } else{
                cout << "Movie " << id <<" has not been checked out" << endl;
            }
            FilmNode* film_delete_prev = film_list_head;
            while (true){
                if (film_delete_prev->next == current){
                    break;
                }
                film_delete_prev = film_delete_prev->next;
            }
            if (current == current->next){
                delete current;
                film_list_head = nullptr;
                film_list_last = nullptr;
                cout << "Movie " << id <<" has been deleted" << endl;
                break;
            }else if(current == film_list_last){
                film_delete_prev->next = current->next;
                film_list_last = film_delete_prev;
                delete current;
                cout << "Movie " << id <<" has been deleted" << endl;
                break;
            }else if(current == film_list_head){
                film_list_head = current->next;
                film_list_last->next = current->next;
                delete current;
                cout << "Movie " << id <<" has been deleted" << endl;
                break;
            }else{
                film_delete_prev->next = current->next;
                delete current;
                cout << "Movie " << id <<" has been deleted" << endl;
                break;
            }
        }
        if (current == film_list_last){
            cout << "Movie " << id << " does not exist" << endl;
            break;
        }
        current = current->next;
    }
}

void LibrarySystem::addUser(const int id, const string username) {
    UserNode* current = user_head;
    bool id_check = true;
    if (current != nullptr){
        while (true){
            if (current->id == id){
                id_check = false;
            }
            if (current == user_last){
                break;
            }
            current = current->next;
        }
    }
    if (id_check){
        if (user_head == nullptr){
            user_head = new UserNode(id,username);
            user_last = user_head;
            user_last->next = user_head;
            user_head->prev = user_last;
        }else{
            user_last->next = new UserNode(id,username);
            user_last->next->prev = user_last;
            user_last = user_last->next;
            user_last->next = user_head;
            user_head->prev = user_last;
        }
        cout << "User " << id << " has been added" << endl;
    }else{
        cout << "User " << id << " already exist" << endl;
    }
}

void LibrarySystem::deleteUser(const int id) {
    UserNode* current = user_head;
    if (current == nullptr){
        cout << "User " << id << " does not exist"<<endl;
        return;
    }
    while(true){
        if (current->id == id){
            if (current->checkedout_head != nullptr){
                while (current->checkedout_head != nullptr){
                    if (current->checkedout_head == current->checkedout_last){
                        FilmNode* film_delete = film_list_head;
                        while (true){
                            if (film_delete->id == current->checkedout_head->id){           //this function deletes movies that this user had been checked out first.
                                FilmNode* film_delete_prev = film_list_head;                //then deletes the user.
                                while (true){
                                    if (film_delete_prev->next == film_delete){
                                        break;
                                    }
                                    film_delete_prev = film_delete_prev->next;
                                }
                                if (film_delete->next == film_delete){
                                    delete film_delete;
                                    film_list_head = nullptr;
                                    film_list_last = nullptr;
                                }else if(film_delete == film_list_head){
                                    film_delete_prev->next = film_delete->next;
                                    film_list_head = film_delete->next;
                                    delete film_delete;
                                }else if(film_delete == film_list_last){
                                    film_delete_prev->next = film_delete->next;
                                    film_list_last = film_delete_prev;
                                    delete film_delete;
                                }else{
                                    film_delete_prev->next = film_delete->next;
                                    delete film_delete;
                                }
                                break;
                            }
                            film_delete = film_delete->next;
                        }
                        delete current->checkedout_head;
                        current->checkedout_head = nullptr;
                        current->checkedout_last = nullptr;
                    }else{
                        FilmNode* temp;
                        temp = current->checkedout_head;
                        FilmNode* film_delete = film_list_head;
                        while (true){
                            if (film_delete->id == temp->id){
                                FilmNode* film_delete_prev = film_list_head;
                                while (true){
                                    if (film_delete_prev->next == film_delete){
                                        break;
                                    }
                                    film_delete_prev = film_delete_prev->next;
                                }
                                if (film_delete->next == film_delete){
                                    delete film_delete;
                                    film_list_head = nullptr;
                                    film_list_last = nullptr;
                                }else if(film_delete == film_list_head){
                                    film_delete_prev->next = film_delete->next;
                                    film_list_head = film_delete->next;
                                    delete film_delete;
                                }else if(film_delete == film_list_last){
                                    film_delete_prev->next = film_delete->next;
                                    film_list_last = film_delete_prev;
                                    delete film_delete;
                                }else{
                                    film_delete_prev->next = film_delete->next;
                                    delete film_delete;
                                }
                                break;
                            }
                            film_delete = film_delete->next;
                        }
                        current->checkedout_head = current->checkedout_head->next;
                        delete temp;
                    }
                }
            }
            if (current == current->next){
                delete current;
                user_head = nullptr;
                user_last = nullptr;
                cout << "User " << id << " has been deleted" << endl;
            }else if (current == user_head){
                user_last->next = current->next;
                current->next->prev = user_last;
                user_head = current->next;
                delete current;
                cout << "User " << id << " has been deleted" << endl;
            }else if (current == user_last){
                current->prev->next = user_head;
                user_head->prev = current->prev;
                user_last = current->prev;
                delete current;
                cout << "User " << id << " has been deleted" << endl;
            }else{
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
                cout << "User " << id << " has been deleted" << endl;
            }
            break;
        }
        if (current == user_last){
            cout << "User " << id << " does not exist" << endl;
            break;
        }
        current = current->next;
    }
}

void LibrarySystem::checkoutMovie(const int movie_id, const int user_id) {
    FilmNode* search = film_list_head;
    while (true){
        if (search->id == movie_id){
            UserNode* c_user = user_head;
            while (true){
                if (c_user->id == user_id){
                    break;
                }
                if (c_user == user_last){
                    cout << "User " << user_id << " not found" << endl;
                    return;
                }
                c_user = c_user->next;
            }
            if (search->status == -1){
                if (c_user->checkedout_head == nullptr){
                    search->status = user_id;
                    c_user->checkedout_head = new FilmNode(search->id,search->title,search->year);
                    c_user->checkedout_last = c_user->checkedout_head;
                    c_user->checkedout_head->next = c_user->checkedout_last;
                    cout << "Movie " << movie_id << " has been checked out by User " << user_id << endl;
                }else{
                    search->status = user_id;
                    c_user->checkedout_last->next = new FilmNode(search->id,search->title,search->year);
                    c_user->checkedout_last = c_user->checkedout_last->next;
                    c_user->checkedout_last->next = c_user->checkedout_head;
                    cout << "Movie " << movie_id << " has been checked out by User " << user_id << endl;
                }
            }else{
                cout << "Movie " << movie_id << " does not exist for checkout"<< endl;
            }
            break;
        }
        if (search == film_list_last){
            cout << "Movie " << movie_id << " does not exist"<<endl;
            break;
        }
        search = search->next;
    }
}

void LibrarySystem::returnMovie(const int movie_id) {
    FilmNode* film_return = film_list_head;
    while(true){
        if (film_return->id == movie_id){
            if (film_return->status != -1){
                UserNode* user_return = user_head;
                while (true){
                    if (user_return->id == film_return->status){
                        FilmNode* current = user_return->checkedout_head;
                        while(true){
                            if (current->id == movie_id){
                                FilmNode* current_prev = user_return->checkedout_head;
                                while (true){
                                    if (current_prev->next == current){
                                        break;
                                    }
                                    current_prev = current_prev->next;
                                }
                                if (current == current->next){
                                    delete current;
                                    user_return->checkedout_head = nullptr;
                                    user_return->checkedout_last = nullptr;                         //this and similar codes that i have wrote takes different actions
                                    cout << "Movie " << movie_id <<" has been returned" << endl;    //for each possible position of the movie in the list
                                    break;
                                }else if (current == user_return->checkedout_last){
                                    current_prev->next = current->next;
                                    user_return->checkedout_last = current_prev;
                                    delete current;
                                    cout << "Movie " << movie_id <<" has been returned" << endl;
                                    break;
                                }else if (current == user_return->checkedout_head){
                                    user_return->checkedout_head = current->next;
                                    user_return->checkedout_last->next = current->next;
                                    delete current;
                                    cout << "Movie " << movie_id <<" has been returned" << endl;
                                    break;
                                }else{
                                    current_prev->next = current->next;
                                    delete current;
                                    cout << "Movie " << movie_id <<" has been returned" << endl;
                                    break;
                                }
                            }
                            current = current->next;
                        }
                        break;
                    }
                    user_return = user_return->next;
                }
                film_return->status = -1;
                break;
            }else{
                cout << "Movie " << movie_id << " has not been checked out" << endl;
                break;
            }
        }
        if (film_return == film_list_last){
            cout << "Movie " << movie_id << " does not exist in the library"<<endl;
            break;
        }
        film_return = film_return->next;
    }
}

void LibrarySystem::showAllMovie() {
    FilmNode* current = film_list_head;
    if (current != nullptr){
        cout << "Movie id - Movie name - Year - Status" << endl;
        while (true){
            if (current->status == -1){
                cout << current->id << " " << current->title << " " << current->year << " Not checked out" << endl;
            }else{
                cout << current->id << " " << current->title << " " << current->year << " Checked out by User " << current->status << endl;
            }
            if (current == film_list_last){
                break;
            }
            current = current->next;
        }
    }
}

void LibrarySystem::showMovie(const int id) {
    FilmNode* f_search = film_list_head;
    if (f_search != nullptr){
        while(true){
            if (f_search->id == id){
                cout << f_search->id << " " << f_search->title << " " << f_search->year;
                if (f_search->status == -1){
                    cout << " Not checked out" << endl;
                    break;
                }else{
                    cout << " Checked out by User " << f_search->status << endl;
                    break;
                }
            }
            if (f_search == film_list_last){
                cout << "Movie with id " << id << " does not exist" << endl;
                break;
            }
            f_search = f_search->next;
        }
    }else{
        cout << "Movie with id " << id << " does not exist";
    }
}

void LibrarySystem::showUser(const int id) {
    UserNode* current_user = user_head;
    while(true){
        if (current_user->id == id){
            cout << "User id: " << current_user->id <<" User name: " << current_user->title << endl;
            cout << "User " << current_user->id <<" checked out the following Movies:" << endl;
            if (current_user->checkedout_head != nullptr){
                cout << "Movie id - Movie name - Year" << endl;
                FilmNode* current_film = current_user->checkedout_head;
                while (true){
                    cout << current_film->id << " " << current_film->title << " " << current_film->year << endl;
                    if (current_film == current_user->checkedout_last){
                        break;
                    }
                    current_film = current_film->next;
                }
            }
            break;
        }
        if (current_user == user_last){
            cout << "User " << id << " not found"<< endl;
            break;
        }
        current_user = current_user->next;
    }
}
