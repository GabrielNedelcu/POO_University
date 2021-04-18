#include <iostream>
#include <vector>
#include <sstream>


class Policy {
protected:
    bool isChecked;

public:
    virtual void check(const std::string& password) = 0;

    bool getCheck() const {
        return isChecked;
    }
};

class LengthPolicy : public Policy {
private:
    uint16_t minLength;
    uint16_t maxLength;

public:
    LengthPolicy (uint16_t pMin) {
        minLength = pMin;
        maxLength = 255;
    }

    LengthPolicy (uint16_t pMin, uint16_t pMax) {
        minLength = pMin;
        maxLength = pMax;
    }

    void check (const std::string& password) {
        if (password.length() < minLength || password.length() > maxLength) {
            isChecked = false;
        } else {
            isChecked = true;
        }

    }
};

class ClassPolicy : public Policy {
private:
    uint16_t minClassCount;

public:
    ClassPolicy (uint16_t pMinClassCount) {
        minClassCount = pMinClassCount;
    }

    void check (const std::string& password) {
        uint16_t digit = 0;
        uint16_t upper = 0;
        uint16_t lower = 0;
        uint16_t other = 0;
        uint16_t differentClasses = 0;

        for (int i = 0; i < password.length(); i++) {
            if (isdigit(password[i])) {
                digit++;
            } else if (isalpha(password[i])) {
                if (isupper(password[i])) {
                    upper++;
                } else {
                    lower++;
                }
            } else {
                other++;
            }
        }

        if (digit != 0) differentClasses++;
        if (upper != 0) differentClasses++;
        if (lower != 0) differentClasses++;
        if (other != 0) differentClasses++;

        if (differentClasses < minClassCount) {
            isChecked = false;
        } else {
            isChecked = true;
        }
    }
};

class IncludePolicy : public Policy {
private:
    char characterType;

public:
    IncludePolicy (char pChar) {
        characterType = pChar;
    }

    void check (const std::string& password) {
        uint16_t count = 0;

        for (int i = 0; i < password.length(); i++) {
            if ((islower(password[i]) && islower(characterType)) || (isupper(password[i]) && isupper(characterType)) ||
                (isdigit(password[i]) && isdigit(characterType)) || (!isalpha(password[i]) && !isdigit(password[i]) &&
                                                                     !isalpha(characterType) && !isdigit(characterType)))
                count++;
        }

        if (count != 0) {
            isChecked = true;
        } else {
            isChecked = false;
        }

    }
};

class NotIncludePolicy : public Policy {
private:
    char characterType;

public:
    NotIncludePolicy (char pChar) {
        characterType = pChar;
    }

    void check (const std::string& password) {
        uint16_t count = 0;

        for (int i = 0; i < password.length(); i++) {
            if ((islower(password[i]) && islower(characterType)) || (isupper(password[i]) && isupper(characterType)) ||
                (isdigit(password[i]) && isdigit(characterType)) || (!isalpha(password[i]) && !isdigit(password[i]) &&
                                                                     !isalpha(characterType) && !isdigit(characterType)))
                count++;
        }

        if (count != 0) {
            isChecked = false;
        } else {
            isChecked = true;
        }

    }
};

class RepetitionPolicy : public Policy {
private:
    uint16_t maxCount;

public:
    RepetitionPolicy (uint16_t pMaxCount) {
        maxCount = pMaxCount;
    }

    void check (const std::string& password) {
        uint16_t count = 1;
        uint16_t max = 0;
        uint16_t i = 1;

        while (i < password.length()) {
            if (password[i] == password[i-1]) {
                count++;
            } else {
                if(count > max) {
                    max = count;
                }

                count = 1;
            }
            i++;
        }

        if (max > maxCount) {
            isChecked = false;
        } else {
            isChecked = true;
        }
    }
};

class ConsecutivePolicy  : public Policy {
private:
    uint16_t maxCount;

public:
    ConsecutivePolicy  (uint16_t pMaxCount) {
        maxCount = pMaxCount;
    }

    void check (const std::string& password) {
        uint16_t count = 1;
        uint16_t max = 0;
        uint16_t i = 1;

        while (i < password.length()) {
            if (password[i] == password[i-1] + 1) {
                count++;
            } else {
                if(count > max) {
                    max = count;
                }
                count = 1;
            }

            i++;
        }

        if (max > maxCount) {
            isChecked = false;
        } else {
            isChecked = true;
        }

       /*uint16_t  max = 0;

        for (int i = 0; i < password.length(); i++) {
            int tempCount = 1;

            for (int j = i + 1; j < password.length(); j++) {
               if (password[j] != password[i] + 1)
                   break;
                tempCount++;
            }

            if (tempCount > max) {
                max = tempCount;
            }
        }

        if (max > maxCount) {
            isChecked = false;
        } else {
            isChecked = true;
        }*/
    }
};

std::string checkPassword (std::string password, std::vector<Policy*> policies) {
    bool ok = true;

    for (auto it : policies) {
        it->check(password);
        if (it->getCheck() == false) {
            ok = false;
            break;
        }
    }

    if (ok) {
        return "OK";
    } else {
        return "NOK";
    }
        //std::cout << "OK" << std::endl;

        //std::cout << "NOK" << std::endl;
}

int main() {
    int n;
    std::string line;
    std::string password;
    std::string policy;
    uint16_t minLength;
    uint16_t maxLength;
    char characterClass;

    std::vector<Policy*> policies;

    std::cin >> n;
    std::cin.get();

    for (int i = 0; i < n; i++) {
        getline(std::cin, line);
        std::istringstream ss(line);
        ss >> policy;

        if (policy == "length") {
            ss >> minLength;
            if (ss >> maxLength) {
                policies.push_back(new LengthPolicy(minLength, maxLength));
            } else {
                policies.push_back(new LengthPolicy(minLength));
            }
        } else if (policy == "class") {
            ss >> minLength;
            policies.push_back(new ClassPolicy(minLength));
        } else if (policy == "include") {
            ss >> characterClass;
            policies.push_back(new IncludePolicy(characterClass));
        } else if (policy == "ninclude") {
            ss >> characterClass;
            policies.push_back(new NotIncludePolicy(characterClass));
        } else if (policy == "repetition") {
            ss >> maxLength;
            policies.push_back(new RepetitionPolicy(maxLength));
        } else if (policy == "consecutive") {
            ss >> maxLength;
            policies.push_back(new ConsecutivePolicy(maxLength));
        }

    }

    while (std::cin >> password) {
        /*bool ok = true;
        for (auto it : policies) {
            it->check(password);
            if (it->getCheck() == false) {
                ok = false;
                break;
            }
        }

        if (ok)
            std::cout << "OK" << std::endl;
        else
            std::cout << "NOK" << std::endl; */
        std::cout << checkPassword (password, policies) << std::endl;
    }

    return 0;
}