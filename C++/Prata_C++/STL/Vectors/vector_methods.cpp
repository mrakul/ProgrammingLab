// vect2.cpp -- methods and iterators
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Review
{
    std::string title;
    int rating;

    static bool worseThan(const Review &r1, const Review &r2)   // makes strict weak ordering. Note: me included in within the struct
    {
        if (r1.rating < r2.rating)
            return false;                        //false means that need to change elements
        else
            return true;                         //true = no need to change elements
    }
};

bool FillReview(Review &rr);
void ShowReview(const Review &rr);

// for sort() function
bool operator<(const Review &r1, const Review &r2); // makes total ordering
// bool worseThan(const Review &r1, const Review &r2); // makes strict weak ordering

int main(int argc, char const *argv[])
{
    using std::cout;
    using std::vector;
    vector<Review> books;
    Review temp;

    // Input while true
    while (FillReview(temp))
        books.push_back(temp);

    int num = books.size(); // get number of elements

    if (num > 0){
        cout << "Thank you. You entered the following:\n"
            << "Rating\tBook\n";
        for (int i = 0; i < num; i++)
            ShowReview(books[i]);
        cout << "Reprising:" << std::endl
            << "Rating\tBook" << std::endl;

        // Use an iterator to show all elements
        vector<Review>::iterator pr;
        // for (pr = books.begin(); pr != books.end(); pr++)
        //     ShowReview(*pr);
        for_each(books.begin(), books.end(), ShowReview); // This is equal to the for cycle above

        // Copy to another list => oldlist
        vector<Review> oldlist(books); // copy constructor used
        if (num > 3){
            // remove 2 items
            books.erase(books.begin() + 1, books.begin() + 3); // remove 2-nd and 3-rd element, that is [1;3)
            cout << "After erasure:\n";
            for (pr = books.begin(); pr != books.end(); pr++)
                ShowReview(*pr);
            // insert 1 item
            books.insert(books.begin(), oldlist.begin() + 1, // add to the books[0] the 2-nd element of the oldlist
                oldlist.begin() + 2);
            cout << "After insertion:\n";
            for (pr = books.begin(); pr != books.end(); pr++)
                ShowReview(*pr);
        }

        // Test sorting
        cout << "Total sorting by title and rating: " << std::endl;
        std::sort(books.begin(), books.end());                      // sorting by use of < operator for the type Review
        for (auto x : books) ShowReview(x);

        cout << "Descending order by rating: " << std::endl;
        std::sort(books.begin(), books.end(), Review::worseThan);            //Sort using the function (descending by rating)
        for (auto x : books) ShowReview(x);

        // Swap two lists
        books.swap(oldlist);
        cout << "Swapping oldlist with books:\n";
        for (pr = books.begin(); pr != books.end(); pr++)
            ShowReview(*pr);
    }
    else
        cout << "Nothing entered, nothing gained.\n";
    return 0;
}

bool FillReview(Review &rr)
{
    std::cout << "Enter book title (quit to quit): ";
    std::getline(std::cin, rr.title);
    if (rr.title == "quit")
        return false;
    std::cout << "Enter book rating: ";
    std::cin >> rr.rating;
    if (!std::cin)
        return false;
    // get rid of rest of input line
    while (std::cin.get() != '\n')
        continue;
    return true;
}

void ShowReview(const Review &rr)
{
    std::cout << rr.rating << "\t" << rr.title << std::endl;
}

bool operator<(const Review &r1, const Review &r2) // just compare, the rest is done by sort()
{
    if (r1.title < r2.title)
        return true;
    else if (r1.title == r2.title && r1.rating < r2.rating)
        return true;
    else
        return false;
}

// bool worseThan(const Review &r1, const Review &r2)
// {
//     if (r1.rating < r2.rating)
//         return false;       //false means that need to change elements
//     else
//         return true;        //true = no need to change elements
// }