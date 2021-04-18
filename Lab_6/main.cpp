#include <bits/stdc++.h>

std::vector<std::string> gAllowedColors {"rosu", "negru", "romb", "trefla"};

class Card {
public:
    uint16_t mCardNumber;
    std::string mCardColor;

    Card (uint16_t pCardNumber, std::string pCardColor) {
        mCardNumber = pCardNumber;
        mCardColor = pCardColor;
    }

    Card () {
        mCardNumber = 0;
        mCardColor = "";
    }

    bool operator == (const Card& rhs) const {
        return (mCardNumber == rhs.mCardNumber && mCardColor == rhs.mCardColor);
    }

    void operator = (const Card& rhs) {
        mCardColor = rhs.mCardColor;
        mCardNumber = rhs.mCardNumber;
    }

    bool checkCard() {
        if (mCardNumber < 2 || mCardNumber > 14) {
            return false;
        }

        if (std::find(gAllowedColors.begin(), gAllowedColors.end(), mCardColor) == gAllowedColors.end()) {
            return false;
        }
        return true;
    }

    void print() {
        std::cout << mCardNumber << "," << mCardColor << std::endl;
    }
};

class Player {
public:
    std::string mName;
    float mStack;
    uint16_t roundCardsTotal;
    bool hasLostRound;

    Player (std::string pName, float pStack) {
        mName = pName;
        mStack = pStack;
        roundCardsTotal = 0;
        hasLostRound = false;
    }

    void print () {
        std::cout << mName << ": " << mStack << std::endl;
    }

    void resetRound() {
        roundCardsTotal = 0;
        hasLostRound = false;
    }

};

void switchCards (std::vector<Card*>& deck, uint16_t firstIndex, uint16_t secondIndex) {
    Card* tmpCard = new Card();

    tmpCard = deck.at(firstIndex);
    deck.at(firstIndex) = deck.at(secondIndex);
    deck.at(secondIndex) = tmpCard;
}

void generateDeck (std::vector<Card*>& deck) {
    for(int j = 0; j < 4; j++) {
        for (int i = 2; i <= 14; i++) {
            if (i != 11)
                deck.push_back(new Card(i, gAllowedColors.at(j)));
        }
    }
}

void shuffleDeck (std::vector<Card*>& deck, uint16_t af, uint16_t xf, uint16_t cf,
                  uint16_t as, uint16_t xs, uint16_t cs) {
    uint16_t firstIndex[51];
    uint16_t secondIndex[51];

    firstIndex[0] = xf;
    secondIndex[0] = xs;

    for (int i = 1; i <= 50; i++) {
        firstIndex[i] = (af * firstIndex[i-1] + cf) % deck.size();
        secondIndex[i] = (as * secondIndex[i-1] + cs) % deck.size();

        switchCards(deck, firstIndex[i], secondIndex[i]);
    }
}

void simulateBlackJackRound (std::vector<Card*>& deck, std::vector<Player*>& players) {
    uint16_t cardCount = 1;
    uint16_t dealerCardCount = 0;
    uint16_t firstCard;
    uint16_t secondCard;

    for (auto player : players) {
        firstCard =  deck.at(cardCount)->mCardNumber;
        secondCard = deck.at(cardCount - 1)->mCardNumber;

        if (firstCard > 10) firstCard = 10;
        if (secondCard > 10) secondCard = 10;

        player->roundCardsTotal = firstCard + secondCard;
        cardCount += 2;
    }

    firstCard =  deck.at(cardCount)->mCardNumber;
    secondCard = deck.at(cardCount - 1)->mCardNumber;

    if (firstCard > 10) firstCard = 10;
    if (secondCard > 10) secondCard = 10;

    dealerCardCount = firstCard + secondCard;

    cardCount++;

    bool dealerLost = false;

    for (auto player : players) {
        if (player->roundCardsTotal <= 16) {
            while (player->roundCardsTotal <= 16) {
                firstCard = deck.at(cardCount)->mCardNumber;

                if (firstCard > 10) firstCard = 10;
                player->roundCardsTotal += firstCard;
                cardCount++;
            }
        }

        if (player->roundCardsTotal > 21) {
            player->hasLostRound = true;
        }
    }

    if (dealerCardCount <= 16) {
        while (dealerCardCount <= 16) {
            firstCard = deck.at(cardCount)->mCardNumber;

            if (firstCard > 10) firstCard = 10;
            dealerCardCount += firstCard;
            cardCount++;
        }
    }

    if (dealerCardCount > 21) {
        for (auto player : players) {
            if (player->hasLostRound == false) {
                player->mStack += 10;
            } else {
                player->mStack -= 10;
            }
        }
    }

    if(dealerCardCount >= 17 && dealerCardCount <=21) {
        for (auto player : players) {
            if (player->roundCardsTotal > dealerCardCount && player->hasLostRound == false) {
                player->mStack += 10;
            } else if (player->roundCardsTotal < dealerCardCount || player->hasLostRound == true) {
                player->mStack -= 10;
            }
        }
    }

    for (std::vector<Player*>::iterator player = players.begin(); player != players.end(); ) {
        if ((*player)->mStack < 10) {
            player = players.erase(player);
        } else {
            ++player;
        }
    }

}



int main() {
    std::string line;
    std::string command;
    std::string cardColor;
    char c;

    uint16_t cardNumber;

    std::vector<Card*> deck;

    std::getline(std::cin, command);

    if (command == "check_cards") {
        bool deckMasluit = false;
        bool blackJackReady = false;

        while (std::getline(std::cin, line)) {
            std::istringstream input(line);

            input >> cardNumber >> c >> cardColor;

            Card* tmpCard = new Card(cardNumber, cardColor);

            if (!tmpCard->checkCard()) {
                deckMasluit = true;
            }
            if (std::find(deck.begin(), deck.end(), tmpCard) != deck.end()){
                blackJackReady = true;
            }
            deck.push_back(tmpCard);
        }

        if (deck.size() != 52) {
            blackJackReady = true;
        }

        if (deckMasluit == true) {
            std::cout << "Pachet masluit" << std::endl;
        } else {
            if (blackJackReady == true) {
                std::cout << "Pregatit pentru Blackjack" << std::endl;
            } else {
                std::cout << "Pachet OK" << std::endl;
            }

        }
    }

    if (command == "shuffle_cards") {
        uint16_t af;
        uint16_t xf;
        uint16_t cf;
        uint16_t as;
        uint16_t xs;
        uint16_t cs;

        std::getline(std::cin,line);
        std::istringstream firstLine (line);
        std::getline(std::cin,line);
        std::istringstream secondLine (line);

        firstLine >> af >> cf >> xf;
        secondLine >> as >> cs >> xs;

        std::string second_line;

        while (std::getline(std::cin, second_line)) {
            std::istringstream input(second_line);
            input >> cardNumber >> c >> cardColor;
            deck.push_back(new Card(cardNumber, cardColor));
        }

        shuffleDeck(deck, af, xf, cf, as, xs, cs);

        for (auto card : deck) {
            card->print();
        }
    }

    if (command == "play_game") {
        uint16_t noPlayers;
        std::vector<Player*> players;
        std::string playerName;
        float playerStack;

        uint16_t af;
        uint16_t xf;
        uint16_t cf;
        uint16_t as;
        uint16_t xs;
        uint16_t cs;

        std::cin >> noPlayers;
        std::cin.get();

        for ( int i = 0; i < noPlayers; i++) {
            std::getline(std::cin, line);
            std::istringstream playerInfo (line);

            playerInfo >> playerName >> playerStack;

            players.push_back(new Player(playerName, playerStack));
        }

        generateDeck(deck);

        while(std::getline(std::cin, line)) {
            if (line != "") {
                std::istringstream input (line);
                input >> af >> cf >> xf >> as >> cs >> xs;

                shuffleDeck(deck, af, xf, cf, as, xs, cs);

                for (auto player : players) {
                    player->resetRound();
                }

                simulateBlackJackRound(deck, players);
            }
        }

        for (auto player : players) {
            player->print();
        }
    }
    return 0;
}