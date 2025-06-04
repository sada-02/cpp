#include "bits/stdc++.h"
using namespace std;

/*
Function template : used for generation of one or more overloaded functions
Primary template -> initial function template used to generate other functions
instantiated function -> generated from primary template

Use of placeholder types (type template parameters) :
- type template parameter -> represents a type
- non type template parameter -> represents a constexpr value
- template template parameter -> represents a template

Template parameter declaration -> scope is strictly limited to function template or class template that follows it
typename -> type template parameter

Function templates are not functions -> not compiled or executed, they create functions that compile or execute
Function call using template argument (types in angular brackets) that will be used instead of template parameters

implicit instantiation -> when function is instantiated due to function call
function that is instantiated from a template is called specialization (primary template)
Ones instantiated, any subsequent calls will not require further instantiation

Using "auto" keyword to create templates -> abbreviated function template
*/

// 1
template <typename T>
T maxx(T x , T y) {
    return (x > y) ? x : y ;
}

// 2
// template <typename T>
// void print(T x) {
//     cout<<"template "<<x<<endl;
// }

// void print(bool x) {
//     cout<<"non template "<<x<<endl;
// }

// 3
template <typename T>
void func(T x , double a) {
    cout<<"template and non template both "<<x<<" "<<a<<endl;
}

// issue
template <typename T>
T func(T x) {
    return x+1;
}

// to disallow certain instantiations we can use function template specialization
// template <>
// int func(int x) = delete ;

// 4 
// Interesting 
// static local variables -> each instantiated functions have seperate version of static local variable
// template <typename T>
// void staticvar(T x) {
//     static int idx {0};
//     cout<<++idx<<" "<<x<<endl;
// }

// 5
/*
use auto as having T or U may result in loss of data 
Also when using auto needs to fully define function in defination else throws error
*/
template <typename T , typename U>
auto maxx(T x , U y) {
    return x > y ? x : y ;
}
// same as
// auto maxx(auto x , auto y) {
//     return x > y ? x : y ;
// }

// 6
template <typename T>
void boo(T x , T y) {
    cout<<"same T and T"<<endl;
}
template <typename T , typename U>
void boo(T x , U y) {
    cout<<"diff T and U"<<endl;
}

int main() {
    // 1
    // cout<<maxx(2,4)<<endl; // telling function to look at all the definitions (template or non template) of this fn
    // cout<<maxx<int>(2.5,4.3)<<endl; // explicitly telling to replace T with int
    // cout<<maxx(2.3,1.34)<<endl;
    // cout<<maxx('a','x')<<endl;
    // cout<<maxx<>(2,4.4)<<endl; // telling the compiler to only look at the template version of this function
    // cout<<maxx<>(3,3.4)<<endl; // error
    // typeconversion done only when resolving fn overload

    // 2
    // print<bool>(true);
    // print<>(true);
    // print(true);

    // 3
    string s = "hello world";
    // func('a' , 9.2);
    // cout<<func(1)<<endl;
    // cout<<func(1.3)<<endl;
    // cout<<func('c')<<endl;
    // cout<<func(s)<<endl; // throws error as it don't make sense
    // cout<<func("hello world")<<endl; // this don't show error

    // 4
    // staticvar(3);
    // staticvar(7);
    // staticvar(7.2);

    // 5
    // cout<<maxx(3,4.1)<<endl;

    // 6
    boo(1 , 1); // compiler could have run T and U but prefers to run more restrictive 
    // In case same restriction is found in two or more function -> ambiguous error
    boo(1 , 1.1);

    return 0;
}