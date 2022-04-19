#ifndef STACKTEMPL_H_
#define STACKTEMPL_H_

template <typename Type = int>  //default type is int if not specified (int is non-type parameter)
class Stack
{
private:
    enum { MAX = 10 };  // constant specific to class
    Type items[MAX];    // holds stack items
    int top;            // index for top stack item
public:
    Stack();
    ~Stack();
    bool isempty();
    bool isfull();
    bool push(const Type &item); // add item to stack
    bool pop(Type &item);        // pop top into item
};


//Template definition (to use by implicit instantiation)
//Below must be in the same header file to be compiled successfully
template <typename Type>
Stack<Type>::Stack()
{ top = 0; }

template <typename Type>
Stack<Type>::~Stack(){}

template <typename Type>
bool Stack<Type>::isempty() {
    return top == 0;
}

template <typename Type>
bool Stack<Type>::isfull() {
    return top == MAX;
}

template <typename Type>
bool Stack<Type>::push(const Type &item)
{
    if (top < MAX)
    {
        items[top++] = item;
        return true;
    }
    else
        return false;
}

template <typename Type>
bool Stack<Type>::pop(Type &item)
{
    if (top > 0)
    {
        item = items[--top];
        return true;
    }
    else
        return false;
}


#endif