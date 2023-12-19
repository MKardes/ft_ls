#include <iostream>
using namespace std;

template <class T = int, int Q = 1>
class My
{
    private:
        T data;
    public:
        My(T _data) { data = _data; }
        void out()  { cout << data << endl; }
        void qOut()  {
            if(Q == 1)
                cout << data << ": Is a q variable" << endl;
        }
};

template <int K>
int func()
{
    if (K == 1)
        cout << "Merhaba" << endl;
    return(123);
}

int func1(int K)
{
    if (K == 1)
        cout << "Merhaba" << endl;
    return(123);
}

int main()
{
    My<int> a(12);
    My<string> b("Musab");
    My c(35);
    a.out();
    b.out();
    c.out();
    //Out:
    // 12
    // Musab
    // 35

    My<int, 2> q1(555);
    q1.qOut();
    My<int, 1> q2(556);
    q2.qOut();
    My q3(557);
    q3.qOut();
    //Out:
    // 556: Is a q variable
    // 557: Is a q variable

    func<1>();
    func<2>();
    func1(1);
    //Out:
    // Merhaba
    // Merhaba
}