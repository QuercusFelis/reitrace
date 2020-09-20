//A. Groeling - 9/20/20
#ifndef SPLITSTRING_H
#define SPLITSTRING_H

#include <string>
#include <algorithm>
#include <iterator>
 
// small utility to help parse strings
template <class Container>
void splitString(const std::string& str, Container& cont,
              const std::string& delims = " ")
{
    std::size_t current, previous = 0;
    current = str.find_first_of(delims);
    while (current != std::string::npos) {
        cont.push_back(str.substr(previous, current - previous));
        previous = current + 1;
        current = str.find_first_of(delims, previous);
    }
    cont.push_back(str.substr(previous, current - previous));
}

#endif
