#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

class Spaceship {
private:
    std::string mName;
    int mAttack;
    int mShield;

public:
    Spaceship() {
        mName = "nedefinit";
        mAttack = 0;
        mShield = 0;
    }

    Spaceship (std::string pName, int pAttack, int pShield) {
        mName = pName;
        mAttack = pAttack;
        mShield = pShield;
    }

    Spaceship (const Spaceship &pSpaceship) {
        mName = pSpaceship.mName;
        mAttack = pSpaceship.mAttack;
        mShield = pSpaceship.mShield;
    }

    std::string getName () {
        return mName;
    }

    int getAttack () {
        return mAttack;
    }

    int getShield () {
        return mShield;
    }

    void setName (std::string pName) {
        mName = pName;
    }

    void setAttack (int pAttack) {
        mAttack = pAttack;
    }

    void setShield (int pShield) {
        mShield = pShield;
    }

    Spaceship& operator=(const Spaceship &pSpaceship) {
        mName = pSpaceship.mName;
        mAttack = pSpaceship.mAttack;
        mShield = pSpaceship.mShield;

        return *this;
    }

    Spaceship operator+=(const Spaceship &pSpasceship) {
        mAttack += pSpasceship.mAttack;
        mShield += pSpasceship.mShield;

        return *this;
    }

    Spaceship operator-=(const Spaceship &pSpaceship) {
        mShield -= pSpaceship.mAttack;

        return *this;
    }

    Spaceship operator^(const Spaceship &pSpaceship) {
        Spaceship copySpaceship = pSpaceship;

        while (mShield > 0 && copySpaceship.mShield > 0) {
            *this -= copySpaceship;

            if (mShield > 0) {
                copySpaceship -= *this;
            }
        }

        if (mShield > 0) {
            return *this;
        }

        return copySpaceship;

    }

    bool operator<(const Spaceship &pSpaceship) {
        if ((mAttack + mShield) > (pSpaceship.mAttack+pSpaceship.mShield))
            return true;

        return false;
    }

    void print () {
        std::cout << mName << std::endl;
    }

};

bool comp (Spaceship sp1, Spaceship sp2) {
    return (sp1.getAttack() + sp1.getShield()) > (sp2.getShield() + sp2.getAttack());
}

bool comparator(pair <string, Spaceship>& one, pair <string, Spaceship>& two)
{
    return one.second.getAttack() + one.second.getShield() > two.second.getAttack() + two.second.getShield();
}

int main() {
    int n;
    int k;

    std::string tmpName;
    int tmpShield;
    int tmpAttack;

    std::map<std::string, Spaceship> spaceships;

    std::string command;
    std::string firstSpaceship;
    std::string secondSpaceship;

    std::cin >> n;

    for (int i = 0; i < n; i++){
        std::cin >> tmpName >> tmpAttack >> tmpShield;

        spaceships.insert(std::pair<std::string, Spaceship> (tmpName, Spaceship(tmpName, tmpAttack, tmpShield)));
    }

    std::cin >> k;

    for (int i = 0; i < k; i++) {
        std::cin >> command >> firstSpaceship >> secondSpaceship;

        if (command == "fight") {
            Spaceship result = spaceships.at(secondSpaceship)^spaceships.at(firstSpaceship);
            spaceships.erase(firstSpaceship);
            spaceships.erase(secondSpaceship);
            spaceships[result.getName()] = result;
        } if (command == "transfer") {
            spaceships.at(firstSpaceship)+=spaceships.at(secondSpaceship);
            spaceships.erase(secondSpaceship);
        }

    }
    vector <pair <string, Spaceship> > output(spaceships.begin(), spaceships.end());

    std::sort(output.begin(), output.end(), comparator);

    for (auto it : output) {
        cout << it.first << endl;
    }

    return  0;
}