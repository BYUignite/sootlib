/**
 * Josh Bedwell - June 2021
 *
 * This file contains utility functions written by Josh Bedwell
 */

#ifndef JUTIL_H_
#define JUTIL_H_

#include <exception>
#include <string>

/**
 * A wrapper class for the static utility functions
 */
class JUtil {
public:

    /**
     * A function that will throw an error if the given value is zero
     *
     * @param v value to check
     * @param name an optional parameter to add to the exception text to make it identifiable
     */
    static void checkZero(double v, const std::string& name = "") {
        if (v == 0) {
            if (name.empty())
                throw std::domain_error("Encountered an illegal zero");
            else
                throw std::domain_error("Encountered an illegal zero - " + name);
        }
    }
};

#endif //JUTIL_H_
