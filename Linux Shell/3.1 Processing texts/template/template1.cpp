#include <iostream>
using namespace std; 
 
int main()
{
    int x, y, tong;
    float trungbinhcong;

    cout << "Nhap hai so nguyen : " << endl;
    cin>>x>>y;

    tong=x+y;
    trungbinhcong=tong/2.0f;
    
    cout << "Tong cua " << x << " va " << y << " la " << tong << "." << endl;
    cout << "Trung binh cong cua " << x <<  " va " << y << " la " << trungbinhcong << "." << endl;
    return 0;
}