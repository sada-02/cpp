#include <bits/stdc++.h>
using namespace std;

void foo(int&& v) {
    cout<<"rvalue ref"<<endl;
}

void foo(const int& v) {
    cout<<"const lvalue ref"<<endl;
}

template <typename T>
class Auto_Ptr {
    private :
    T* m_ptr ;

    public :
    Auto_Ptr(T* ptr = nullptr) : m_ptr {ptr} {
        cout<<"Constructor was called"<<endl;
    }

    ~Auto_Ptr() {
        cout<<"Destructors are called"<<endl;
        delete m_ptr ;
    }

    Auto_Ptr(const Auto_Ptr& ptr) {
        m_ptr = new T();
        *m_ptr = *ptr.m_ptr;
        cout<<"Copy Constructor was called"<<endl;
    }

    Auto_Ptr(Auto_Ptr&& ptr) : m_ptr {ptr.m_ptr} {
        ptr.m_ptr = nullptr;
        cout<<"Move Constructor was called"<<endl;
    }

    Auto_Ptr& operator=(const Auto_Ptr& a) {
        cout<<"Copy assignment operator was called"<<endl;
        if(&a == this) return *this;
        
        delete m_ptr;
        m_ptr = new T();
        *m_ptr = *a.m_ptr;

        return *this;
    }

    Auto_Ptr& operator=(Auto_Ptr&& ptr) {
        cout<<"Move assignment operator was called"<<endl;
        if(&ptr == this) return *this;

        delete m_ptr ;
        m_ptr = ptr.m_ptr ;
        ptr.m_ptr = nullptr ;
        return *this;
    }

    T& operator*() const {
        return *this;
    }

    T* operator->() const {
        return this;
    }
};

class Resource {
    public:
    Resource() {
        cout<<"Resource acquired"<<endl;
    }

    ~Resource() {
        cout<<"Resource deallocated"<<endl;
    }
};

Auto_Ptr<Resource> AssignResource() {
    cout<<"Assigning the resource"<<endl;
    Auto_Ptr<Resource> new_resource {new Resource()};
    return new_resource;
}

class Name {
    private :
    string m_name ;

    public :
    Name(string s) : m_name {s} {
        cout<<"Constructor was called"<<endl;
    }

    ~Name() {
        cout<<"Destructor was called"<<endl;
    }

    Name(const Name& val) : m_name {val.m_name} {
        cout<<"Copy Constructor was called";
    }

    void printName() {
        cout<<m_name<<endl;
    }

    Name(Name&& val) = delete ;

    Name& operator=(const Name& val) {
        if(&val == this) return *this;
        m_name = val.m_name ;
        return *this;
    }

    Name& operator=(Name&& val) = delete;
};

Name func() {
    Name res("what");
    // return res; this not work as use of move is preferred

    return Name("what"); // works
    // return move(res); --> do not work also do not fallback to copy even if move fails
}

/*
Move semantics -> used for rvalues (transfer of ownership)
Copy semantics -> when lvalues or move not defined

Implicit move constructor involved when no user ddefined copy , move or user declared destructor
It works as follows :
if member has move then move else copy

Deleted function takes part in function overloading and gives error if selected
when return by value, move is prefered

move is used to convert lvalue into rvalue references -> the moved object should not be further refered
remember use smart pointer on stack only not in dynamic memory
*/

unique_ptr<Resource> createResource() {
    unique_ptr<Resource> temp {new Resource()};
    return temp;
}

void printSurname(unique_ptr<Name> p) {
    cout<<"xoxo"<<endl;
}
void printSurname(const Name* p) {
    cout<<"xoxo"<<endl;
}

class Cycleptr {
    private :
    string m_name ;
    shared_ptr<Cycleptr> strong ;
    weak_ptr<Cycleptr> weak;

    public :
    Cycleptr(const string& s = "") : m_name {s} {
        cout<<"Constructor"<<endl;
    }

    ~Cycleptr() {
        cout<<"Destructor"<<endl;
    }

    void partnerStrong(shared_ptr<Cycleptr>& ptr) {
        this->strong = ptr;
        cout<<m_name<<" :: "<<ptr->m_name<<endl;
    }

    void partnerWeak(shared_ptr<Cycleptr>& ptr) {
        this->weak = ptr;
        cout<<m_name<<" :: "<<ptr->m_name<<endl;
    }

    shared_ptr<Cycleptr> getPartner() {
        return weak.lock();
    }

    string getName() {
        return m_name;
    }
};

weak_ptr<Cycleptr> getWeak() {
    shared_ptr<Cycleptr> lol {new Cycleptr("wolly")};
    return weak_ptr<Cycleptr> {lol};
}

int main() {
    const int x = 1;
    int y = 2 ;

    // int& lref {x}; connot bind lvalue ref with const objects
    int& lref {y}; // works
    // int& lref {10}; connot bing lvalue ref with rvalues

    // All works fine
    // const int& constlref {x};
    // const int& constlref = y;
    const int& constlref = 10;

    // int&& rref {x}; // cannot bind rvalue ref with any lvalue
    // int&& rref = y; // cannot bind rvalue ref with any lvalue
    int&& rref = 9;

    foo(rref); // calls const lvalue ref rather than rvalue ref as rref is now lvalue

    Auto_Ptr<int> ptr1(new int(9)) ;
    Auto_Ptr<int> ptr2 {ptr1} ;
    Auto_Ptr<int> ptr3(new int(10)) ;
    ptr1 = ptr3;

    cout<<"---------------------------------------"<<endl;
    Auto_Ptr<Resource> resource;
    resource = AssignResource();
    cout<<"---------------------------------------"<<endl;

    Name val = func();

    cout<<"---------------------------------------"<<endl;
    // manages objects not shared among 
    unique_ptr<Resource> a {new Resource()};
    unique_ptr<Resource> b {};

    cout<<"A : "<<(a?"not null":"null")<<endl;
    cout<<"B : "<<(b?"not null":"null")<<endl;
    // a = b ; // error as copy semantics are deleted
    b = move(a);
    cout<<"A : "<<(a?"not null":"null")<<endl;
    cout<<"B : "<<(b?"not null":"null")<<endl;

    cout<<"---------------------------------------"<<endl;

    unique_ptr<Name> nam(new Name("Joe"));
    nam->printName();

    auto ptr = make_unique<Name>("Lol");
    ptr->printName();

    auto hollow {createResource()};
    // printSurname(ptr); //error
    // printSurname(move(ptr));
    // now ptr is of no use
    // better way is to just pass the pointer itself
    printSurname(ptr.get());

    Resource* resptr {new Resource()};
    // auto ptrres1 = make_unique<Resource>(resptr); // cannot do this
    unique_ptr<Resource> ptrres(resptr);

    cout<<"----------------------------------------"<<endl;

    Name* pres {new Name("volla")};
    shared_ptr<Name> count {pres};
    shared_ptr<Name> count2 {count};
    {
        Name* loti {new Name("holla")};

        // shared_ptr<Name> count1 {pres}; // wrong way to do this as count and count1 will not be awared of each other
        shared_ptr<Name> count1 {count};
        count1->printName();
        // count2 = loti;
        // count2->printName();
    }
    count->printName();
    count2->printName();

    auto countptr {make_shared<Name>("jolly")};

    cout<<"----------------------------------------"<<endl;

    auto m {make_shared<Cycleptr>("mully")} , n {make_shared<Cycleptr>("bully")};
    // n->partnerStrong(m);
    // m->partnerStrong(n);
    // circular dependancy results in destructors never being called

    n->partnerWeak(m);
    m->partnerWeak(n);

    auto vptr = n->getPartner();
    cout<<vptr->getName()<<endl;
    // remember cannot access elements in weak ptr we need to convert them into shared ptr

    auto pptr {getWeak()};
    cout<<pptr.expired()<<endl;

    weak_ptr<Name> weakCount {count};
    cout<<weakCount.expired()<<endl;

    cout<<"----------------------------------------"<<endl;
}