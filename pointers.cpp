#include <bits/stdc++.h>
using namespace std;

/*
& (address of) operator returns the memory address of the first byte.
* (deference indirection operator) returns value at given memory location.

pointer stores the memory address of an object.

if we do not initialise the pointer it leads to creation of wild pointer (contain garbage address)

we can change the address to which pointer points

pointers are object while references are not
pointer can change the address they are pointing to
pointers need not be initialised

always remember &x returns pointer to x rather than address whose value is address

Besides memory address pointer can also hold null value
When a pointer is holding a null value, it means the pointer is not pointing at anything. 
Such a pointer is called a null pointer.

Favour reference over pointers 

Always use pass by reference (along with const -> can take both lvalues and rvalues) as these are more robust as they need to be bounded to an object to 
persist and thus prevents the chances of dereferencing null values. by address can only take lvalues

if we return then also copying can be a problem
*/

void passbyvalue(int val) {
    cout<<"Pass by value : "<<val<<endl;
}
void passbyadd(int* val) {
    cout<<"Pass by address : "<<*val<<endl;
}
void passbyref(int& val) {
    cout<<"Pass by value : "<<val<<endl;
}

void changevalue(int* ptr) {
    *ptr = 6;
}

void preventnull(const int* ptr) {
    if(!ptr) {
        cout<<"Null"<<endl;
        return;
    }
    cout<<"It is not null"<<endl;
}

void setnull(int* ptr) {
    ptr = nullptr;
}

void setnullref(int*& ptr) {
    ptr = nullptr;
}

void callhim(int* ptr) {
    cout<<"int* "<<endl;
}
void callhim(int ptr) {
    cout<<"int "<<endl;
}

// this would not work as the object get terminated as soon as the function ends
// const string& getstring() {
//     const string s = "Hello World";
//     return s;
// }    

// this will work
const string& getstring() {
    static const string s = "Hello World";
    return s;
}

const int& returnconstref(const int& ref) {
    return ref ;
}

int main() {
    int x = 5;
    int z = 9;
    double y = 1.2;
    cout<<&x<<" "<<*(&x)<<endl;
    int* wptr;
    int* ptr = &x; // ok
    // int* iptr = &y; // error
    double* dptr = &y; // ok
    // double* ddptr = &x; // error

    // int* p = 5; // error
    // int* p = 0x0012FF7C; // error considered as int

    // cout<<wptr<<endl; // no error but garbage value;
    // int* ptr1 , * ptr2 ; // to define multiple pointers

    // *ptr is lvalue
    cout<<*ptr<<endl;
    ptr = &z;
    cout<<*ptr<<endl;
    *ptr = 88;
    cout<<z<<" "<<*ptr<<endl;

    char* chptr ;
    double* dbptr ;
    cout<<sizeof(wptr)<<endl;
    cout<<sizeof(chptr)<<endl;
    cout<<sizeof(dbptr)<<endl;

    cout<<"Dangling ptr"<<endl;
    if(true) {
        int y = 9;
        ptr = &y;

        cout<<*ptr<<endl;
    }
    // object to which it was pointing is destroyed
    cout<<*ptr<<endl;

    // defining null ptr
    int* p = nullptr;
    int* q {};
    int* r = 0;
    int* s = NULL;

    int vala = 1 ;
    int valb = 1 ;

    if(!p) {
        cout<<"false"<<endl;
    }
    else {
        cout<<"true"<<endl;
    }

    // cout<<*p<<endl; // dereferencing null pointers crashes program 
    p = &vala;
    q = &valb;

    if(!p) {
        cout<<"false"<<endl;
    }
    else {
        cout<<"true"<<endl;
    }
    // there is no way of detecting dangling pointers best practice is to set it to nullptr (isn't done automatically)

    const int valc = 4 ;
    const int vald = 5 ;
    // int* ff = &valc; // violating constness
    const int* ee = &valc; // this works
    ee = &vald; // can chaange the address it holds no problem
    // *ee = 8; // can not change this
    ee = &x;
    // *ee = 8 ; // still won't work
    cout<<*ee<<endl;
    x = 100;
    cout<<*ee<<endl;

    // const pointers
    int* const pp = &x ; // needs to be initialized
    // pp =  &y; // won't work
    *pp = 7 ; // this works
    cout<<x<<endl;

    // const pointer to a const
    const int* const qq = &valc;
    // qq = &vald; // won't work

    // const int* donot = 10 ; // error can not point to rvalues as they don't have address

    int val = 99;
    ptr = &val;
    passbyvalue(val); // creates copy
    passbyref(val); // binds with object
    passbyadd(&val); // holds address object passed by address
    passbyadd(ptr); // pointer passed by value

    cout<<*ptr<<endl;
    changevalue(ptr); // if you do not eant to change value use const int*
    cout<<val<<endl;
    // avoids making copy of the object, but creates copy for storing the address which is faster

    // ptr = 0 ;
    // preventnull(ptr);

    cout<<ptr<<endl;
    setnull(ptr);
    cout<<ptr<<" "<<*ptr<<endl;
    setnullref(ptr);
    // ptr = 0 ;
    if(ptr) {
        cout<<"false"<<endl;
    }
    else {
        cout<<"true"<<endl;
    }

    // NULL has an ambiguous behaviour it can either evaluate to 0 , 0L , ((void*)0)
    ptr = NULL;
    callhim(ptr); // this in vs code is considered as int* but is ambiguous

    cout<<getstring()<<endl; // doesn't create a copy

    const int& ref1 = 5 ; // no problem it works
    cout<<ref1<<endl;
    // but when we do this using return from a function call the temperory variable gets forgotten
    const int& ref2 = returnconstref(6); // this gives dangling pointer
    cout<<ref2<<endl; 

    return 0;
}