#include <bits/stdc++.h>
using namespace std;

struct Employee {
    // data members
    string name;
    int id;
    int age;
    double salary;
};

// overloading output << operator
ostream& operator<<(ostream& out, const Employee& e) {
    out << "name : "<<e.name<<" id : "<<e.id<<" age : "<<e.age<<" salary : "<<e.salary;
    return out;
}

void printEmployee(Employee& val) {
    cout<<val.name<<" id : "<<val.id<<"  age : "<<val.age<<" salary : "<<val.salary<<endl;
}

void printEmployee(const Employee& val) {
    cout<<val.name<<" id : "<<val.id<<"  age : "<<val.age<<" salary : "<<val.salary<<endl;
}

struct Point3D {
    int x {};
    int y {};
    int z {};
};

ostream& operator<<(ostream& out , const Point3D& pt) {
    out << "x : " << pt.x<<" y : "<<pt.y<<" z : "<<pt.z;
    return out;
}

Point3D& getpoint3D() {
    Point3D temp = {0,0,0};
    Point3D& t = temp;
    return t;
}

int main() {
    Employee x ;
    x.age = 19 ;
    cout<<x.age<<endl;
    cout<<x.id<<endl; // undefined behaviour as not initialised

    Employee y {"Chotu" , 3 , 26}; // passed in the order of declaration
    printEmployee(y);

    cout<<y<<endl;

    // can be const
    // const Employee a ; //error as uninitialised
    const Employee a {}; // always prefer value initialisation rather than depending on default values
    Employee b {.id = 9 , .salary = 4230.45}; // designateed initialiser
    // Employee b {.salary = 930.53 , .id = 9}; // error as doesn't match the declaration order
    cout<<b<<endl;
    y = {y.name , y.id , y.age + 1 , 78319.31}; // cumulatively changing members
    cout<<y<<endl;
    x = y ; // copy
    cout<<x<<endl;

    // printEmployee(Employee {"Hero" , 1 , 20 , 4180.31}); // error rvalue 
    printEmployee(Employee {"Hero" , 1 , 20 , 4180.31}); 

    Point3D& z = getpoint3D(); // dangling reference
    cout<<z<<endl;
    return 0;
}