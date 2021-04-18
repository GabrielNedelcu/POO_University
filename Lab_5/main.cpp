#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <bits/unique_ptr.h>
#include <iomanip>


class Person {
public:
    std::string mName;
    uint16_t mAge;
    double mSalary;

    Person() {
        mAge = 0;
        mSalary = 0;
        mName = "";
    }

    Person(std::string pName, uint16_t pAge, double pSalary) {
        mName = pName;
        mAge = pAge;
        mSalary = pSalary;
    }

    bool operator==(const Person& pPerson) const {
        return (pPerson.mSalary == mSalary && pPerson.mAge == mAge && pPerson.mName == mName);
    }

    bool operator < (const Person& pPerson) const {
        return mName < pPerson.mName;
    }

    Person* operator = (const Person& pPerson) {
        mName = pPerson.mName;
        mSalary = pPerson.mSalary;
        mAge = pPerson.mAge;

        return this;
    }
};

class Building {
protected:
    std::string mBuildingName;
    std::string mType;
    Person mCoordinator;
    std::vector<Person> mEmployees;
    std::vector<Person> mCitizens;

public:
    Building(std::string pBuildingName, std::string pType) {
        mBuildingName = pBuildingName;
        mType = pType;
    }

    virtual void add(const Person& pPerson) = 0;

    virtual void remove(const Person& pPerson) = 0;

    virtual Building* operator + (const Person& pPerson){
        return nullptr;
    }

    virtual Building* operator - (const Person& pPerson){
        return nullptr;
    }

    virtual Building* operator - (){
        return nullptr;
    }

    std::string getBuildingName() const {
        return mBuildingName;
    }

    std::string getType () const {
        return mType;
    }

    uint16_t getEmployeesSize() const {
        return mEmployees.size();
    }

    uint16_t getCitizensSize() const {
        return mCitizens.size();
    }

    Person getEmployee(uint16_t index) const {
        return mEmployees.at(index);
    }

    Person getCitizen(uint16_t index) const {
        return mCitizens.at(index);
    }

    Person getCoordinator() const {
        return mCoordinator;
    }
};

class CityHall : public Building {
public:
    CityHall(std::string pBuildingName) : Building(pBuildingName, "CityHall"){
        mCitizens.clear();
        mCoordinator = Person();
    }

    Building* operator+(const Person& pPerson) {
        if (mCoordinator.mAge == 0 && mCoordinator.mSalary == 0 && mCoordinator.mName == "") {
            mCoordinator.mAge = pPerson.mAge;
            mCoordinator.mName = pPerson.mName;
            mCoordinator.mSalary = pPerson.mSalary;
        }

        return this;
    }

    Building* operator - () {
        mCoordinator = Person();

        return this;
    }

    void add(const Person& pPerson) {
        mCitizens.push_back(pPerson);
    }

    void remove(const Person& pPerson) {
        for (std::vector<Person>::iterator person = mCitizens.begin(); person != mCitizens.end(); person++) {
            if (*person == pPerson) {
                mCitizens.erase(person);
                break;
            }
        }
    }
};

class Hospital : public Building {
public:
    Hospital(std::string pBuildingName) : Building(pBuildingName, "Hospital"){
        mCitizens.clear();
        mEmployees.clear();
    }

    Building* operator + (const Person& pPerson) {
        mEmployees.push_back(pPerson);

        return this;
    }

    Building* operator - (const Person& pPerson) {
        for (std::vector<Person>::iterator person = mEmployees.begin(); person != mEmployees.end(); person++) {
            if (*person == pPerson) {
                mEmployees.erase(person);
                break;
            }
        }

        return this;
    }

    void add(const Person& pPerson) {
        mCitizens.push_back(pPerson);
    }

    void remove(const Person& pPerson) {
        for (std::vector<Person>::iterator person = mCitizens.begin(); person != mCitizens.end(); person++) {
            if (*person == pPerson) {
                mCitizens.erase(person);
                break;
            }
        }
    }
};


class PoliceStation  : public Building {
public:
    PoliceStation (std::string pBuildingName) : Building(pBuildingName, "PoliceStation"){
        mCitizens.clear();
        mEmployees.clear();
    }

    Building* operator+(const Person& pPerson) {
        mEmployees.push_back(pPerson);

        return this;
    }

    Building*operator-(const Person& pPerson) {
        for (std::vector<Person>::iterator person = mEmployees.begin(); person != mEmployees.end(); person++) {
            if (*person == pPerson) {
                mEmployees.erase(person);
                break;
            }
        }

        return this;
    }

    void add(const Person& pPerson) {
        mCitizens.push_back(pPerson);
    }

    void remove(const Person& pPerson) {
        for (std::vector<Person>::iterator person = mCitizens.begin(); person != mCitizens.end(); person++) {
            if (*person == pPerson) {
                mCitizens.erase(person);
                break;
            }
        }
    }
};

class House : public Building {
private:
    uint16_t mMaxNumber;

public:
    House(std::string pBuildingName, uint16_t pMaxNumber) : Building(pBuildingName, "House") {
        mMaxNumber = pMaxNumber;
        mCitizens.clear();
        mCoordinator = Person();
    }

    Building* operator + (const Person& pPerson) {
        if (mCoordinator.mAge == 0 && mCoordinator.mSalary == 0 && mCoordinator.mName == "") {
            /*mCoordinator.mAge = pPerson.mAge;
            mCoordinator.mName = pPerson.mName;
            mCoordinator.mSalary = pPerson.mSalary;*/

            mCoordinator = pPerson;
        }

        return this;
    }

    Building* operator - () {
        mCoordinator = Person();
        return this;
    }

    void add(const Person& pPerson) {
        uint16_t peopleCount = mCitizens.size();

        if (mCoordinator.mName != "")
            peopleCount++;

        if (peopleCount < mMaxNumber) {
            mCitizens.push_back(pPerson);
        }
    }

    void remove(const Person& pPerson) {
        if (pPerson.mAge >= 18) {
            for (std::vector<Person>::iterator person = mCitizens.begin(); person != mCitizens.end(); person++) {
                if (*person == pPerson) {
                    mCitizens.erase(person);
                    break;
                }
            }
        }
    }

};

class Block : public Building {
private:
    uint16_t mMaxNumberPerFloor;

public:
    Block(std::string pBuildingName, uint16_t pFloors, uint16_t pMaxNumberPerFloor) : Building(pBuildingName, "Block") {
        mMaxNumberPerFloor = pMaxNumberPerFloor;
        mCitizens.clear();
        mCoordinator = Person();

        for(int i = 0; i < pFloors * mMaxNumberPerFloor; i++) {
            mCitizens.push_back(Person());
        }
    }

    Building* operator+(const Person& pPerson) {
        if (mCoordinator.mAge == 0 && mCoordinator.mSalary == 0 && mCoordinator.mName == "") {
            /*mCoordinator.mAge = pPerson.mAge;
            mCoordinator.mName = pPerson.mName;
            mCoordinator.mSalary = pPerson.mSalary;*/

            mCoordinator = pPerson;
        }

        return this;
    }

    Building*operator - () {
        mCoordinator = Person();

        return this;
    }

    void add(const Person& pPerson) {
        for(std::vector<Person>::iterator person = mCitizens.begin(); person != mCitizens.end(); person++) {
            if(person->mAge == 0 && person->mSalary == 0 && person->mName.empty()) {
                *person = pPerson;
                break;
            }
        }
    }

    void remove(const Person& pPerson) {
        if (pPerson.mAge >= 18) {
            for (std::vector<Person>::iterator person = mCitizens.begin(); person != mCitizens.end(); person++) {
                if (*person == pPerson) {
                    *person = Person();
                    break;
                }
            }
        }
    }

};


int main() {

    std::map<std::string, std::unique_ptr<Building>> buildings;
    std::map<std::string, Person> persons;
    std::vector<std::string> housesAndBlocks;
    std::vector<Person> houseOwners;
    std::vector<Person> blockAdministrator;

    std::string command;
    std::string toDo;
    std::string toOperate;
    std::string buildingName;
    uint16_t maxNumber;
    uint16_t floors;
    uint16_t maxNumberPerFloor;
    std::string personName;
    uint16_t personAge;
    double personSalary;
    std::string buildingToAddTo;

    while (getline(std::cin, command)){
        std::istringstream input(command);
        input >> toDo >> toOperate;

        if (toDo == "add") {
            if (toOperate == "CityHall") {
                input >> buildingName;
                buildings.insert(std::pair<std::string, std::unique_ptr<Building>>(buildingName, std::unique_ptr<Building>(new CityHall(buildingName))));
            }

            if (toOperate == "Hospital") {
                input >> buildingName;
                buildings.insert(std::pair<std::string, std::unique_ptr<Building>>(buildingName, std::unique_ptr<Building>(new Hospital(buildingName))));
            }

            if (toOperate == "PoliceStation") {
                input >> buildingName;
                buildings.insert(std::pair<std::string, std::unique_ptr<Building>>(buildingName, std::unique_ptr<Building>(new PoliceStation(buildingName))));
            }

            if (toOperate == "House") {
                input >> buildingName;
                input >> maxNumber;
                buildings.insert(std::pair<std::string, std::unique_ptr<Building>>(buildingName, std::unique_ptr<Building>(new House(buildingName, maxNumber))));
                //houses.push_back(new House(buildingName, maxNumber));
                //housesAndBlocks.push_back(new House(buildingName, maxNumber));
                housesAndBlocks.push_back(buildingName);
            }

            if (toOperate == "Block") {
                input >> buildingName;
                input >> floors >> maxNumberPerFloor;
                buildings.insert(std::pair<std::string, std::unique_ptr<Building>>(buildingName, std::unique_ptr<Building>(new Block(buildingName, floors, maxNumberPerFloor))));
                //blocks.push_back(new Block(buildingName, floors, maxNumberPerFloor));
                //housesAndBlocks.push_back(new Block(buildingName, floors, maxNumberPerFloor));
                housesAndBlocks.push_back(buildingName);
            }

            if (toOperate == "coordinator") {
                input >> personName >> personAge >> personSalary >> buildingToAddTo;
                persons.insert(std::pair<std::string, Person>(personName + buildingToAddTo + "coordinator", Person(personName, personAge, personSalary)));
                *buildings.at(buildingToAddTo) = *(*buildings.at(buildingToAddTo) + persons.at(personName + buildingToAddTo + "coordinator"));
            }

            if (toOperate == "employee") {
                input >> personName >> personAge >> personSalary >> buildingToAddTo;
                persons.insert(std::pair<std::string, Person>(personName + buildingToAddTo + "employee", Person(personName, personAge, personSalary)));
                *buildings.at(buildingToAddTo) = *(*buildings.at(buildingToAddTo) + persons.at(personName + buildingToAddTo + "employee"));
            }

            if (toOperate == "citizen") {
                input >> personName >> personAge >> personSalary >> buildingToAddTo;
                persons.insert(std::pair<std::string, Person>(personName + buildingToAddTo + "citizen", Person(personName, personAge, personSalary)));
                buildings.at(buildingToAddTo)->add(persons.at(personName + buildingToAddTo + "citizen"));
            }
        } else {
            if (toOperate == "coordinator") {
                input >> personName >> buildingToAddTo;
                *buildings.at(buildingToAddTo) = *(-*buildings.at(buildingToAddTo));
            }

            if (toOperate == "employee") {
                input >> personName >> buildingToAddTo;
                *buildings.at(buildingToAddTo) = *(*buildings.at(buildingToAddTo) - persons.at(personName + buildingToAddTo + "employee"));
            }

            if (toOperate == "citizen") {
                input >> personName >> buildingToAddTo;
                buildings.at(buildingToAddTo)->remove(persons.at(personName + buildingToAddTo + "citizen"));
            }
        }
    }

    uint16_t cityHallCount = 0;
    uint16_t policeStationCount = 0;
    uint16_t hospitalCount = 0;
    uint16_t houseCount = 0;
    uint16_t blockCount = 0;
    uint16_t patientCount = 0;
    uint16_t doctorCount = 0;
    uint16_t copCount = 0;
    uint16_t cityHallEmployeeCount = 0;
    uint16_t bustedPeopleCount = 0;
    uint16_t bustedPeopleAge = 0;
    uint16_t mayorCount = 0;

    double doctorSalary = 0.00;
    double copSalary = 0.00;
    double mayorSalary = 0.00;
    double cityHallEmployeeSalary = 0.00;


    for (std::map<std::string, std::unique_ptr<Building>>::iterator building = buildings.begin(); building != buildings.end(); building++) {
        if(building->second->getType() == "CityHall") {
            cityHallCount ++;

            if (building->second->getCoordinator().mName != ""){
                mayorSalary += building->second->getCoordinator().mSalary;
                mayorCount++;
            }
            cityHallEmployeeCount += building->second->getCitizensSize();

            for (int i = 0; i < building->second->getCitizensSize(); i++) {
                cityHallEmployeeSalary += building->second->getCitizen(i).mSalary;
            }
        }

        if(building->second->getType() == "PoliceStation") {
            policeStationCount ++;

            copCount += building->second->getEmployeesSize();

            for (int i = 0; i < building->second->getEmployeesSize(); i++) {
                copSalary += building->second->getEmployee(i).mSalary;
            }

            bustedPeopleCount += building->second->getCitizensSize();

            for (int i = 0; i < building->second->getCitizensSize(); i++) {
                bustedPeopleAge += building->second->getCitizen(i).mAge;
            }
        }

        if(building->second->getType() == "Hospital") {
            hospitalCount ++;
            patientCount += building->second->getCitizensSize();
            doctorCount += building->second->getEmployeesSize();

            for (int i = 0; i < building->second->getEmployeesSize(); i++) {
                doctorSalary += building->second->getEmployee(i).mSalary;
            }
        }

        if(building->second->getType() == "House") {
            houseCount ++;
        }

        if(building->second->getType() == "Block") {
            blockCount ++;
        }
    }

    /**
     * Printout
     */

    if (cityHallCount >= 3 && hospitalCount >= 2 && policeStationCount >= 3 && houseCount >= 8 && blockCount >= 4) {
        std::cout << "Type: Capital" << std::endl;
    } else if (cityHallCount >= 2 && hospitalCount >= 1 && policeStationCount >= 2 && houseCount >= 4 && blockCount >= 1) {
        std::cout << "Type: Town" << std::endl;
    } else {
        std::cout << "Type: Village" << std::endl;
    }

    std::cout << "Number of patients in hospitals: " << patientCount << std::endl;
    if (doctorCount == 0 || doctorSalary == 0){
        std::cout << "Average salary for doctors: 0" << std::endl;
    } else {
        std::cout << "Average salary for doctors: " << std::fixed << std::setprecision(2) << (double)doctorSalary/doctorCount << std::endl;
    }
    if (copCount == 0 || copSalary == 0){
        std::cout << "Average salary for cops: 0" << std::endl;
    } else {
        std::cout << "Average salary for cops: " << std::fixed << std::setprecision(1) << (double)copSalary/copCount << std::endl;
    }
    if (cityHallCount == 0 || mayorSalary == 0) {
        std::cout << "Average salary for mayors: 0" << std::endl;
    } else {
        std::cout << "Average salary for mayors: " << std::fixed << std::setprecision(2) << (double)mayorSalary/mayorCount << std::endl;
    }
    if (cityHallEmployeeCount == 0 || cityHallEmployeeSalary == 0) {
        std::cout << "Average salary for city hall employees: 0" << std::endl;
    } else {
        std::cout << "Average salary for city hall employees: " << std::fixed << std::setprecision(2) << (double)cityHallEmployeeSalary/cityHallEmployeeCount << std::endl;
    }
    if (bustedPeopleCount == 0 || bustedPeopleAge == 0) {
        std::cout << "Average age of busted in police stations: 0" << std::endl;
    } else {
        //double averageAge = (double)bustedPeopleAge/bustedPeopleCount;
        std::cout << "Average age of busted in police stations: " << (double)bustedPeopleAge/bustedPeopleCount << std::endl;
    }

    //std::vector<Person> administrators;

    for (auto bName : housesAndBlocks) {
        if (buildings.at(bName)->getType() == "House") {
            std::cout << "Number of people in House " << buildings.at(bName)->getBuildingName() << ": ";
            uint16_t peopleCount = buildings.at(bName)->getCitizensSize();

            if (buildings.at(bName)->getCoordinator().mName != "")
                peopleCount++;

            std::cout << peopleCount << std::endl;

            if (buildings.at(bName)->getCoordinator().mName != "")
                houseOwners.push_back(buildings.at(bName)->getCoordinator());
        } else {
            std::cout << "Number of people in Block " << buildings.at(bName)->getBuildingName() << ": ";
            uint16_t peopleCount = 0;

            for (int i = 0; i < buildings.at(bName)->getCitizensSize(); i++) {
                if (buildings.at(bName)->getCitizen(i).mName != "")
                    peopleCount++;
            }

            if (buildings.at(bName)->getCoordinator().mName != "")
                peopleCount++;

            std::cout << peopleCount << std::endl;

            if (buildings.at(bName)->getCoordinator().mName != "")
                blockAdministrator.push_back(buildings.at(bName)->getCoordinator());
        }
    }

    std::cout << "Administrators of house and block: ";

    /*if (administrators.size() == 0) {
        std::cout << "Nobody";
    } else {
        for (auto it : administrators) {
            std::cout << it.mName << " ";
        }
    }*/

    int counter = 0;
    for (auto owner : houseOwners) {
        for (auto administrator : blockAdministrator) {
            if (owner == administrator) {
                counter ++;
                std::cout << owner.mName << " ";
            }
        }
    }

    if (counter == 0)
        std::cout << "Nobody";

    return 0;
}