#include <bits/stdc++.h>


class Car {
protected:
    std::string mType;
    float mConsume;

public:
    virtual void print () = 0;
    virtual void calculateConsume() = 0;

    float getConsume() {
        return mConsume;
    }
};

class Gas: public Car {
private:
    float mGas;

public:
    Gas (float pGas) {
        mGas = pGas;
        mType = "benzina";
    }

    Gas () {
        mGas = 0;
        mType = "nedefinit";
    }

    void print() {
        std::cout << mType << " " << std::fixed << std::setprecision(2) << mGas << std::endl;
    }

    void calculateConsume() {
        mConsume = mGas * 5.8;
    }

};

class Hybrid : public Car {
private:
    float mGas;
    float mBattery;

public:
    Hybrid (float pGas, float pBattery) {
        mGas = pGas;
        mBattery = pBattery;
        mType = "hibrid";
    }

    Hybrid () {
        mGas = 0;
        mBattery = 0;
        mType = "nedefinit";
    }

    void print () {
        std::cout << mType << " " << std::fixed << std::setprecision(2) << mGas << " " << std::fixed << std::setprecision(2) << mBattery << std::endl;
    }

    void calculateConsume() {
        mConsume = mGas * 5.8 + mBattery * 1.0;
    }
};

class Diesel: public Car {
private:
    float mDiesel;

public:
    Diesel() {
        mDiesel = 0;
        mType = "nedefinit";
    }

    Diesel (float pDiesel) {
        mDiesel = pDiesel;
        mType = "diesel";
    }

    void print() {
        std::cout << mType << " " << std::fixed << std::setprecision(2) << mDiesel << std::endl;
    }

    void calculateConsume() {
        mConsume = mDiesel * 6;
    }
};

bool comp(Car* c1, Car* c2) {
    return c1->getConsume() < c2->getConsume();
}

int main() {
    int n;
    std::string type;
    float tmpFuel;
    float tmpBattery;
    std::vector<Car*> cars;

    std::cin >> n;
    for(int i = 0; i < n; i++) {
        std::cin >> type;

        if(type == "benzina") {
            std::cin >> tmpFuel;
            cars.push_back(new Gas(tmpFuel));
        }

        if(type == "diesel") {
            std::cin >> tmpFuel;
            cars.push_back(new Diesel(tmpFuel));
        }

        if(type == "hibrid") {
            std::cin >> tmpFuel >> tmpBattery;
            cars.push_back(new Hybrid(tmpFuel, tmpBattery));
        }
    }

    for (auto it : cars) {
        it->calculateConsume();
    }

    std::sort(cars.begin(), cars.end(), comp);

    for (auto it : cars) {
        it->print();
    }

    return 0;
}