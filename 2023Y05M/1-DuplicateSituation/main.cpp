#include <iostream>
#include <string>
using namespace std;

string inputSituation();

int main()
{
    int n;
    cin >> n;


    string* situation = new string[n];
    int* times = new int[n];

    for(int i = 0; i < n; i++)
        times[i] = 1;

    for (int i = 0; i < n; i++)
        situation[i] = inputSituation();

    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++){
            if(situation[j] == situation[i])
                times[i]++;
        }
    }

    for(int i = 0; i < n; i++)
        cout << times[i] << endl;

    return 0;
}

string inputSituation()
{
    string situation;
    for (int i = 0; i < 8; i++)
    {
        string temp;
        cin >> temp;
        situation += temp;
    }

    return situation;
}