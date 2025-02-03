//
// Created by andreasjhon on 1/31/25.
//

#include <cstring>
#include <algorithm>
#include "str.h"

str::str(char t,size_t i)
    :len(i), s(new char[len + 1]) {
    for (size_t j {}; j < i; j++)
        s[j] = t;
    s[i] = '\0';
}
str::str(size_t i)
    :len(i), s(new char[i]){
}
str::str(const char *s)
    :len(std::strlen(s)), s(new char[len + 1]) {
    std::strcpy(this->s,s);
}
str::str()
    :len(0), s(new char[1]) {
    *s = '\0';
}
str::str(const str &s)
    :len(s.len), s(new char[len + 1]) {
    std::strcpy(this->s,s.s);
}
str::str(str&& s) noexcept
    :len(s.len), s(s.s) {
    s.len = 0;
    s.s = new char[1];
    *s.s = '\0';
}
std::ostream &operator<<(std::ostream &os, const str &s) {
    os << s.s;
    return os;
}
str operator+(const str &lhs, const str &rhs) {
    size_t totalLen {lhs.len + rhs.len};
    str temp(totalLen + 1);
    std::strcpy(temp.s,lhs.s);
    std::strcat(temp.s,rhs.s);
    return temp;
}
str& str::operator+=(const str &s) {
    size_t totalLen {this->len + s.len};
    char* temp {new char[totalLen + 1]};
    std::strcpy(temp,this->s);
    std::strcat(temp,s.s);

    delete[] this->s;
    this->s = temp;
    this->len = totalLen;
    return *this;
}
char& str::operator[](size_t i) {
    return s[i];
}
str& str::operator=(const str &s) { //overload operator= with deep copy with support for chaining
    if(this == &s) //if users assign this to itself, just return reference to this
        return *this;
    //otherwise, deep copy's about to happen
    delete[] this->s; //delete this.s
    char* temp {new char[s.len + 1]}; //create new space for copy
    std::strcpy(temp,s.s); //copy *s.s to *temp
    this->s = temp; //reassign this.s to temp
    this->len = s.len; //reassign this.ln to s.len
    return *this; //return reference to this
}
void swap(str& lhs,str& rhs) { //method for swapping
    std::swap(lhs.len,rhs.len);
    std::swap(lhs.s,rhs.s);
}
str& str::operator=(str&& s) noexcept { //overload operator= with move semantics with support for chaining
    if (this == &s) //if users assign this to itself, just return reference to this
        return *this;
    swap(*this,s);
    return *this;
}
size_t str::size() const { //return length of the string
    return len;
}
bool operator==(const str &lhs, const str &rhs) {
    return std::strcmp(lhs.s,rhs.s) == 0;
}
char str::operator[](size_t i) const {
    return s[i];
}
str& str::operator*=(size_t i) {
    size_t totalLen {this->len * i};
    char* temp {new char[totalLen + 1]};

    for (size_t j {}; j < i; j++) {
        std::memcpy(temp + (j * this->len),this->s,this->len);
    }

    delete[] this->s;
    this->s = temp;
    this->len = totalLen;

    return *this;
}
str str::invert() const {
    str temp(this->len + 1);

    for (size_t j {}; j < this->len; j++) {
        temp.s[j] = islower(this->s[j]) ? std::toupper(this->s[j]) : std::tolower(this->s[j]);
    }
    temp.s[this->len] = '\0';

    return temp;
}
bool operator!=(const str& lhs,const str& rhs) {
    return (!operator==(lhs,rhs));
}
str low(const str& s){
    str temp(s.len + 1);
    for (size_t j {}; j < s.len; j++) {
        temp.s[j] = std::tolower(s.s[j]);
    }
    return temp;
}
bool operator<(const str& lhs, const str& rhs) {
    return (std::strcmp(lhs.s,rhs.s) < 0);
}
bool operator>(const str& lhs, const str& rhs) {
    return !(operator<(lhs,rhs));
}
str operator-(const str& lhs,const str& rhs) {
    const char* first = lhs.s;
    const char* second = rhs.s;
    //lhs must be longer than rhs, order doesn't matter
    //doesn't follow arithmatic rules for substraction, example : 5 - 2 = 3 and 2 - 5 = -3
    if (rhs.len > lhs.len)
        std::swap(first,second);

    const char* found {std::strstr(first,second)};
    //if considering substring found
    if (found != nullptr) {
        //ex : you wanna remove "at" in "i study maths at school"
        //preLen is the length of "i study maths "
        size_t preLen = std::strlen(first) - std::strlen(found);
        //second_len is the length of "at"
        size_t second_len {std::strlen(second)};
        //from "at school" + second_len, we'll get " school"
        const char* lastFound {found + second_len};
        //we'll make space for "i study maths " + " school" + '\0'
        str temp(preLen + std::strlen(lastFound) + 1);
        //we'll copy "i study maths "
        std::memcpy(temp.s,first,preLen);
        //if the sentence is not end, we continue copying " school\0"
        if (*lastFound != '\0')
            std::strcpy(temp.s + preLen,first + preLen + second_len);
        //we'll continue with recursive to find similar keyword
        return operator-(temp,str(second));
    }
   return str(first);
}
str &str::operator-=(const str &s) {
    const char* found {std::strstr(this->s,s.s)};

    size_t preLen {std::strlen(this->s) - std::strlen(found)};

    if (found != nullptr) {
        size_t second_len {std::strlen(s.s)};
        const char* lastFound {found + second_len};
        char* temp {new char[preLen + std::strlen(lastFound) + 1]};
        std::memcpy(temp,this->s,preLen);
        if (*lastFound != '\0')
            std::strcpy(temp + preLen,this->s + preLen + second_len);
        delete[] this->s;
        this->s = temp;
        this->len = preLen + second_len;
        return *this;
    }
    return *this;
}
str up(const str& s){
    str temp(s.len + 1);
    for (size_t i {}; i < s.len; i++) {
        temp.s[i] = std::toupper(s.s[i]);
    }
    return temp;
}








