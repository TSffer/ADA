#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

class CNode
{
    public:
        int x , y;
        double m_data;
        CNode *ptrX , *ptrY;
        CNode(int x_,int y_,double data)
        {
            this->x = x_;
            this->y = y_;
            this->m_data = data;
            ptrX = nullptr;
            ptrY = nullptr;
        }
};

template <class M>
class CTNode
{
    public:
        int x,y;
        double m_data;
        M* matriz;
        CTNode(int ,int ,double,M *);
        CTNode<M> &operator = (double d);
        CTNode<M> &operator = (CTNode<M> &);
        operator double();
};

template <class M>
inline CTNode<M>::CTNode(int _x,int _y,double d,M *m)
{
    this->x = _x;
    this->y = _y;
    m_data = d;
    matriz = m;
}

template <class M>
inline CTNode<M> &CTNode<M>::operator = (double d)
{
    if(d == matriz->Null)
    {
        matriz->remover(x,y);
    }
    else
    {
        matriz->insertar(d,x,y);
    }
    return *this;
}

template <class M>
inline CTNode<M> &CTNode<M>::operator = (CTNode<M> &obj)
{
    this->m_data = obj.m_data;
    return *this;
} 

template <class M>
inline CTNode<M>::operator double()
{
    return m_data;
}

template <int TX,int TY>
class CMatriz
{
    public:
        typedef CMatriz<TX,TY> Self;
        double Null = -1.0;
        CNode *listX[TX];
        CNode *listY[TY];
        vector<int> nV;
        vector<vector<int>> index; 

        bool findLisX(int x,int y,CNode **&);
        bool findLisY(int ,int,CNode **&);
        bool insertar(double,int,int);
        bool remover(int,int);
        int size(int);
        vector<int> adyacentes(int y);
        double iterator(int,int);

        CTNode<Self> operator()(int ,int);
        Self &operator = (Self &);
        Self operator = (Self);
        Self operator + (Self &);
        Self operator - (Self &);
        void print();
        CMatriz() : index(TY)
        {
            fill(listX,listX+TX,nullptr);
            fill(listY,listY+TY,nullptr);
            
            nV.assign(TY,0);
        }
};

template <int TX,int TY>
inline bool CMatriz<TX,TY>::findLisX(int x,int y,CNode**&ptr)
{
    ptr = &(listX[x]);
    if(*ptr)
    {
        while(*ptr && (*ptr)->y < y)
            ptr = &((*ptr)->ptrY);
            if(*ptr && (*ptr)->y == y)
                return true;
    }
    return false;
}

template <int TX,int TY>
inline bool CMatriz<TX,TY>::findLisY(int x,int y,CNode **&ptr)
{
    ptr = &(listY[y]);
    if(*ptr)
    {
        while(*ptr && (*ptr)->x < x)
            ptr = &((*ptr)->ptrX);
            if(*ptr && (*ptr)->x == x)
             return true;
    }
    return false;
}

template <int TX,int TY>
vector<int> CMatriz<TX,TY>::adyacentes(int x)
{
    CNode **ptr;
    vector<int> v;
    for(int i=0;i<TX;i++)
    {
        if(findLisX(x,i,ptr)!=false)
        {
            v.push_back(i);
            //cout<<(*ptr)->x<<endl;
        }
    }
    return v;
}

template <int TX,int TY>
inline bool CMatriz<TX,TY>::insertar(double d,int x,int y)
{
    CNode **ptr;
    if(x < 0 || y<0 || x>=TX || y>TY)
        return false;
    if(findLisX(x,y,ptr))
    {
        (*ptr)->m_data = d;
        return false;
    }
    else
    {
        CNode *tmp = new CNode(x,y,d);
        tmp->ptrY = *ptr;
        *ptr = tmp;
        findLisY(x,y,ptr);
        tmp->ptrX = *ptr;
        *ptr = tmp;
        nV[y] = nV[y]+1;
        index[y].push_back(x);
        return true;
    }
}
template <int TX,int TY>
inline bool CMatriz<TX,TY>::remover(int x,int y)
{
    CNode **ptrY;
    CNode **ptrX;
    if(!findLisX(x,y,ptrY))
        return false;
    findLisY(x,y,ptrX);
    CNode *tmpY = (*ptrY)->ptrY;
    CNode *tmpX = (*ptrX)->ptrX;
    delete *ptrY;
    *ptrY = tmpY;
    *ptrX = tmpX;
    return true;
}

template <int TX,int TY>
int CMatriz<TX,TY>::size(int x)
{
    int lon=0;
    CNode **ptr;

    for(int i=0;i<TX;i++)
    {
        if(findLisX(x,i,ptr)!=false)
        {
            lon++;
        }
    }
    return lon;
}

template <int TX,int TY>
double CMatriz<TX,TY>::iterator(int i,int j)
{
    CNode **ptr = &(listX[i]);
    int cont=0;
    while(cont!=j)
    { 
        ptr = &((*ptr)->ptrY);
        cont++;
    }
    return (*ptr)->m_data;
}

template <int TX,int TY>
inline CTNode<CMatriz<TX,TY> > CMatriz<TX,TY>::operator()(int x,int y)
{
    double d;
    CNode **ptr;
    if(findLisX(x,y,ptr))
        d = (*ptr)->m_data;
    else
        d = -1.0;
    return CTNode<Self>(x,y,d,this);
}

template <int TX,int TY>
inline CMatriz<TX,TY> &CMatriz<TX,TY>::operator = (Self &obj)
{
    for(int i=0;i<TX;i++)
    {
        for(int j=0;j<TY;j++)
        {
            (*this)(i,j) = obj(i,j);
        }
    }
    return *this;
} 

template <int TX, int TY>
inline CMatriz<TX,TY> CMatriz<TX,TY>::operator = (Self obj)
{
    for(int i=0;i<TX;i++)
    {
        for(int j=0;j<TY;j++)
        {
            (*this)(i,j) = obj(i,j);
        }
    }
    return *this;
}

template <int TX,int TY>
inline void CMatriz<TX,TY>::print()
{
    for(int i=0;i<TY;i++)
    {
        int cont = 0;
        CNode *ptr = listY[i];
        while(ptr)
        {
            while(ptr->x > cont)
            {
                cout<<-1.0<<"         ";
                cont++;
            }
            cout<<ptr->m_data<<"         ";
            ptr = ptr->ptrX;
            cont++;
        }
        while(TX - cont > 0)
        {
            cout<<-1.0<<"         ";
            cont++;
        }
        cout<<"\n";
    }

    cout<<"\n"<<endl;
}
/*
int main()
{
    CMatriz<1000000,1000000> A;
    A(1,1) = 1.1;
    //double r = A(1,1);
    //cout<<r<<endl;
    //A.print();
    return 0;
}*/