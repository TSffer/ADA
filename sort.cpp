#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <chrono>
#include <queue>

using namespace std;


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




template<class RandomAccessIterator>
void countingsort(RandomAccessIterator first, RandomAccessIterator last, int k)
{
    vector<int> counts(k+1,0);
    
    vector<int>::iterator it; 
    for(it = first ; it!= last ; it++)
    {
        counts[*it]++;
    }

    vector<int> result;
    vector<int>::iterator itc;
    itc = counts.begin(); 

    for(int i=0;i<counts.size();i++)
    {
        int a_i=0;
        while(a_i<counts[i])
        {
            (*first) = i;
            first++;
            a_i++;
        }
    }
}

template<class RandomAccessIterator>
void bucketsort(RandomAccessIterator first, RandomAccessIterator last,int k,int BUCKET_NUM)
{
    vector<int> sorted;

    vector<pair<int,int>>::iterator it; 

    vector< vector<pair<int,int>> > bucket(BUCKET_NUM);
    int i_A;
    for(it=first ; it!=last ; it++)
    {
       bucket[(*it).first].push_back((*it));
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
            (*first).second = bucket[i].at(t).second;
            //sorted.push_back( bucket[i].at(t).second);
            first++;
            t++;
        }
    }
}

template<class RandomAccessIterator>
void converter(RandomAccessIterator first1, RandomAccessIterator last1,int j)
{
    int i_dig,dig=0;
    pair<int,int> A_i;
    vector< pair<int,int> > A_conv;
    vector<pair<int,int>>::iterator it;

    for(it=first1;it!=last1;it++)
    {
        dig = pow(10,j);
        i_dig = (*it).second/dig%10;
        (*first1).first = i_dig;
        (*first1).second = (*it).second;
        first1++;
        //A_conv.push_back(A_i); 
    }
}

template<class RandomAccessIterator>
void radixsort(RandomAccessIterator first, RandomAccessIterator last,int d,int k)
{   
    for(int i=0;i<d;i++)
    {
        converter(first,last,i);
        bucketsort(first,last,k,k);
    }
} 

template<class RandomAccessIterator>
bool issorted(RandomAccessIterator first, RandomAccessIterator last){
	first++;
    for(RandomAccessIterator tem = first; tem != last; tem++){
        if(*tem < *(tem-1)) return false;
    }
    return true;
}

template<class RandomAccessIterator>
bool issorteds(RandomAccessIterator first, RandomAccessIterator last){
	first++;
    for(RandomAccessIterator tem = first; tem != last; tem++){
        if((*tem).second < (*(tem-1)).second) return false;
    }
    return true;
}

int main()
{

    // COMPILAR    g++ -std=c++11 sort.cpp -o main
    double tt1,tt2,tt3;
    vector<pair<int,int>> VC;
    std::chrono::high_resolution_clock::time_point t1;
    std::chrono::high_resolution_clock::time_point t2;
    std::chrono::duration<double> time_span;


    vector<int> Vector,Vec;
    vector<pair<int,int>> A;
    int l;
    pair<int,int> par;


    for(int i=1000;i<=10000;i=i+1000)
    {
        for(int j=0;j<i;j++)
        {
            l = rand()%i;
            par.second = l;
            par.first = 1;
            Vector.push_back(l);
            A.push_back(par);
        }
            Vec = Vector;

            t1 = std::chrono::high_resolution_clock::now();
                countingsort(Vector.begin(),Vector.end(),i);
            t2 = std::chrono::high_resolution_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1);
            double tt1 = time_span.count();

                VC = getKey(Vec,i,i);
            t1 = std::chrono::high_resolution_clock::now();
                bucketsort(VC.begin(),VC.end(),i,i);
            t2 = std::chrono::high_resolution_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1);
            double tt2 = time_span.count();

            t1 = std::chrono::high_resolution_clock::now();
            std::string s = std::to_string(i);
                radixsort(A.begin(),A.end(),s.size(),10);
            t2 = std::chrono::high_resolution_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1);
            double tt3 = time_span.count();

            Vector.clear();
            Vec.clear();
            A.clear();

            cout<<tt1<<" "<<tt2<<" "<<tt3<<" "<<endl;


    }
    cout<<endl;


/*
    int ns[] = {1000, 10000, 100000, 1000000, 10000000, 100000000};
    int ks[] = {1000, 100000, 100000000};
    vector<int> a;
    pair<int,int> par;
    int l;
    vector<pair<int,int>> a1;
    vector<pair<int,int>> a2;
    double h1, h2, i1, i2, j1, j2, t1, t2, t3;
    for(auto n: ns)
    {
        for(auto k: ks)
        {
          
            for(int i=0;i<n;i++)
            { 
                l = rand()%n;
                par.first = 1;
                par.second = l;
                a.push_back(l);
                a1.push_back(par);
            }

            vector<int> aa = a;

            h1 = clock();
            countingsort(a.begin(),a.end(),k);
            h2 = clock();
            if(!issorted(a.begin(),a.end()))
            {
                throw "countingsort not working";
            }
            t1 = (h2-h1)/CLOCKS_PER_SEC;

            a2 = getKey(aa,k,k/2);
            i1 = clock();
            bucketsort(a2.begin(),a2.end(),k,k/2);
            i2 = clock();
            //if (!issorted(a2.begin(),a2.end()))
            //{
            //    throw "bucketsort not working";
            //}
            t2 = (i2-i1)/CLOCKS_PER_SEC;
            
            j1 = clock();
            radixsort(a1.begin(),a1.end(),10,k);
            j2 = clock();
            //if (!issorted(a1.begin(),a1.end()))
            //{
             //   throw "radixsort not working";
            //}
            t3 = (j2-j1)/CLOCKS_PER_SEC;

            a.clear();
            a1.clear();
            a2.clear();
            aa.clear();
            
            cout << n << "  " << k << "  " << t1 << " " << t2 << " " << t3 << endl;
         }
    }*/

    return 0;
}