#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <cmath>


using namespace std;

// Function declarations
char toLowerChar(char c);
string toLowerCase(const string &str);
bool equalsIgnoreCase(const string &str1, const string &str2);
string trim(const string &str);
double toRadians(double degrees);
string escapeQuotes(const string &field);

#endif // UTILITIES_H
