#include <iostream>
#include <utility>
#include <algorithm>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;

void CA1()
{
    string v_inventory[] = { "sword", "dagger", "bow", "sling" };
    string itemToFind;
    bool searchStatus = false;
    cout << "What do you want to find? : ";
    cin >> itemToFind;

    for (int i = 0; i < size(v_inventory); i++)
    {
        if (itemToFind == v_inventory[i])
        {
            cout << "Item found!" << endl;
            cout << "It is found at the index " << i << ".";
            searchStatus = true;
        }
    }
    if (searchStatus == false)
    {
        cout << "Item not found!" << endl;
    }
}
void CA2()
{
    
    int rank[] = { 700, 723, 795, 854, 1000 };
    int low = 0;
    int high = size(rank) - 1;
    int scoreToFind;
    bool searchStatus = false;

    cout << "What do you want to find?: ";
    cin >> scoreToFind;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (scoreToFind == rank[mid])
        {
            cout << "Value found!" << endl;
            cout << "Value found in index " << mid << "." << endl;
            searchStatus = true;
            return;
        }
        else if (scoreToFind < rank[mid])
        {
            high = mid - 1;
            
        }
        else if (scoreToFind > rank[mid])
        {
            low = mid + 1;
        }
        
        if (searchStatus == false)
        {
            cout << "Item not found!" << endl;
            return;
        }
    }

}
auto CA3_1()
{
    int A = 1;
    int J = 11;
    int K = 13;
    int cards[] = { 5, A, 6, 10, K, J, 9, 3 };
    bool swapped;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < size(cards) - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < size(cards) - i - 1; j++)
        {
            if (cards[j] > cards[j + 1])
            {
                swap(cards[j], cards[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
    auto stop = high_resolution_clock::now();
    cout << "Sorted Cards : ";

    for (int i = 0; i < size(cards); i++)
    {
        if (cards[i] == 1)
        {
            cout << "A,";
            continue;
        }
        if (cards[i] == 11)
        {
            cout << "J,";
            continue;
        }
        if (cards[i] == 12)
        {
            cout << "Q,";
            continue;
        }
        if (cards[i] == 13)
        {
            cout << "K";
            continue;
        }
        cout << cards[i] << ",";

    }
    cout << endl;
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "Time taken to sort with bubble sort: " << duration << endl;

    return duration;
    
}
auto CA3_2()
{
    int cards[] = { 5,1, 6,10,13, 11, 9,3 };
    auto start = high_resolution_clock::now();
    for (int i = 1; i < size(cards); ++i)
    {
        int key = cards[i];
        int j = i - 1;

        while (j >= 0 && cards[j] > key)
        {
            cards[j + 1] = cards[j];
            j--;
        }
        cards[j + 1] = key;
    }
    auto stop = high_resolution_clock::now();

    cout << "Sorted Cards : ";
    for (int i = 0; i < size(cards); i++)
    {
        if (cards[i] == 1)
        {
            cout << "A";
        }
        else if (cards[i] == 11)
        {
            cout << "J";
        }
        else if (cards[i] == 12)
        {
            cout << "Q";
        }
        else if (cards[i] == 13)
        {
            cout << "K";
        }
        else
        {
            cout << cards[i];
        }
        if (!(i == size(cards) - 1))
        {
            cout << ",";
        }
    }
    cout << endl;
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "Time taken to sort with insertion sort: " << duration << endl;

    return duration;
}
int main()
{
    //CA1();
    //CA2();

    CA3_1();
    CA3_2();

    //if (CA3_1 > CA3_2)
    //{
    //    cout << "Insertion sort is faster for this time!";
    //}
    //else if (CA3_2 > CA3_1)
    //{
    //    cout << "Bubble sort is faster for this time!";
    //}
    //else if (CA3_2 == CA3_1)
    //{
    //    cout << "Both algorithm result in the same duration for this time!";
    //}

    return 0;
}
