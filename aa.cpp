#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>
#include <chrono>
using namespace std;

int partition_1(vector<int> &A,int left,int right)
{
    float temp;
    int pivote = A[left];
    int izq = left-1;
    int der = right+1;
    while(izq<der)
    {
        do
        {
            izq++;
        }while(A[izq]<pivote);
        do
        {
            der--;
        }while(A[der]>pivote);
        if(izq<der)
        {
            temp = A[izq];
            A[der] = A[izq];
            A[izq] = temp;
        }
    }
    return (der);
}

int partition_2(vector<int> &A,int left,int right)
{
    double pivote,temp;
    int i,j;
    pivote = A[right];
    i=left-1;
    for(j=left;j<=right-1;j++)
    {
        if(A[j]<pivote)
        {
            i++;
            temp = A[i];
            A[i]=A[j];
            A[j] = temp;
        }
    }
    temp = A[i-1];
    A[i+1]=A[right];
    A[right]=temp;
    return i+1;
}

void Quicksort_1(vector<int> &A,int p,int r)
{
    if(p<r)
    {
        int q = partition_1(A,p,r);
        Quicksort_1(A,p,q);
        Quicksort_1(A,q+1,r);
    }    
}

void Quicksort_2(vector<int> &A,int p,int r)
{
    if(p<r)
    {
        int q = partition_2(A,p,r);
        Quicksort_2(A,p,q);
        Quicksort_2(A,q+1,r);
    }    
}

int main()
{
    vector<int> Vec_1,Vec_2;
    int a=20;
    double h1, h2, i1, i2, j1, j2, t1, t2 ;
    
    for(int i=100000;i<=1000000;i=i+100000)
    {
        for(int j=0;j<i;j++)
        {
            Vec_1.push_back(j);
        }
        Vec_2 = Vec_1;
        h1=clock();
        Quicksort_1(Vec_1,0,Vec_1.size());
        h2=clock();

        t1=(h2-h1)/CLOCKS_PER_SEC;

        i1=clock();
       //Quicksort_2(Vec_2,0,Vec_2.size());
        i2=clock();

        t2=(i2-i1)/CLOCKS_PER_SEC;
        
    /*
        for(int i=0;i<Vec_1.size();i++)
        {
            cout<<Vec_1[i]<<" ";
            
            
        }
    */
        cout<<t1<<"  "<<t2<<endl;
        Vec_1.clear();
        Vec_2.clear();
    }

    cout<<endl;
    return 0;
}