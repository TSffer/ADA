#include <iostream>
#include <vector>
#include <time.h>
#include <ctime>
#include <chrono>
using namespace std;

int partition_1(vector<int> &A,int p,int r)
{
    int x = A[p];
    int i = p-1;
    int j = r+1;
    while(true)
    {
        do
        {
            j = j-1;
        }while(A[j]<=x);

        do
        {
            i=i+1;
        }while(A[i]>=x);
        
        if(i<j)
        {
            swap(A[i],A[j]);
        }
        else
        {
            return j;
        }
    }
}

int partition_2(vector<int> &A,int p,int r)
{
    int x = A[r];
    int i = p-1;
    
    for(int j=p;j<r;j++)
    {
        if(A[j]<=x)
        {
            i=i+1;
            swap(A[i],A[j]);
            
        }
    }
    swap(A[i+1],A[r]);
    return (i+1);
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

        for(int j=0;j<200000;j++)
        {
            Vec_1.push_back(j);

        }
        Vec_2 = Vec_1;
        h1=clock();
        Quicksort_1(Vec_1,1,Vec_1.size()-1);
        h2=clock();

        t1=(h2-h1)/CLOCKS_PER_SEC;

        i1=clock();
        Quicksort_2(Vec_2,1,Vec_2.size()-1);
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
    cout<<endl;
    return 0;
}