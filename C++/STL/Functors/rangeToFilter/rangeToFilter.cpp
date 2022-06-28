#include <list>
#include <iostream>

// Make a predicate,  that is takes one argument (int in our case) and returning boolean value
bool tooBig(int n)
{
    return (n < 8 || n > 10); // Stay only numbers in the range of (8; 10)
}

//Create template functor class to be able to specify the range of allowed values
template <typename Type>
class AllowedRange
{
private:
    Type lowerBound;
    Type upperBound;
public:
    AllowedRange(const Type &lowValue, const Type &upValue) : lowerBound(lowValue), upperBound(upValue) {}

    //Use the pair template to get the pair of the current bounds
    std::pair<Type, Type> getBounds(){
        return std::pair<Type, Type>{lowerBound, upperBound};
    }

    //Overloaded operator to filter out values by allowed range (predicate in this case, since takes on argument and returning boolean)
    bool operator()(const Type &curVal){
        return (curVal <= lowerBound || curVal >= upperBound);       //If out of the range, return true meaning to remove
    }
};

// Function to print the list
void printTheList(std::list<int> &listToPrint);

int main(int argc, char const *argv[])
{
    using std::list;
    list<int> numbers;
    //Populate the list
    numbers.insert(numbers.begin(), 9);  // insert to the head
    numbers.insert(numbers.begin(), 10); // insert to the head
    numbers.insert(numbers.begin(), 11); // insert to the head
    numbers.push_back(15); // insert to the head
    numbers.push_front(7); // insert to the tail

    //Make the copy of the list
    list<int> numbers2(numbers);

    // Print out the current list #1
    printTheList(numbers);

    // Remove unwanted numbers from the list #1
    numbers.remove_if(tooBig);

    // Print out the list after the removing values from the list #1
    printTheList(numbers);

    /*** List #2 test ***/
    AllowedRange<int> rangeToFilter(7, 10);        //Make allowed range of (7; 10)

    //Print the current bounds and the initial list values
    std::cout << "The lower bound is: " << rangeToFilter.getBounds().first << " and the upper bound is: " << rangeToFilter.getBounds().second << std::endl;
    printTheList(numbers2);     //print the current list
    //Sort the values and print
    numbers2.sort();
    printTheList(numbers2);

    //Remove the numbers by using a functor created and print out the list again
    numbers2.remove_if(rangeToFilter);     //or use anonymous object as numbers2.remove_if(AllowedRange<int>(7, 10));
    printTheList(numbers2);

    return 0;
}

void printTheList(std::list<int> &listToPrint){
    std::cout << "List values: " << std::endl;
    for (auto number : listToPrint)
        std::cout << number << " ";
    std::cout << std::endl;
}