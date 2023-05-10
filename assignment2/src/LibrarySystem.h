#ifndef ASSIGNMENT2_LIBRARYSYSTEM_H
#define ASSIGNMENT2_LIBRARYSYSTEM_H
using namespace std;

class LibrarySystem {
public:
    LibrarySystem();
    ~LibrarySystem();

    static void addMovie(const int id, const string title, const int year);
    static void deleteMovie(const int id);
    static void addUser(const int id, const string username);
    static void deleteUser(const int id);
    static void checkoutMovie(const int movie_id, const int user_id);
    static void returnMovie(const int movie_id);
    static void showAllMovie();
    static void showMovie(const int id);
    static void showUser(const int id);
};


#endif //ASSIGNMENT2_LIBRARYSYSTEM_H
