// lab4: 滑动拼图游戏
// date: 2022-03-30
/*
程序开始时，让用户输入拼图盘的大小，即几行几列，例如用户输入：4  4，
则生成一个4x4的拼图盘，并在上面随机摆放标有“1”到“15”的15块拼图。
接下来每次提示用户输入下一步，只能是“L”，“R”，“U”和“D”四种可能的移动。
“L”是向左移动，“R”是向右移动，“U”是向上移动，“D”是向下移动，
每次移动只能将一块拼图移到它相邻的一个空位上。
直到用户输入“q”退出游戏。
*/

/* 
实现了边界检测。
如果用户输入除了 R, L, U, D, q，会重新输入。
如果用户正确输入，但无法移动，
例如空方格在第一行第一个，用户还要向上移动，
会提示用户无法移动，重新输入。

缺点是拼图大小有限制，要小于 100 100
*/

#include <random>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <list>
// #include "lab4_random.cpp" // 生成随机数
using namespace std;
#define R 100
#define C 100


vector<int> GenerateDiffNumber(int max, int num=0, int min=0) // 产生随机序列
{
    num = max + 1;
    int rnd;
    vector<int> diff;
    vector<int> tmp; // 存储剩余的数 
    //初始化
    for(int i = min;i < max+1 ; i++ )
    {
        tmp.push_back(i);
    }
    srand((unsigned)time(0)); //初始化随机数种子
    for(int i = 0 ; i < num ; i++)
    {
        do{
            rnd = min+rand()%(max-min+1);
     
        }while(tmp.at(rnd-min)==-1);
        diff.push_back(rnd);
        tmp.at(rnd-min) = -1;
    }
    return diff;
}

class Jigsaw{
public:
    Jigsaw(){};
    Jigsaw(const int r, const int c);
    void exchange(char opr);
    void display();
    ~Jigsaw(){};
private:
    int _r = 1, _c = 1;
    int zero_r = 0, zero_c = 0;
    vector<int> v;
    int cs[R][C];
};

Jigsaw::Jigsaw(const int r, const int c)
{
    _r = r, _c = c;
    v = GenerateDiffNumber(r * c - 1);
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cs[i][j] = v[i * c + j];
            if (v[i * c + j] == 0)
            {
                zero_r = i, zero_c = j;
            }
        }
    }
}

void Jigsaw::exchange(char opr) // 执行 opr 操作 交换两个数
{
    int tmp = this->cs[zero_r][zero_c];
    // check if opr is legal
    
    while(true){
        int flag = 0;
        if((opr == 'R' && this->zero_c == this->_c - 1) ||
           (opr == 'L' && this->zero_c == 0) ||
           (opr == 'U' && this->zero_r == 0) ||
           (opr == 'D' && this->zero_r == this->_r - 1))
           flag = 1;
        if(flag){
            cout << "You can not move.\n";
            cout << "What is you next move: ";
            cin >> opr;
        }
        if(opr == 'q') { cout << "Game over.\n"; exit(0); }
        if(flag == 0) break;
    }
    
    switch (opr)
    {
    case 'R':
        cs[zero_r][zero_c] = cs[zero_r][zero_c + 1];
        cs[zero_r][zero_c + 1] = tmp;
        this->zero_c++;
        break;
    case 'L':
        cs[zero_r][zero_c] = cs[zero_r][zero_c - 1];
        cs[zero_r][zero_c - 1] = tmp;
        this->zero_c--;
        break;
    case 'U':
        cs[zero_r][zero_c] = cs[zero_r - 1][zero_c];
        cs[zero_r - 1][zero_c] = tmp;
        this->zero_r--;
        break;
    case 'D':
        cs[zero_r][zero_c] = cs[zero_r + 1][zero_c];
        cs[zero_r + 1][zero_c] = tmp;
        this->zero_r++;
        break;
    default:
        // cout << "wrong input\n";
        break;
    }
} 


void Jigsaw::display() 
{
    for(int i=0; i<this->_r; i++)
    {
        for(int j=0; j<this->_c; j++) { cout << "o----"; }
        cout << "o\n";
        for(int j=0; j<this->_c; j++) { cout << "|    "; }
        cout << "|\n";
        for(int j=0; j<this->_c; j++)
        {
            if(cs[i][j]==0){
                cout << "|    ";
            }else if(0 < cs[i][j] && cs[i][j] < 10){
                cout << "|  " << cs[i][j] << " ";
            }else if(10 <= cs[i][j]){
                cout << "| " << cs[i][j] << " ";
            }
        }
        cout << "|\n";
        for(int j=0; j<this->_c; j++) { cout << "|    "; }
        cout << "|\n";
    }
    for(int j=0; j<this->_c; j++) { cout << "o----"; }
    cout << "o\n";
}


int main(){
    int r=0, c=0;
    char opr;
    cout << "Please input the size of the plate: ";
    cin >> r >> c;
    Jigsaw j(r, c);
    j.display();
    // cout << "NOTE:\n";
    // cout << "input L means the empty card will move to the left;\n";
    // cout << "input R means the empty card will move to the right;\n";
    // cout << "input D means the empty card will move to the downward;\n";
    // cout << "input U means the empty card will move to the upperward;\n";
    // cout << "input q means to stop game.\n";
    while(true)
    {
        cout << "What is your next move: ";
        cin >> opr;
        if(opr != 'U' && opr != 'D' && opr != 'L' && opr != 'R' && opr != 'q')
        {
            cout << "Please input L, R, U, D or q.\n";
            continue;
        }
        if(opr == 'q')
        { 
            cout << "Game over.\n";
            break;
        }
        j.exchange(opr);
        j.display();
    }
    return 0;
}
