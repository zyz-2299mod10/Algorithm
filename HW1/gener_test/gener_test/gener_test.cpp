#include <iostream>
#include <fstream>

using namespace std;

#define m 150
int S[10001];

int main()
{
    srand(5);
    int check;
    while (cin >> check && check)
    {
        ofstream ofs;
        ofs.open("C:/Users/asd91/Desktop/test.txt");
        int time = rand() % (1500 - 3) + 3;
        int realw = rand() % (m - 1) + 1;
        int fakew = rand() % (m - 1) + 1;
        int fake_position = rand() % (time - 3) + 3;

        for (int i = 0; i < time; i++)
        {
            if (i == fake_position) S[i] = fakew;
            else S[i] = realw;
        }

        ofs << time << "\n";
        for (int i = 0; i < time; i++) ofs << S[i] << " ";
        ofs << "\n";
        cout << fake_position << endl;

        ofs.close();
    }

    return 0;
}

