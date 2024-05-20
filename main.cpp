/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Name: Cynthia Hernandez
 *
 * 
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class PlayingCard {
public:
    PlayingCard(int value)
        : value_(value)
    {
    }

    void show() const {
        cout << valueToString(value_) << "\n";
    }
    int getValue() const {
        return value_;
    }
private:
    int value_;

    string valueToString(int value) const {
        switch (value) {
        case 1:
            return "Ace";
        case 2:
            return "Two";
        case 3:
            return "Three";
        case 4:
            return "Four";
        case 5:
            return "Five";
        case 6:
            return "Six";
        case 7:
            return "Seven";
        case 8:
            return "Eight";
        case 9:
            return "Nine";
        case 10:
            return "Ten";
        case 11:
            return "Jack";
        case 12:
            return "Queen";
        case 13:
            return "King";
        default:
            return "";
        }
    }
};

class CardDeck {
public:
    CardDeck() {
        for (int suit = 0; suit < 4; ++suit) {
            for (int value = 1; value <= 13; ++value) {
                if (value == 1 || value >= 10) { // create cards for Ace and face values
                    deck_.emplace_back(value);
                }
            }
        }
    }
    vector<PlayingCard> draw(int numCards) {
        vector<PlayingCard> hand;
        for (int i = 0; i < numCards; i++) {
            hand.push_back(deck_.back());
            deck_.pop_back();
        }
        return hand;
    }

    void shuffleDeck() {
        random_shuffle(deck_.begin(), deck_.end());
    }

    void display() const {
        for (const auto& card : deck_) {
            card.show();
        }
    }

private:
    vector<PlayingCard> deck_;
};

double calculatePairProbability(int simulations) {
    int pairCount = 0;

    for (int i = 0; i < simulations; i++) {
        CardDeck deck;
        deck.shuffleDeck();
        vector<PlayingCard> hand = deck.draw(4);
        
        for (size_t j = 0; j < hand.size(); j++) {
            for (size_t k = j + 1; k < hand.size(); k++) {
                if (hand[j].getValue() == hand[k].getValue()) {
                    pairCount++;
                    break;
                }
            }
        }
    }

    double probability = static_cast<double>(pairCount) / (simulations * (4 * 3 / 2));
    return probability;
}

double calculateTwoPairProbability(int simulations) {
    int twoPairCount = 0;
    for (int i = 0; i < simulations; ++i) {
        CardDeck deck;
        deck.shuffleDeck();

        vector<PlayingCard> hand;
        for (int j = 0; j < 4; ++j) {
            hand.push_back(deck.draw(1)[0]);
        }

        int pairCount = 0;
        for (int j = 0; j < hand.size(); ++j) {
            for (int k = j + 1; k < hand.size(); ++k) {
                if (hand[j].getValue() == hand[k].getValue()) {
                    ++pairCount;
                }
            }
        }
        if (pairCount == 2) {
            ++twoPairCount;
        }
    }
    double noTwoPairProb = static_cast<double>(simulations - twoPairCount) / simulations;
    return 1.0 - noTwoPairProb;
}

double calculateThreeOfAKindProbability(int simulations) {
    int threeOfAKindCount = 0;

    for (int i = 0; i < simulations; ++i) {
        CardDeck deck;
        deck.shuffleDeck();

        vector<PlayingCard> hand;
        for (int j = 0; j < 4; ++j) {
            hand = deck.draw(3);
        }

        bool hasThreeOfAKind = false;
        for (int j = 0; j < hand.size(); ++j) {
            int count = 0;
            for (int k = 0; k < hand.size(); ++k) {
                if (hand[j].getValue() == hand[k].getValue()) {
                    ++count;
                }
            }
            if (count == 3) {
                hasThreeOfAKind = true;
                break;
            }
        }
        if (hasThreeOfAKind) {
            ++threeOfAKindCount;
        }
    }
    return static_cast<double>(threeOfAKindCount) / simulations;
}

double calculateFourOfAKindProbability(int simulations) {
    int fourOfAKindCount = 0;
    for (int i = 0; i < simulations; ++i) {
        CardDeck deck;
        deck.shuffleDeck();

        vector<PlayingCard> hand;
        for (int j = 0; j < 4; ++j) {
            hand = deck.draw(3);
        }

        int matchCount = 1;
        for (int j = 0; j < hand.size(); ++j) {
            for (int k = j + 1; k < hand.size(); ++k) {
                if (hand[j].getValue() == hand[k].getValue()) {
                    ++matchCount;
                }
            }
        }
        if (matchCount == 4) {
            ++fourOfAKindCount;
        }
    }
    return static_cast<double>(fourOfAKindCount) / simulations;
}

int main() {
    CardDeck deck;
    deck.shuffleDeck();
    vector<PlayingCard> hand = deck.draw(4);

    int simulations = 100000;
    double pairProbability = calculatePairProbability(simulations) * 100;
    double twoPairProbability = calculateTwoPairProbability(simulations) * 100;
    double threeOfAKindProbability = calculateThreeOfAKindProbability(simulations) * 100;
    double fourOfAKindProbability = calculateFourOfAKindProbability(simulations) * 100;
    
    cout << "Probability of getting a pair: " << pairProbability << "%" << endl;
    cout << "Probability of getting 2 pairs: " << twoPairProbability << "%" << endl;
    cout << "Probability of getting three of a kind: " << threeOfAKindProbability << "%" << endl;
    cout << "Probability of getting four of a kind: " << fourOfAKindProbability << "%" << endl;
    return 0;
}
