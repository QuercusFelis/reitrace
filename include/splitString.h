//A. Groeling - 9/20/20
#ifndef SPLITSTRING_H
#define SPLITSTRING_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
 
// small utility to help parse strings
void splitString(const std::string& str, std::vector<std::string>& cont,
              const char delim = ' ')
{
    std::string token;
    std::istringstream tokenStream(str); 
    while(std::getline(tokenStream, token, delim))
    {
        if(token.size() > 0)
            cont.push_back(token);
    }
}

#endif
