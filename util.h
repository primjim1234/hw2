#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <set>
#include <algorithm>

std::string convToLower(std::string src);
std::set<std::string> parseStringToWords(std::string rawWords);

template <typename T>
std::set<T> setIntersection(const std::set<T>& s1, const std::set<T>& s2)
{
    std::set<T> result;
    typename std::set<T>::iterator it1 = s1.begin();
    typename std::set<T>::iterator it2 = s2.begin();
    while(it1 != s1.end() && it2 != s2.end()){
        if(*it1 < *it2) ++it1;
        else if(*it2 < *it1) ++it2;
        else{
            result.insert(*it1);
            ++it1; ++it2;
        }
    }
    return result;
}

template <typename T>
std::set<T> setUnion(const std::set<T>& s1, const std::set<T>& s2)
{
    std::set<T> result = s1;
    result.insert(s2.begin(), s2.end());
    return result;
}

std::string &ltrim(std::string &s);
std::string &rtrim(std::string &s);
std::string &trim(std::string &s);

#endif
