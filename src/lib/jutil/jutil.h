#ifndef JOSH_H_
#define JOSH_H_

#include <exception>
#include <string>

class JUtil {
public:
    static void checkZero(double v, const std::string& name = "") {
        if (v == 0) {
            if (name.empty())
                throw std::domain_error("Encountered an illegal zero");
            else
                throw std::domain_error("Encountered an illegal zero - " + name);
        }
    }
};

#endif //JOSH_H_
