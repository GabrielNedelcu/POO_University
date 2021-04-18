#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>

// BEGIN Clasele voastre aici

class AccessPoint {
private:
    bool mUnlocked;

public:
    AccessPoint() {
        mUnlocked = false;
    }

    bool isUnlocked() {
        return mUnlocked;
    }

    void toggle() {
        mUnlocked = !mUnlocked;
    }

};

class AccessDeniedException : std::exception {

};

class User {
protected:
    std::string mUserId;
    std::set<uint64_t> mCards;
    std::vector<AccessPoint*> mAccessPoints;
    uint32_t mActivity;

public:
    User (const std::string& pUserId) {
        mUserId = pUserId;
        mCards = {};
        mAccessPoints = {};
        mActivity = 0;
    }

    void toggleDoor (AccessPoint* door) {
        if (find(mAccessPoints.begin(), mAccessPoints.end(), door) != mAccessPoints.end()) {
            door->toggle();
            mActivity++;
        } else {
            ///Throw exception
            throw AccessDeniedException();
        }
    }

    void addAccessPoint (AccessPoint* door) {
        if (find(mAccessPoints.begin(), mAccessPoints.end(), door) == mAccessPoints.end()) {
            mAccessPoints.push_back(door);
        }
    }

    void addCard (uint64_t card) {
        if (mCards.find(card) == mCards.end()) {
            mCards.insert(card);
        }
    }

    bool hasCard (uint64_t card) {
        return mCards.find(card) != mCards.end();
    }

    uint32_t countCards () {
        return mCards.size();
    }

    uint32_t getActivity () {
        return mActivity;
    }
};

class AdminUser : public User {
public:
    AdminUser(const std::string& pUserId) :  User (pUserId) {

    }

    void toggleDoor (AccessPoint* door) {
        door->toggle();
        mActivity++;
    }
};

class Database {
private:
    std::map<std::string, User*> mUsers;
    std::unordered_map<uint64_t, AccessPoint> mAccessPoints;

public:
    void addUser(const std::string & id, char type) {
        if (type == 'U') {
            mUsers.insert(std::pair<std::string, User*>(id, new User(id)));
        } else {
            mUsers.insert(std::pair<std::string, User*>(id, new AdminUser(id)));
        }
    }

    void addAccessPoint(uint64_t doorId) {
        mAccessPoints.insert(std::pair<uint64_t, AccessPoint>(doorId, AccessPoint()));
    }

    void addCardToUser(const std::string & userId, uint64_t cardId) {
        mUsers.at(userId)->addCard(cardId);
    }

    void addAccessPointToUser(const std::string & userId, uint64_t doorId) {
        mUsers.at(userId)->addAccessPoint(&mAccessPoints.at(doorId));
    }

    void parseEvent(uint64_t cardId, uint64_t doorId) {
        bool cardExists = false;

        for(auto user : mUsers) {
            if (user.second->hasCard(cardId)) {
                cardExists = true;
                //mAccessPoints.at(doorId).toggle();
                user.second->toggleDoor(&mAccessPoints.at(doorId));
            }
        }

        if (cardExists == false) {
            throw AccessDeniedException();
        }
    }

    uint32_t countUnlockedDoors() {
        uint32_t unlockedDoors = 0;

        for (auto door : mAccessPoints) {
            if (door.second.isUnlocked() == true) {
                unlockedDoors++;
            }
        }

        return unlockedDoors;
    }

    uint32_t countActivity() {
        uint32_t activity = 0;

        for (auto user : mUsers) {
            activity += user.second->getActivity();
        }

        return activity;
    }

    std::vector<std::string> findUsersWithNoCards() {
        std::vector<std::string> usersWithNoCards;

        for (auto user : mUsers) {
            if (user.second->countCards() == 0) {
                usersWithNoCards.push_back(user.first);
            }
        }

        std::sort(usersWithNoCards.begin(), usersWithNoCards.end());

        return usersWithNoCards;
    }

    uint32_t countCards() {
        uint32_t cards = 0;

        for (auto user : mUsers) {
            cards += user.second->countCards();
        }

        return cards;
    }

};


// END Clasele voastre aici

int main() {
    uint32_t n, m, k;
    std::cin >> n >> m >> k;
    Database database;
    while(n--) {
        uint64_t accessPointId;
        std::cin >> accessPointId;
        database.addAccessPoint(accessPointId);
    }
    while(m--) {
        std::string userId;
        char type;
        std::cin >> userId >> type;
        database.addUser(userId, type);
        uint32_t c;
        std::cin >> c;
        while(c--) {
            uint64_t cardId;
            std::cin >> cardId;
            database.addCardToUser(userId, cardId);
        }
        uint32_t u;
        std::cin >> u;
        while(u--) {
            uint64_t accessPointId;
            std::cin >> accessPointId;
            database.addAccessPointToUser(userId, accessPointId);
        }
    }
    uint32_t errors = 0;

    while(k--) {
        uint64_t accessPointId, cardId;
        std::cin >> accessPointId >> cardId;
        try {
            database.parseEvent(cardId, accessPointId);
        }catch(AccessDeniedException & ex) {
            errors++;
        }

    }
    uint32_t subject;
    std::cin >> subject;
    switch(subject) {
        case 1: {
            std::cout << database.countUnlockedDoors();
            break;
        }
        case 2: {
            std::cout << database.countActivity();
            break;
        }
        case 3: {
            auto users = database.findUsersWithNoCards();

            if (users.size() != 0) {
                for(const auto & user : users) std::cout << user << " ";
            } else {
                std::cout << std::endl;
            }

            break;
        }
        case 4: {
            std::cout << database.countCards();
            break;
        }
        case 5: {
            std::cout << errors;
            break;
        }
    }
    return 0;
}