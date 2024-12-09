#include "Utilities.h"

// Function to convert a character to lowercase
char toLowerChar(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c + ('a' - 'A');
    }
    return c;
}

// Function to convert a string to lowercase
string toLowerCase(const string &str)
{
    string lowerStr = str;
    for (size_t i = 0; i < lowerStr.length(); ++i)
    {
        lowerStr[i] = toLowerChar(lowerStr[i]);
    }
    return lowerStr;
}

// Function to compare strings case-insensitively
bool equalsIgnoreCase(const string &str1, const string &str2)
{
    if (str1.length() != str2.length())
        return false;

    for (size_t i = 0; i < str1.length(); ++i)
    {
        if (toLowerChar(str1[i]) != toLowerChar(str2[i]))
            return false;
    }
    return true;
}

// Function to trim leading and trailing whitespace and control characters
string trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// Function to convert degrees to radians
double toRadians(double degrees)
{
    return degrees * M_PI / 180.0;
}

// Escapes double quotes within a field by doubling them and encloses the field in double quotes
string escapeQuotes(const string &field)
{
    string escaped = "";
    for (char c : field)
    {
        if (c == '"')
            escaped += "\"\"";
        else
            escaped += c;
    }
    return "\"" + escaped + "\"";
}
