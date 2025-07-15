#include <bits/stdc++.h>
using namespace std;

/*
Function pointer -> pointer holding address of a function
these are useful for sending them as arguments in another function and such funstions are called callback functions
*/

int foo() {
    return 5;
}

double goo() {
    return 5.5;
}

void print(int x) {
    cout<<"int version"<<endl;
}
void print(int x , int y =10) {
    cout<<"int int version"<<endl;
}

bool ascending(int x , int y) {
    return y < x ;
}
bool descending(int x , int y) {
    return y > x ;
}

// can be defined using function keyword as function<bool(int,int)> fnc but using this we call only using implicit
void SortSelection(int* arr , int size , bool (*compfn)(int,int) = ascending) {
    if(!arr || ! compfn) return;

    for(int i{0} ;i<size ;i++) {
        for(int j{i+1} ;j<size ;j++) {
            if(compfn(arr[i],arr[j])) {
                swap(arr[i],arr[j]);
            }
        }
    }
}


void printarr(int* arr , int size) {
    for(int i{0} ;i<size ;i++) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

/*
The memory that a program uses is typically divided into a few different areas, called segments:

The code segment (also called a text segment), where the compiled program sits in memory. The code segment is 
typically read-only.
The bss segment (also called the uninitialized data segment), where zero-initialized global and static variables are 
stored.
The data segment (also called the initialized data segment), where initialized global and static variables are stored
The heap, where dynamically allocated variables are allocated from.
The call stack, where function parameters, local variables, and other function-related information are stored.

heap segment (free store)

Allocating memory on the heap is comparatively slow.
Allocated memory stays allocated until it is specifically deallocated or the application ends 
Dynamically allocated memory must be accessed through a pointer. Dereferencing a pointer is slower than accessing a 
variable directly.
Because the heap is a big pool of memory, large arrays, structures, or classes can be allocated here.

Call stack keeps track of all the active functions (those that have been called but have not yet terminated) from the 
start of the program to the current point of execution, and handles allocation of all function parameters and local
variables.

Call stack segment contains the memory for call stack

When a function is called:
The program encounters a function call.
A stack frame is constructed and pushed on the stack. The stack frame consists of:
-The address of the instruction beyond the function call (called the return address). This is how the CPU remembers 
where to return to after the called function exits.
-All function arguments.
-Memory for any local variables
-Saved copies of any registers modified by the function that need to be restored when the function returns
The CPU jumps to the function’s start point.
The instructions inside of the function begin executing.

When the function terminates, the following steps happen:
Registers are restored from the call stack
The stack frame is popped off the stack. This frees the memory for all local variables and arguments.
The return value is handled.
The CPU resumes execution at the return address.

Stack overflow happens when all the memory in the stack has been allocated, further allocations begin overflowing 
into other sections of memory.
*/

long long lcnt = 0;
void printi() {
    cout<<++lcnt<<endl;
    // printi(); // here stack would overflow 
    // return printi(); // this is tail function call which is optimised by compiler by using the same stack space of 
    // the caller function to avoid stack growth this won't stop executing
}

void funcy() {
    cout<<"called funcy"<<endl;
}

void funcy(int v) {
    cout<<"called int funcy"<<endl;
}

int main() {
    // () -> jumps the execution to this address
    cout<<foo()<<endl;

    // this is converted into function pointer and is converted into bool since it is non null it prints 1
    cout<<foo<<endl;

    // int (*fncptr)(); // creates a pointer to a function that takes no argument and returns an integer
    // int (*const fncnstptr)(); // constant function pointer

    int (*fptr)() {&foo};
    // double (*fooptr)() {&foo}; // error return type do not match
    double (*gooptr)() {&goo};
    int (*fooptr)() {foo}; // this works for some compilers

    // int (*valueptr)() {foo()}; // wrong you are assigning return value
    // void* voidptr {foo}; // this not allowed
    // can be assigned to nullptr

    cout<<fptr()<<endl; // implicit dereference 
    cout<<(*fptr)()<<endl; // explicit dereference 
    
    void (*iptr)(int) {print};
    iptr(1);

    void (*iiptr)(int ,int) {print};
    iiptr(1,3); // it ignores default argument
    // iiptr(1) // do not work

    int* arr {new int [5]{5 , 2 , 8 , 4 , 7}};
    SortSelection(arr , 5 , ascending);
    printarr(arr,5);
    SortSelection(arr , 5 , descending);
    printarr(arr,5);

    printi();

    void (*fn)() {&funcy};
    fn();

    // fn = &funcy;
    // fn(7);

    function<void(int)> ptrfn {static_cast<void(*)(int)>(&funcy)};
    ptrfn(10);
    return 0;
}