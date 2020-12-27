#include<iostream>
#include<stdlib.h>

using namespace std;
#define max 6

//升序
void Insert_Sort(int *A);
//降序
void Insert_Sort1(int *A);

int main()
{
    int A[max]={5,2,4,6,1,3};
    Insert_Sort(A);
    Insert_Sort1(A);
    system("pause");
    return 0;
}

void Insert_Sort(int *A){
    int i;
    for(int j=1; j<max; j++){
        int key = A[j];
        for(i=j-1; i>-1 && key<A[i]; i--){
        //右移覆盖key的位置，原位置为空待插入如果key满足该位置直接插入否则继续寻找key的位置
            A[i+1] = A[i];          
        }
        A[i+1] = key;
    }
    for(i=0; i<max; i++){
        cout<< A[i] <<" ";
    }
    cout<<endl;
}

void Insert_Sort1(int *A){
    int i;
    for(int j=1; j<max; j++){
        int key = A[j];
        for(i=j-1; i>-1 && key>A[i]; i--){
            A[i+1] = A[i];
        }
        A[i+1] = key;
    }
    for(i=0; i<max; i++){
        cout<< A[i] <<" ";
    }
    cout<<endl;
}