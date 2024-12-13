//
// Created by Uriel Sofer on 12/12/2024.
//

#include "StringUtils.h"

string toUpper(const string& s) {
    string result;

    for (unsigned int i = 0; i < s.length(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            result += (s[i] - 'a' + 'A');
        }
        else
        {
            result += s[i];
        }
    }
    return result;
}

string toLower(const string& s) {
    string result;

    for (unsigned int i = 0; i < s.length(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            result += (s[i] - 'A' + 'a');
        }
        else
        {
            result += s[i];
        }
    }
    return result;
}

char toUpper(const char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 'A';
    }
    return c;
}

char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}
