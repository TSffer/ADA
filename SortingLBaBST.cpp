#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <chrono>
#include <queue>

using namespace std;

vector<int> bucket_sort(vector<pair<int,int>> A,int k,int BUCKET_NUM);



bool compare_as_keys(pair<int,int> i,pair<int,int> j)
{
    return i.first<j.first;
}

vector<pair<int,int>> getKey(vector<int> A,int k,int BUCKET_NUM)
{
    pair<int,int> KeyA;
    vector<pair<int,int>> V;

    const int BUCKET_SIZE = k/BUCKET_NUM;
    for(int i=0;i<A.size();i++)
    {
        int bucket_index = A[i]/BUCKET_SIZE;
        if(bucket_index >= BUCKET_NUM)
        {
            bucket_index = BUCKET_NUM-1;
        }
        KeyA.first = bucket_index;
        KeyA.second = A[i];
        V.push_back(KeyA);
    }
    
    return V;//bucket_sort(V,k,BUCKET_NUM);
}


vector<int> bucket_sort(vector< pair<int,int> > A,int k,int BUCKET_NUM)
{
    vector<int> sorted;

    vector< vector<pair<int,int>> > bucket(BUCKET_NUM);
    
   // const int BUCKET_SIZE = k/BUCKET_NUM;
    
    for(int i=0;i<A.size();i++)
    {
        /*int bucket_index = A[i]/BUCKET_SIZE;
        if(bucket_index >= BUCKET_NUM)
        {
            bucket_index = BUCKET_NUM-1;
        }*/

        bucket[A[i].first].push_back(A[i]);
    }
    
    if(BUCKET_NUM<k)
    {
        for(int i=0;i<bucket.size();i++)
        {
            stable_sort(bucket[i].begin(),bucket[i].end(),compare_as_keys);
        }
    }
    
    for(int i=0;i<BUCKET_NUM;i++)
    {
        int t=0;
        while(t<bucket[i].size())
        {   
            sorted.push_back( bucket[i].at(t).second);
            t++;
        }
    }
    return sorted;
}


/*
int select_digit(int number,int place)
{
    for(int i=0;i<4;i++)
    {
        int d=pow(10,i);
        cout<<1983/d%10<<" ";
    }
}*/

vector<pair<int,int>> converter(vector<int> A,int j)
{
    int i_dig,dig=0;
    pair<int,int> A_i;
    vector< pair<int,int> > A_conv;

    for(int i=0;i<A.size();i++)
    {
        dig = pow(10,j);
        i_dig = A[i]/dig%10;
        A_i.first = i_dig;
        A_i.second = A[i];
        A_conv.push_back(A_i); 
    }
    return A_conv;
}

vector<int> radix_sort(vector<int> A,int d,int k)
{   
    vector<int> result;
    for(int i=0;i<d;i++)
    {
        A = bucket_sort(converter(A,i),k,k);
    }
    return A;
} 

int main()
{
    double tt1,tt2,tt3;
    vector<pair<int,int>> VC;
    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
    std::chrono::duration<double> time_span;


    vector<int> Vector;
    /*for(int i=0;i<1000000;i++)
    {
        Vector.push_back(rand()%999999);
    }*/
    
    //Vector = counting_sort(Vector,1000000);
    //Vector = getKey(Vector,1000000,1000000);
    /*Vector = radix_sort(Vector,6,10);

    for(int i=0;i<Vector.size();i++)
    {
        cout<<Vector[i]<<" ,";
    }*/

    cout<<"Counting_S "<<"Buket_S "<<"Radix_S "<<endl;
    
    for(int i=100000;i<=1000000;i=i+100000)
    {
        for(int j=0;j<i;j++)
        {
            Vector.push_back(rand()%i);

vector<int> counting_sort(vector<int> A,int k)
{
    vector<int> counts(k+1,0);
    for(int i=0;i<A.size();i++)
    {
        counts[A[i]]++;
    }
    vector<int> result;
    for(int i=0;i<counts.size();i++)
    {
        int a_i=0;
        while(a_i<counts[i])
        {
            result.push_back(i);
            a_i++;
        }
    }
    return result;
}        }
            t1 = std::chrono::high_resolution_clock::now();
                counting_sort(Vector,i);
            t2 = std::chrono::high_resolution_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1);
            double tt1 = time_span.count();

                VC = getKey(Vector,i,i);
            t1 = std::chrono::high_resolution_clock::now();
                bucket_sort(VC,i,i);
            t2 = std::chrono::high_resolution_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1);
            double tt2 = time_span.count();

            t1 = std::chrono::high_resolution_clock::now();
            std::string s = std::to_string(i);
                radix_sort(Vector,s.size(),10);
            t2 = std::chrono::high_resolution_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1);
            double tt3 = time_span.count();

            Vector.clear();
            cout<<tt1<<" "<<tt2<<" "<<tt3<<" "<<endl;
    }
    cout<<endl;

    return 0;
}