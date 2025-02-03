//
// Created by andreasjhon on 1/31/25.
//

#ifndef STR_H
#define STR_H

#include <iostream>

class str {

private:
    size_t len;
    char *s;
public:
    str(char t, size_t i);
    str(size_t i);
    str(const char *s);//default constructor
    str();//default constructor
    str(const str &s);//copy constructor
    str(str&& s) noexcept;//move constructor
    //overload operator+=
    str& operator+=(const str &s);
    //overload operator=
    str& operator=(const str &s); //take lvalue
    str& operator=(str&& s) noexcept; //take rvalue
    friend std::ostream& operator<<(std::ostream& os, const str& s);
    friend str operator+(const str& lhs, const str& rhs);
    friend str operator-(const str& lhs,const str& rhs);
    str& operator-=(const str& s);
    //overload operator == and !=
    friend bool operator==(const str& lhs, const str& rhs);
    friend bool operator!=(const str& lhs,const str& rhs);
    friend bool operator<(const str& lhs, const str& rhs);
    friend bool operator>(const str& lhs, const str& rhs);

    //overload operator[]
    char& operator[](size_t i);
    char operator[](size_t i) const;

    friend str low(const str& s);
    friend str up(const str& s);
    str& operator*=(size_t i);
    str invert() const;
    size_t size() const;
    friend void swap(str& lhs,str& rhs);

    ~str() {delete[] s;}
};

#endif //STR_H
