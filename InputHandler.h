#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <string>
#include <limits>
#include "Utilities.h"

using namespace std;

/**
 * Class for handling user input with validation.
 */
class InputHandler
{
public:
    /**
     * Gets a line of input from the user.
     */
    static string getLineInput(const string &prompt);

    /**
     * Converts a string to an integer with validation.
     */
    static int getValidatedInt(const string &prompt, int min = numeric_limits<int>::min(), int max = numeric_limits<int>::max());

    /**
     * Converts a string to a double with validation.
     */
    static double getValidatedDouble(const string &prompt, double min = numeric_limits<double>::lowest(), double max = numeric_limits<double>::max());

    /**
     * Gets a 4-digit year input from the user with validation.
     */
    static int getYearInput(const string &prompt);

    /**
     * Gets a latitude input between -90 and 90.
     */
    static double getLatitudeInput(const string &prompt);

    /**
     * Gets a longitude input between -180 and 180.
     */
    static double getLongitudeInput(const string &prompt);
};

#endif // INPUTHANDLER_H
