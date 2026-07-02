#include <iostream>
#include <string>
#include <istream>
using namespace std;

void CA1()
{
    int a = 9;
    int b = 10;

    int* pointer1 = nullptr;
    int* pointer2 = nullptr;

    pointer1 = &a;
    pointer2 = &b;

    cout << "Address of a from the variable a: " << &a << endl;
    cout << "Address of b from the variable b: " << &b << endl;

    cout << endl;

    cout << "Address if a from the pointer1 : " << pointer1 << endl;
    cout << "Address if b from the pointer2 : " << pointer2 << endl;

    cout << endl;

    cout << "Address of pointer1: " << &pointer1 << endl;
    cout << "Address of pointer2: " << &pointer2 << endl;

    cout << endl;

    cout << "Content of a from pointer1 : " << *pointer1 << endl;
    cout << "Content of b from pointer2 : " << *pointer2 << endl;

    *pointer1 = 13;
    *pointer2 = 14;

    cout << endl;

    cout << "Value of a after changing the value with pointer : " << a << endl;
    cout << "Value of b after changing the value with pointer : " << b << endl;

    int* temp = pointer1;
    pointer1 = pointer2;
    pointer2 = temp;
    cout << endl;

    cout << "Pointer1 is referring to b now : " << *pointer1 << endl;
    cout << "Pointer2 is referring to a now : " << *pointer2 << endl;

    cout << "Address of a from the variable a: " << pointer1 << endl;
    cout << "Address of b from the variable b: " << pointer2 << endl;
}
class Flower
{
    int flowerId;
    string flowerName;
    string flowerColor;

    public: 
        Flower()
        {
            flowerId = 1;
            flowerName = "Rose";
            flowerColor = "Red";
        }
        Flower(int flowerId, string flowerName, string flowerColor)
        {
            this->flowerId = flowerId;
            this->flowerName = flowerName;
            this->flowerColor = flowerColor;
        }
        void printFLower()
        {
            cout << "Flower Id : " << flowerId << endl;
            cout << "Flower Name : " << flowerName << endl;
            cout << "Flower Color : " << flowerColor << endl;
        }
        ~Flower()
        {
            cout << "Deleted FLower : " << flowerId << endl;
        }
};
class Player
{
    public:
        int playerId;
        string playerName;

        Player()
        {
            playerId = 1;
            playerName = "Anonymous";
        }
        Player(int playerId, string playerName)
        {
            this->playerId = playerId;
            this->playerName = playerName;
        }
        void setPlayers(int id, string name)
        {
            this->playerId = id;
            this->playerName = name;
        }
        void printPlayers()
        {
            cout << "playerId : " << playerId << endl;
            cout << "playerName : " << playerName << endl;
        }
    
};
void CA4()
{
    Flower flower1;
    flower1.printFLower();
    cout << endl;

    Flower flower2(2, "Jasmine", "White");
    flower2.printFLower();
    cout << endl;

    Flower* flower3 = new Flower;
    flower3->printFLower();
    cout << endl;

    Flower* flower4 = new Flower(3, "Tulip", "Purple");
    flower4->printFLower();
    cout << endl;

    delete flower3;
    delete flower4;
}
void CA6()
{
    string playerName;
    int n = 0;
    beforeInput:
    cout << "How many players are there (2-8): ";
    cin >> n;

    if (n > 8 || n < 2)
    {
        cout << "Invalid Player Number! Try again!" << endl;
        goto beforeInput;
    }

    cin.ignore();

    Player* player = new Player[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter player " << i + 1 << " name : ";
        getline(cin, playerName);
        player[i].setPlayers(i + 1, playerName);
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        player[i].printPlayers();
        cout << endl;
    }

    delete[] player;
    
}
int main()
{

    //CA1();
    CA6();
    //CA4();
    return 0;
}
