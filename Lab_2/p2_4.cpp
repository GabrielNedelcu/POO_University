#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>

class Item {
private:
    std::string m_object;
    float m_price;
public:
    Item() {

    }

    Item(std::string p_object, float p_price) {
        m_object = p_object;
        m_price = p_price;
    }

    std::string getObject() {
        return m_object;
    }

    float getPrice() {
        return m_price;
    }

};

class Room {
private:
    unsigned int m_number;
    std::vector<Item> m_valuables;
public:
    Room() {

    }

    Room(int p_number) {
        m_number = p_number;
    }

    unsigned int getNumber() {
        return m_number;
    }

    unsigned int getValuablesSize () {
        return m_valuables.size();
    }

    Item getValuable(unsigned int index) {
        return *(m_valuables.begin()+index);
    }

    void add(Item toAdd) {
        m_valuables.push_back(toAdd);
    }

};

class Hotel {
private:
    std::string m_name;
    std::string m_street;
    std::string m_city;
    std::vector<Room> m_rooms;
public:
    Hotel() {

    }

    Hotel(std::string p_name, std::string p_street, std::string p_city) {
        m_name = p_name;
        m_street = p_street;
        m_city = p_city;
    }

    std::string getName() {
        return m_name;
    }

    std::string getStreet() {
        return m_street;
    }

    std::string getCity() {
        return m_city;
    }

    unsigned int getRoomsSize() {
        return m_rooms.size();
    }

    Room getRoom(unsigned int index) {
        return *(m_rooms.begin() + index);
    }

    void add(Room toAdd) {
        m_rooms.push_back(toAdd);
    }
};

float getRoomPrice(Room room) {
    float total;
    total = 0;

    for (int i = 0; i < room.getValuablesSize(); i++) {
        total += room.getValuable(i).getPrice();
    }

    return total;
}

float getHotelPrice(Hotel hotel) {
    float total;
    total = 0;

    for(int i = 0; i < hotel.getRoomsSize(); i++) {
        total += getRoomPrice(hotel.getRoom(i));
    }

    return total;
}

int main() {
    std::string line;
    std::string tmpStreet;
    std::string tmpCity;
    std::string tmpHotelName;
    std::string tmpValuable;
    int tmpRoomNumber;
    int n;
    float tmpValuablePrice;

    /**
     * hotels:
     * first -> string (strada+oras+hotel)
     * second -> Hotel (hotelul respectiv)
     */

    std::map<std::string, Hotel> hotels;

    /**
     * streets:
     * first -> string (strada+oras)
     * second -> float (suma tuturor bunurilor din hotelurile de pe aceasta strada)
     */

    std::map<std::string, float> streets;

    while (std::getline(std::cin, line)){

        std::istringstream data(line);

        data >> tmpStreet >> tmpCity >> tmpHotelName >> tmpRoomNumber >> n;

        std::string hotelIdentifier = tmpStreet + "_" + tmpCity + "_" + tmpHotelName;

        Hotel tmpHotel(tmpHotelName, tmpStreet, tmpCity);

        Room tmpRoom(tmpRoomNumber);
        for (int i = 0; i < n; i++) {
            data >> tmpValuable >> tmpValuablePrice;
            Item tmpItem(tmpValuable, tmpValuablePrice);
            tmpRoom.add(tmpItem);
        }

        if (hotels.find(hotelIdentifier) == hotels.end()) {
            tmpHotel.add(tmpRoom);
            hotels.insert(std::pair<std::string, Hotel>(hotelIdentifier, tmpHotel));
        } else {
            hotels.find(hotelIdentifier)->second.add(tmpRoom);
        }

        std::string streetCity = hotels.find(hotelIdentifier)->second.getStreet() + " " + hotels.find(hotelIdentifier)->second.getCity();

        if (streets.find(streetCity) == streets.end()) {
            streets.insert(std::pair<std::string, float>(streetCity, getRoomPrice(tmpRoom)));
        } else {
            streets.find(streetCity)->second += getRoomPrice(tmpRoom);
        }
    }

    float maxPrice = 0;
    Hotel maxHotel;

    for (auto it : hotels) {
        if (getHotelPrice(it.second) > maxPrice) {
            maxPrice = getHotelPrice(it.second);
            maxHotel = it.second;
        }
    }

    std::cout << maxHotel.getName() << " " << std::fixed << std::setprecision(2) << maxPrice << std::endl;

    float maxPriceStreet;
    maxPriceStreet = 0;
    std::string streetName;

    for (auto it : streets) {
        if (it.second > maxPriceStreet) {
            maxPriceStreet = it.second;
            streetName = it.first;
        }
    }

    std::cout << streetName << " " << maxPriceStreet;


    return 0;
}
