#include <iostream>
#include <vector>
using namespace std;

struct group
{
    vector<int> g;
    int n;
    group(int n):n(n) {for (int i = 1; i < n; i++) g.push_back(i);}
    group(vector<int> g): g(g) {}

    int ord(int a)
    {
        int i = 1;
        int a_i = a;
        while (a_i != 1)
        {
             a_i = (a_i * a) % n;
             i++;
        }
        return i;
    }
};

int main()
{

    group z_11(11);
    cout << z_11.ord(3) << endl;  // returns 5
    cout << z_11.ord(2) << endl;  // returns 10 
    return 0;
}
