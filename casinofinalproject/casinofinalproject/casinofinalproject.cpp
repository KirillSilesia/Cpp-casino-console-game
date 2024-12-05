#include <iostream>     // for for std::wcout
#include <string>       // for using string
#include <cstdlib>      
#include <ctime>
#include <fcntl.h>      // for _setmode
#include <io.h>         // for _setmode
#include <stdio.h>      // for _fileno
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <array>




using namespace std;

string name; // holds players's name
int balance; // holds player's current balance
int bet; // holds player's betting aammount
char guess; // holds player's guess
int guessroulette;
int dice; // hold's right guess
int randomcolour;
char colourofroulette;
char choise; // hold's choise of continuing the game
char choiseingame;
char choiseofcolour;
int total_win = 0; // hold's player's total ammount of winning
int x; // integer for switch operator
string spin; // string for start playing one-armed bandit
bool result; // bool to check if the input is corect
const wchar_t* symbolsArray[6] = { L"\u2665", L"\u03A9", L"7", L"\u263B", L"\u2663", L"\u2660" };  // hold's all possible symbols for roulette
char rouletteArray[37] = { '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '0' };
char playerArray[1];
wstring randomArray[3];  // hold's the combination of symbols player can get
string take; // string for start playing blackjack
int DealerHand[5]; // maximum ammount of cards for dealer
int PlayerHand[5]; // maximum ammount of cards for player
int PlayerHandSize = 0; // ammount of cards player has
int DealerHandSize = 0; // ammount of cards dealer has
int PlayerSum; // sum of cards player has
int DealerSum; // sum of cards dealer has
bool DealerDone; // logical function that stops dealer from getting more cards
bool PlayerDone; // logical function to stop player from getting more cards
char Hit; // char to hold player's choise of getting more cards
char Stand; // char for holding player's choise of not getting anymore cards
bool EndGame = false; //logical function to determine whether game is ended or not



void CentreWord(string str)
{
    int padding = (80 - str.size()) / 2;

    // Print underscores before the string
    for (int i = 0; i < padding; ++i)
    {
        cout << ' ';
    }


    cout << str;


    for (int i = 0; i < padding; ++i)
    {
        cout << ' ';
    }

    cout << std::endl;
}

void CentreInt(int num)
{

    string str = to_string(num);

    int padding = (80 - str.size()) / 2;


    for (int i = 0; i < padding; ++i)
    {
        cout << ' ';
    }


    cout << num;


    for (int i = 0; i < padding; ++i)
    {
        cout << ' ';
    }

    cout << std::endl;
}



void DrawLine(int n, char symbol)
{
    for (int i = 0; i < n; i++)
        cout << symbol;
    cout << endl;
}

void RulesOfTheGame1()
{
    system("cls");
    cout << endl;
    DrawLine(60, '_');
    CentreWord("RULES OF THE GAME");
    DrawLine(60, '_');
    CentreWord("CHOOSE A TYPE OF BET");
    cout << endl;
    CentreWord("IF YOU WIN IN STRAIGHT UP YOU WIN 35 TIMES MORE");
    cout << endl;
    CentreWord("IF YOU WIN IN COLOUR YOU WIN 2 TIMES MORE");
    cout << endl;
    CentreWord("IF YOU WIN IN DOZEN YOU WIN 3 TIMES MORE");
    cout << endl;
    CentreWord("IF YOU WIN IN ODD YOU WIN 2 TIMES MORE");
    cout << endl;
    CentreWord("IF YOU WIN IN EVEN YOU WIN 2 TIMES MORE");
    cout << endl;
    CentreWord("IF YOU GUESS ZERO OR GREEN YOU WIN A JACKPOT(TIMES 100)");
    cout << endl;
    CentreWord("IF YOU DON'T WIN YOU LOSE YOUR BET");
    DrawLine(60, '_');
}

void RulesOfTheGame3()
{
    system("cls");
    cout << endl;
    DrawLine(60, '_');
    CentreWord("RULES OF THE GAME");
    DrawLine(60, '_');
    CentreWord("IF YOU GET THREE HEARTS YOUR BET MULTIPLIES BY 3");
    cout << endl;
    CentreWord("IF YOU GET THREE OMEGAS YOUR BET MULTIPLIES BY 5");
    cout << endl;
    CentreWord("IF YOU GET 777 YOUR BET MULTIPLIES BY 10");
    cout << endl;
    CentreWord("IF YOU GET OTHER TRIPLED COMBINATIONS YOUR BET MULTIPLIES BY 2");
    cout << endl;
    CentreWord("IN ALL OTHER CASES YOU LOSE YOUR BET");
    DrawLine(60, '_');
}

void RulesOfTheGame2()
{
    system("cls");
    cout << endl;
    DrawLine(60, '_');
    CentreWord("RULES OF THE GAME");
    DrawLine(60, '_');
    CentreWord("GOAL OF THE GAME IS TO BEAT COMPUTER BY GETTING AS CLOSE TO 21 POINTS AS POSSIBLE");
    cout << endl;
    CentreWord("IF YOU WIN YOU GET 5 TIMES MORE THAN YOU BET");
    cout << endl;
    CentreWord("IF YOU GET 21 POINTS YOU GET 10 TIMES MORE THAN YOU BET");
    cout << endl;
    CentreWord("IF YOU AND DEALER HAAVE THE SAME AMMOUNT OF POINTS YOU GET YOUR BET");
    DrawLine(60, '_');
}



void DrawLine(int n, char symbol);
void RulesOfTheGame1();
void RulesOfTheGame2();
void RulesOfTheGame3();
void CentreWord(string);
void CentreInt(int num);

void displayTopPlayers(const string& filename);



class Player {
private:
    string name;
    int balance;
    int totalWin;

public:
    Player(const string& playerName, int playerBalance, int total_win) : name(playerName), balance(playerBalance), totalWin(total_win) {}

    const string& getName() const { return name; }
    int getBalance() const { return balance; }
    int getTotalWin() const { return totalWin; }

    void updateBalance(int amount) { balance = amount; }
    void updateTotalWin(int amount) { totalWin += amount; }
};

void writeTopPlayersToFile(const vector<Player>& players, const string& filename) {
    ofstream file(filename, ios::app); // Open for writing, append to the end of the file
    if (file.is_open()) {
        for (const auto& player : players) {
            file << player.getName() << "," << player.getBalance() << "," << player.getTotalWin() << endl;
        }
    }
    else {
        cerr << "The file cannot be opened for writing." << endl;
    }
}





void updateTopPlayersFile(Player player, const string& filename) {

    ifstream checkFile(filename);
    if (checkFile.good())
    {
        checkFile.close();
        vector<Player> existingPlayers;
        string line;
        ifstream inputFile(filename);
        while (getline(inputFile, line))
        {
            string playerName = line.substr(0, line.find(','));
            int balance = stoi(line.substr(line.find(',') + 1, line.rfind(',') - line.find(',') - 1));
            int totalWin = stoi(line.substr(line.rfind(',') + 1));

            // Player not found in the updated list, add it to existing players
            existingPlayers.push_back(Player(playerName, balance, totalWin));
        }
        inputFile.close();


        existingPlayers.push_back(Player(player.getName(), player.getBalance(), player.getTotalWin()));
        sort(existingPlayers.begin(), existingPlayers.end(), [](const Player& a, const Player& b)
            { return a.getTotalWin() > b.getTotalWin(); });

        // Write the merged and sorted player list to the file
        ofstream outputFile(filename, ios::trunc);
        for (const auto& player : existingPlayers)
        {
            outputFile << player.getName() << "," << player.getBalance() << "," << player.getTotalWin() << endl;
        }
        outputFile.close();
    }
    else {
        // File does not exist, write players directly to the file
        ofstream outputFile(filename);

        outputFile.close();
    }
}

void displayTopPlayers(const string& filename) {
    ifstream file("top_players.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cerr << "The file cannot be opened for reading." << endl;
    }
}


vector<Player> topPlayers;




class Game {
public:
    virtual void play(Player& player, int& total_win) = 0;
};

class GuessTheNumber : public Game {
private:
    vector<Player>& players;
public:
    GuessTheNumber(vector<Player>& players) : players(players) {}

    void play(Player& player, int& total_win) override {
        CentreWord("WOULD YOU LIKE TO PLAY?(y/n)");
        cin >> choise;

        while (choise != 'Y' && choise != 'y' && choise != 'n' && choise != 'N')
        {
            cout << "Maybe you have mispelled, try again" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            CentreWord("WOULD YOU LIKE TO PLAY?(y/n)");
            cin >> choise;
        }



        system("cls");
        RulesOfTheGame1();
        CentreWord("YOUR BALANCE IS : ");
        CentreInt(balance);

        do {
            cout << name << ", how much would you like to bet? ";
            cin >> bet;
            if (cin.fail() || bet > balance || bet <= 0) {
                cout << "Invalid bet! Please enter a valid positive integer lower than your balance." << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            }
        } while (cin.fail() || bet > balance || bet <= 0);
        balance -= bet;

        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        while (choiseingame != '6') { // Loop indefinitely until user decides to exit
            CentreWord("DO YOU WANT TO BET ON A STRAIGHT UP(ONE NUMBER)(1), COLOUR(2), DOZEN(1,2 OR 3 DOZEN)(3), ODD(4) OR ON AN EVEN(5)?");
            CentreWord("TYPE '6' TO EXIT");
            cin >> choiseingame;


            switch (choiseingame) {
            case('1'): {
                do {
                    do {
                        cout << "Guess a number between 1 and 37 : ";
                        cin >> guessroulette;
                        if (cin.fail() || guessroulette <= 0 || guessroulette > 37)
                            cout << "Your number is not in range! Try again" << endl;
                        cin.clear(); // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                    } while (cin.fail() || guessroulette <= 0 || guessroulette > 37);

                    dice = rand() % 37 + 1; //holds randomly generates number in range between 1 and 10


                    if (dice == guessroulette) {
                        if (dice == 0) {
                            cout << "You got zero! You win " << bet * 100 << endl;
                            balance = balance + bet * 100;
                        }
                        else {
                            cout << "Well done! You won " << bet * 10 << endl;
                            balance = balance + bet * 35;
                        }
                    }


                    else {
                        cout << "Nice try... You lost " << bet << endl;

                    }
                    cout << "The winning number was : " << dice << endl;
                    cout << "You have : " << balance << " left" << endl;
                    if (balance == 0) {
                        cout << "You have no money to play with";
                        break;
                    }
                    CentreWord("WOULD YOU LIKE TO PLAY AGAIN?");
                    cin >> choise;
                } while (choise == 'y' || choise == 'Y');

                break;

            }
            case '2': {
                do {
                    do {
                        cout << "Guess a colour: red(1), blue(2), or zero(0) ";
                        cin >> choiseofcolour;
                        if (cin.fail() || choiseofcolour != '1' && choiseofcolour != '2' && choiseofcolour != '0')
                            cout << "There is no such colour! Try again" << endl;
                        cin.clear(); // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                    } while (cin.fail() || choiseofcolour != '1' && choiseofcolour != '2' && choiseofcolour != '0');
                    int randomcolour = rand() % 37;
                    playerArray[0] = rouletteArray[randomcolour];
                    if (playerArray[0] == choiseofcolour) {
                        if (playerArray[0] == '0') {
                            cout << "You won a jackpot!" << endl;
                            balance = balance + bet * 100;
                        }
                        else {
                            cout << "You won!" << endl;
                            balance = balance + bet * 2;
                        }
                    }
                    else {
                        cout << "Nice try... You lost " << bet << endl;
                    }
                    cout << "The winning number was : " << playerArray[0] << endl;
                    cout << "You have : " << balance << " left" << endl;
                    if (balance == 0) {
                        cout << "You have no money to play with";
                        break;
                    }
                    CentreWord("WOULD YOU LIKE TO PLAY AGAIN?");
                    cin >> choise;
                } while (choise == 'y' || choise == 'Y');

                break;
            }
            case '3': {
                do {
                    do {
                        cout << "Choose a dozen(1,2 or 3): ";
                        cin >> guess;
                        if (cin.fail() || (guess != '1' && guess != '2' && guess != '3'))
                            cout << "Your number is not in range! Try again" << endl;
                        cin.clear(); // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                    } while (cin.fail() || (guess != '1' && guess != '2' && guess != '3'));

                    dice = rand() % 37 + 1; //holds randomly generates number in range between 1 and 10


                    if (dice >= 0 && dice <= 12 && guess == '1') {
                        cout << "Well done! You won " << bet * 2 << endl;
                        balance = balance + bet * 3;
                    }
                    else if (dice >= 13 && dice <= 24 && guess == '2') {
                        cout << "Well done! You won " << bet * 2 << endl;
                        balance = balance + bet * 3;
                    }
                    else if (dice >= 25 && dice <= 26 && guess == '3') {
                        cout << "Well done! You won " << bet * 2 << endl;
                        balance = balance + bet * 3;
                    }
                    else {
                        cout << "Nice try... You lost " << bet << endl;

                    }
                    cout << "The winning number was : " << dice << endl;
                    cout << "You have : " << balance << " left" << endl;
                    if (balance == 0) {
                        cout << "You have no money to play with";
                        break;
                    }
                    CentreWord("WOULD YOU LIKE TO PLAY AGAIN?");
                    cin >> choise;
                } while (choise == 'y' || choise == 'Y');
                break;
            }
            case '4': {
                do {
                    dice = rand() % 37 + 1; //holds randomly generates number in range between 1 and 10
                    if (dice % 2 == 0) {
                        cout << "Nice try... You lost " << bet << endl;
                    }
                    else {
                        cout << "Well done! You won " << bet * 2 << endl;
                        balance = balance + bet * 2;
                    }
                    cout << "The winning number was : " << dice << endl;
                    cout << "You have : " << balance << " left" << endl;
                    if (balance == 0) {
                        cout << "You have no money to play with";
                        break;
                    }
                    CentreWord("WOULD YOU LIKE TO PLAY AGAIN?");
                    cin >> choise;
                } while (choise == 'y' || choise == 'Y');

                break;
            }
            case '5': {
                do {
                    dice = rand() % 37 + 1; //holds randomly generates number in range between 1 and 10
                    if (dice % 2 == 0) {
                        cout << "Well done! You won " << bet * 2 << endl;
                        balance = balance + bet * 2;
                    }
                    else {
                        cout << "Nice try... You lost " << bet << endl;
                    }
                    cout << "The winning number was : " << dice << endl;
                    cout << "You have : " << balance << " left" << endl;
                    if (balance == 0) {
                        cout << "You have no money to play with";
                        break;

                    }
                    CentreWord("WOULD YOU LIKE TO PLAY AGAIN?");
                    cin >> choise;
                } while (choise == 'y' || choise == 'Y');

                break;
            }
            default: {
                if (choiseingame != '6') {
                    cout << "Maybe you have misspelled, try again." << endl;
                    break;
                }

            }
            }
        }

        cout << endl;
        DrawLine(60, '_');
        cout << "Thank you for playing. Your balance is : " << balance << endl;
        if (total_win != 0) {
            cout << "Your total ammount of winning is : " << total_win << endl;
        }
        DrawLine(60, '_');
        player.updateTotalWin(total_win);
        player.updateBalance(balance);
        updateTopPlayersFile(player, "top_players.txt");
    }

};

class Blackjack : public Game {
private:
    vector<Player>& players;
public:
    Blackjack(vector<Player>& players) : players(players) {}
    void play(Player& player, int& total_win) override {
        CentreWord("WOULD YOU LIKE TO PLAY?(y/n)");
        cin >> choise;

        while (choise != 'Y' && choise != 'y' && choise != 'n' && choise != 'N')
        {
            cout << "Maybe you have mispelled, try again" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            CentreWord("WOULD YOU LIKE TO PLAY?(y/n)");
            cin >> choise;
        }

        do {

            EndGame = false;
            PlayerDone = false;
            DealerDone = false;
            PlayerHandSize = 0;
            DealerHandSize = 0;
            DealerSum = 0;
            PlayerSum = 0;
            for (int i = 0; i < 5; i++) DealerHand[i] = 0;
            for (int i = 0; i < 5; i++) PlayerHand[i] = 0;

            do {
                cout << name << ", how much would you like to bet? ";
                cin >> bet;
                if (cin.fail() || bet > balance || bet <= 0) {
                    cout << "Invalid bet! Please enter a valid positive integer lower than your balance." << endl;
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                }
            } while (cin.fail() || bet > balance || bet <= 0);

            DealerSum = 0;
            PlayerSum = 0;
            for (int i = 0; i < 5; i++) DealerHand[i] = 0;
            for (int i = 0; i < 5; i++) PlayerHand[i] = 0;


            system("cls");
            RulesOfTheGame2();
            CentreWord("YOUR BALANCE IS : ");
            CentreInt(balance);

            do {
                cout << "Type TAKE to play" << endl;
                cin >> take;
                result = (take == "TAKE");
                if (cin.fail() || !result) {
                    cout << "Invalid input, please, try again" << endl;
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                }
            } while (cin.fail() || !result);


            while (PlayerHandSize < 2) {
                PlayerHand[PlayerHandSize++] = 1 + (rand() % 11);
            }

            while (DealerHandSize < 2) {
                DealerHand[DealerHandSize++] = 1 + (rand() % 11);
            }

            PlayerSum = 0;
            for (int i = 0; i < PlayerHandSize; i++) {
                PlayerSum += PlayerHand[i];
            }

            DealerSum = 0;
            for (int j = 0; j < DealerHandSize; j++) {
                DealerSum += DealerHand[j];
            }

            CentreWord("YOUR CURRENT HAND SUM IS: ");
            CentreInt(PlayerSum);

            cout << "Your current hand is: " << endl;
            for (int i = 0; i < PlayerHandSize; i++) {
                CentreInt(PlayerHand[i]);
            }

            cout << "Dealer's current hand is: " << endl;
            for (int j = 0; j < DealerHandSize; j++) {
                CentreInt(DealerHand[j]);
            }

            if (DealerSum == 21 && PlayerSum == 21)
            {
                CentreWord("IT'S A TIE! YOU GET YOUR BET BACK");
                CentreWord("YOUR BALANCE IS : ");
                CentreInt(balance);

                for (int i = 0; i < 5; i++) DealerHand[i] = 0;
                for (int i = 0; i < 5; i++) PlayerHand[i] = 0;
                EndGame = true;
            }

            else if (DealerSum == 21 && PlayerSum != 21) {
                CentreWord("DEALER HAS A BLACKJACK. YOU LOSE");
                balance -= bet;
                CentreWord("YOUR BALANCE IS : ");
                CentreInt(balance);

                for (int i = 0; i < 5; i++) DealerHand[i] = 0;
                for (int i = 0; i < 5; i++) PlayerHand[i] = 0;
                EndGame = true;
            }
            else if (PlayerSum == 21 && DealerSum != 21) {
                CentreWord("YOU HAVE A BLACKJACK! YOU WIN!");
                balance += bet * 5;
                total_win = total_win + bet * 5;
                CentreWord("YOUR BALANCE IS : ");
                CentreInt(balance);
                CentreWord("YOUR TOTAL WIN IS : ");
                CentreInt(total_win);
                for (int i = 0; i < 5; i++) DealerHand[i] = 0;
                for (int i = 0; i < 5; i++) PlayerHand[i] = 0;

                EndGame = true;
            }

            while (!EndGame) {
                if (!PlayerDone) {
                    cout << "Would you like to hit? (y/n)" << endl;
                    cin >> Hit;

                    while (Hit != 'Y' && Hit != 'y' && Hit != 'n' && Hit != 'N') {
                        cout << "Invalid input, please enter 'y' or 'n'" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                        cin >> Hit;
                    }

                    if (Hit == 'y' || Hit == 'Y') {
                        if (PlayerHandSize < 5) {
                            PlayerHand[PlayerHandSize++] = 1 + (rand() % 11);
                        }
                        else {
                            CentreWord("YOU HAVE REACHED YOUR LIMIT OF CARDS");
                            PlayerDone = true;
                        }

                        cout << "Your current hand is: " << endl;
                        for (int i = 0; i < PlayerHandSize; i++) {
                            CentreInt(PlayerHand[i]);
                        }

                        PlayerSum = 0;
                        for (int i = 0; i < PlayerHandSize; i++) {
                            PlayerSum += PlayerHand[i];
                        }

                        CentreWord("YOUR CURRENT HAND SUM IS: ");
                        CentreInt(PlayerSum);

                        if (PlayerSum > 21) {
                            CentreWord("YOU HAVE EXCEEDED 21. YOU LOSE");
                            balance -= bet;
                            CentreWord("YOUR BALANCE IS : ");
                            CentreInt(balance);

                            for (int i = 0; i < 5; i++) DealerHand[i] = 0;
                            for (int i = 0; i < 5; i++) PlayerHand[i] = 0;
                            EndGame = true;
                        }

                        if (!PlayerDone) {
                            cout << "Would you like to stand? (y/n)" << endl;
                            cin >> Stand;

                            while (Stand != 'Y' && Stand != 'y' && Stand != 'n' && Stand != 'N') {
                                cout << "Invalid input, please enter 'y' or 'n'" << endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                                cin >> Stand;
                            }

                            if (Stand == 'y' || Stand == 'Y') {
                                PlayerDone = true;
                            }
                        }
                    }
                    else {
                        PlayerDone = true;
                    }
                }

                if (!DealerDone && PlayerDone) {
                    if (DealerSum < 17) {
                        if (DealerHandSize < 5) {
                            DealerHand[DealerHandSize++] = 1 + (rand() % 11);
                        }
                        else {
                            DealerDone = true;
                        }

                        DealerSum = 0;
                        for (int i = 0; i < DealerHandSize; i++) {
                            DealerSum += DealerHand[i];
                        }

                        cout << "Dealer's current hand is: " << endl;
                        for (int j = 0; j < DealerHandSize; j++) {
                            CentreInt(DealerHand[j]);
                        }

                        CentreWord("DEALER'S CURRENT HAND SUM IS: ");
                        CentreInt(DealerSum);

                        if (DealerSum > 21) {
                            CentreWord("DEALER'S HAND EXCEEDED 21. YOU WIN");
                            balance += bet * 5;
                            total_win += bet * 5;
                            CentreWord("YOUR TOTAL WIN IS : ");
                            CentreInt(total_win);
                            CentreWord("YOUR BALANCE IS : ");
                            CentreInt(balance);
                            for (int i = 0; i < 5; i++) DealerHand[i] = 0;
                            for (int i = 0; i < 5; i++) PlayerHand[i] = 0;

                            EndGame = true;
                        }
                    }
                    else {
                        DealerDone = true;
                    }
                }

                if (PlayerDone && DealerDone) {
                    if (PlayerSum == DealerSum) {
                        CentreWord("IT'S A TIE. YOU GET YOUR BET BACK");
                        CentreWord("YOUR BALANCE IS : ");
                        balance += bet;
                        CentreInt(balance);
                        for (int i = 0; i < 5; i++) DealerHand[i] = 0;
                        for (int i = 0; i < 5; i++) PlayerHand[i] = 0;

                        EndGame = true;
                    }
                    else if (PlayerSum > DealerSum) {
                        CentreWord("YOUR HAND SUM EXCEEDS THE DEALER'S. YOU WIN!");
                        balance += bet * 5;
                        total_win += bet * 5;
                        CentreWord("YOUR TOTAL WIN IS : ");
                        CentreInt(total_win);
                        CentreWord("YOUR BALANCE IS : ");
                        CentreInt(balance);
                        for (int i = 0; i < 5; i++) DealerHand[i] = 0;
                        for (int i = 0; i < 5; i++) PlayerHand[i] = 0;

                        EndGame = true;
                    }
                    else {
                        CentreWord("DEALER'S HAND SUM EXCEEDS YOURS. YOU LOSE!");
                        balance -= bet;
                        CentreWord("YOUR BALANCE IS : ");
                        CentreInt(balance);
                        for (int i = 0; i < 5; i++) DealerHand[i] = 0;
                        for (int i = 0; i < 5; i++) PlayerHand[i] = 0;

                        EndGame = true;
                    }
                    EndGame = true;
                }
            }

            CentreWord("YOUR BALANCE IS : ");
            CentreInt(balance);
            CentreWord("YOUR TOTAL WIN IS : ");
            CentreInt(total_win);

            if (balance <= 0) {
                CentreWord("You have no money to play with");
                break;
            }

            cout << "Would you like to play again? (y/n)";
            cin >> choise;

            while (choise != 'Y' && choise != 'y' && choise != 'n' && choise != 'N') {
                cout << "Invalid input! Please enter 'y' or 'n'." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                cout << "Would you like to play again? (y/n)";
                cin >> choise;
            }





        } while (choise == 'Y' || choise == 'y');
        player.updateBalance(balance);
        player.updateTotalWin(total_win);
        updateTopPlayersFile(player, "top_players.txt");

    }
};

class OneArmedBandit : public Game {
private:
    vector<Player>& players;
public:
    OneArmedBandit(vector<Player>& players) : players(players) {}
    void play(Player& player, int& total_win) override {
        CentreWord("WOULD YOU LIKE TO PLAY?(y/n)");
        cin >> choise;

        while (choise != 'Y' && choise != 'y' && choise != 'n' && choise != 'N')
        {
            cout << "Maybe you have mispelled, try again" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            CentreWord("WOULD YOU LIKE TO PLAY?(y/n)");
            cin >> choise;
        }

        do {
            system("cls");
            RulesOfTheGame3();
            CentreWord("YOUR BALANCE IS : ");
            CentreInt(balance);

            do {
                cout << name << ", how much would you like to bet? ";
                cin >> bet;
                if (cin.fail() || bet > balance || bet <= 0) {
                    cout << "Invalid bet! Please enter a valid positive integer lower than your balance." << endl;
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                }
            } while (cin.fail() || bet > balance || bet <= 0);

            do {
                cout << "Type SPIN to play" << endl;
                cin >> spin;
                result = (spin == "SPIN");
                if (cin.fail() || !result) {
                    cout << "Invalid input, please, try again" << endl;
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                }
            } while (cin.fail() || !result);

            if (result) {
                srand(time(nullptr)); // sets random number generator

                for (int i = 0; i < 3; i++) {
                    int randomIndex = rand() % 6; // takes random symbol from symbolsArray
                    randomArray[i] = symbolsArray[randomIndex]; // transfers random symbol to new array
                }

                for (int i = 0; i < 3; ++i) {

                    _setmode(_fileno(stdout), _O_U16TEXT); // switch to unicode
                    wprintf(randomArray[i].c_str());
                    _setmode(_fileno(stdout), _O_TEXT); // switch back to text mode

                }
                cout << endl;

                if (randomArray[0] == randomArray[1] && randomArray[0] == randomArray[2])
                {
                    if (randomArray[0] == symbolsArray[2])
                    {
                        cout << "Congratulations! You won a jackpot!" << endl;
                        balance += bet * 10;
                        total_win += bet * 10;
                        CentreWord("YOUR TOTAL WIN IS : ");
                        CentreInt(total_win);
                        CentreWord("YOUR BALANCE IS: ");
                        CentreInt(balance);

                    }
                    else if (randomArray[0] == symbolsArray[0])
                    {
                        cout << "Congratulations! Your bet multiplies by 3" << endl;
                        balance += bet * 3;
                        total_win += bet * 3;
                        CentreWord("YOUR TOTAL WIN IS : ");
                        CentreInt(total_win);
                        CentreWord("YOUR BALANCE IS: ");
                        CentreInt(balance);

                    }
                    else if (randomArray[0] == symbolsArray[1])
                    {
                        cout << "Congratulations! Your bet multiplies by 5" << endl;
                        balance = balance + bet * 5;
                        total_win += bet * 5;
                        CentreWord("YOUR TOTAL WIN IS : ");
                        CentreInt(total_win);
                        CentreWord("YOUR BALANCE IS: ");
                        CentreInt(balance);

                    }
                    else {
                        cout << "Congratulations! Your bet multiplies by 2" << endl;
                        balance = balance + bet * 2;
                        total_win += bet * 2;
                        CentreWord("YOUR TOTAL WIN IS : ");
                        CentreInt(total_win);
                        CentreWord("YOUR BALANCE IS: ");
                        CentreInt(balance);

                    }

                }
                else {
                    cout << "Nice try... You lost" << endl;
                    balance = balance - bet;
                    CentreWord("YOUR BALANCE IS: ");
                    CentreInt(balance);

                }
            }
            if (balance == 0) {
                cout << "You have no money to play with";
                break;
            }
            cout << "Do you want to play again? (y/n): ";
            cin >> choise;

        } while (choise == 'y' || choise == 'Y');

        while (choise != 'Y' && choise != 'y' && choise != 'n' && choise != 'N') {
            cout << "Invalid input! Please enter 'y' or 'n'." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            cout << "Would you like to play again? (y/n)";
            cin >> choise;
        };

        player.updateTotalWin(total_win);
        player.updateBalance(balance);
        updateTopPlayersFile(player, "top_players.txt");

    }
};




int main() {


    DrawLine(80, '_');
    CentreWord("CASINO");
    DrawLine(80, '_');

    CentreWord("WRITE YOUR NAME");;
    getline(cin, name); // gets player's name
    do {


        cout << "DEPOSIT YOUR AMOUNT: ";
        cin >> balance;


        // Check if the input is a valid integer and greater than zero
        if (cin.fail() || balance <= 0) {
            cout << "Invalid input. Please enter a positive integer." << endl;
        }
        // flush the input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (cin.fail() || balance <= 0);

    Player player(name, balance, total_win);
    vector<Player> topPlayers;
    topPlayers.push_back(player);



    int choice;
    char input;


    while (true) { // Loop indefinitely until user decides to exit
        CentreWord("Please, choose the game");
        CentreWord(" GUESS THE NUMBER (1) ");
        CentreWord(" BLACKJACK (2) ");
        CentreWord(" ONE - ARMED BANDIT (3) ");
        CentreWord(" EXIT (4) ");
        CentreWord(" SHOW TOP-100 PLAYERS (5) ");
        cout << "Type here: ";
        cin >> input; // Read user input

        switch (input) {

        case '1': {
            GuessTheNumber guessGame(topPlayers);
            guessGame.play(player, total_win);
            break;
        }

        case '2': {
            Blackjack blackjackGame(topPlayers);
            blackjackGame.play(player, total_win);
            break;
        }

        case '3': {
            OneArmedBandit banditGame(topPlayers);
            banditGame.play(player, total_win);
            break;
        }
        case '4': {
            return 0;
        }
        case '5': {
            displayTopPlayers("top_players.txt");
            break;
        }
        default: {
            cout << endl;
            CentreWord("Invalid choice. Please enter a number between 1 and 5.");
        }
        }
    }
    return 0;
}
