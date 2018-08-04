#include <iostream>
#include <vector>
#include <stdio.h>
#include <utility>
#include <algorithm>
#include <map>
#include <queue>
#include <time.h>

using namespace std;
#define MAX 100005 
#define INF 1<<30 


struct cmp {
    bool operator() (const pair<int,double> &a,const pair<int,double> &b) {
        return a.second > b.second;
    }
};

struct Edge  
{ 
    int v, w;
    double c;
    Edge(int v = -1,int w = -1 , double c = -1.0):v(v),w(w),c(c){}
};

class GRAPH 
{
  private:
    // Implementation-dependent code
    vector<vector <double> > adj;
    int Vcnt, Ecnt;
    bool digraph;
  public:
    vector< pair<int,double> > ady[MAX]; 
    double distancia[MAX];    
    bool visitado[MAX];      
    priority_queue<pair<int,double>,vector<pair<int,double>>,cmp> Q;                     
    int previo[MAX]; 
    bool *visited;


    GRAPH(int V, bool digraph = false) : adj(V), Vcnt(V), Ecnt(0), digraph(digraph)
    {
        /*for (int i = 0; i < V; i++)
            adj[i].assign(V, -1.0);*/
    }

    void reset()
    {
        for(int i = 0;i <= this->V() ;++i )
        {
            distancia[i] = INF;  
            visitado[i] = false; 
            previo[i] = -1;      
        }
    }

    void rl(int actual,int adyacente,double peso)
    {
        if( distancia[actual] + peso < distancia[adyacente] )
        {
            distancia[adyacente] = distancia[actual] + peso;  
            previo[adyacente] = actual;   
            pair<int,double> node;
            node.first = adyacente;
            node.second = distancia[ adyacente ];
            Q.push( node ); 
        }
    }

    void print(int destino)
    {
        if(previo[destino] != -1) 
            print(previo[destino]);
        cout<<destino<<",";       
    }

    void dijkstra(int inicial,int destino)
    {
        reset(); 
        float lon=0;
        pair<int,double> node;
        node.first = inicial;
        node.second = 0.0;
        Q.push(node); 
        distancia[inicial] = 0;      
        int actual , adyacente;
        double peso;
        while(!Q.empty())
        {                   
            actual = Q.top().first;            
            Q.pop();                           
            if( visitado[actual] )
            {
                visitado[actual] = true; 
            } 
                    
    
            for(int i=0 ;i < ady[actual].size() ; ++i ){ 
                adyacente = ady[ actual ][ i ].first;   
                //cout<<"A: "<<adyacente<<endl;
                //cout<<"I: "<<actual<<endl;
                peso = ady[ actual ][ i ].second;         
                if( !visitado[ adyacente ] ){        
                    rl(actual,adyacente,peso); 
                }
            }
        }
    
        /*cout<<"Distancia mas corta en vertice :"<<inicial<<endl;
        for(int i=1;i<=this->V();++i){
            cout<<"distancia "<<i<<": distancia corta ="<< distancia[i]<<endl;
        }*/
        cout<<distancia[destino]<<endl;
        cout<<"\n**************Impresion de camino mas corto**************"<<endl;    
        print(destino);
        cout<<endl;
    }

    int V() const
    {
        return Vcnt;
    }

    int E() const
    {
        return Ecnt;
    }

    bool directed() const
    {
        return digraph;
    }

    void insert(Edge e)
    {
        //adj[e.v][e.w] = e.c;
        Ecnt++;

        //adj[e.w][e.v] = e.c;
        pair<int,double> node;
        node.first = e.w;
        node.second = e.c;
        ady[e.v].push_back(node);
        /*node.first = e.v;
        node.second = e.c;
        ady[e.w].push_back(node);*/
        
    }

    void remove(Edge e)
    {
        adj[e.v][e.w] = -1.0;
        Ecnt--;
    }
    
    double edge(int a, int b)
    {
        return adj[a][b];
    }    

    class adjIterator 
    {
        private:
            const GRAPH &G;
            int i, v;   

        public:
            adjIterator(const GRAPH &G, int v) :  G(G), v(v), i(-1) { }
            int beg() { i = -1; return nxt(); }
            int nxt() {
                for (i++; i < G.V(); i++)
                    if (G.adj[v][i] != -1.0) return i;
                return -1;
            }
            bool end() { return i >= G.V(); }
    };

    ~GRAPH()
    {
        
    }

};


template <class Graph>
vector <Edge> edges(Graph &G)
{
    int E = 0;
    vector<Edge> a(G.E());
    for (int v = 0; v < G.V(); v++) {
        typename Graph::adjIterator A(G, v);
        for (int w = A.beg(); !A.end(); w = A.nxt()){
            if (G.directed() || v < w){
                a[E++] = Edge(v, w , G.edge(v,w));
            }    
        }
    }
    return a;
}

template <class Graph>
void show(const Graph &G) 
{
    for (int s = 0; s < G.V(); s++)
    {
        cout.width(2); cout << s << ":";
        typename Graph::adjIterator A(G, s);
        for (int t = A.beg(); !A.end(); t = A.nxt())
        { 
            cout.width(2); cout << t << " "; 
        }
        cout << endl;
    }
}

template <class T>
class dijkstra
{
    public:
        vector<bool> visitados;
        vector<double> w;
        vector<int> adj_prev;
        vector<int> res;
        int ini;
        dijkstra(){};
        void execute(T &G,int inicio,int destino);
        int sig(vector<bool> v,vector<double> p);
        void path(vector<int> prev,int final);
        void print();
        
};

template <class T>
void dijkstra<T>::execute(T &G,int inicio,int destino)
{
    ini = inicio;
    
    visitados.assign(G.V(),false);
    w.assign(G.V(),INF);
    adj_prev.assign(G.V(),-1);
    
    w[inicio] = 0;

    for(int i=0;i<G.V();i++)
    {
        visitados[inicio] = true;
        typename T::adjIterator A(G,inicio);
        for(int j=A.beg();!A.end();j=A.nxt())
        {
            if(visitados[j]==false)
            {
                if(w[j]>(w[inicio]+G.edge(inicio,j)))
                {
                    w[j] = w[inicio] + G.edge(inicio,j);
                    adj_prev[j] = inicio;
                }
            }
        }
        inicio = sig(visitados,w);
    }
   
    cout<<ini<<"->"<< destino <<" = : "<< w[destino] <<endl;
    path(adj_prev,destino);
}

template <class T>
int dijkstra<T>::sig(vector<bool> v,vector<double> p)
{
    map<double,int> vec;
    for(int i=0;i<v.size();i++)
    {
        if(v[i]==false)
        {
            vec[p[i]] = i;
        }
    }
    return vec.begin()->second;
}

template <class T>
void dijkstra<T>::path(vector<int> prev,int end)
{
    if(prev[end] == -1)
    {
        res.push_back(ini);
        return;
    }
    else
    {
        //cout<< end <<",";
        res.push_back(end);
        path(prev,prev[end]);
    }
}

template <class T>
void dijkstra<T>::print()
{
    for(int i=res.size()-1;i>=0;i--)
    {
        cout<<res[i]<<",";
    }
    cout<<endl;
}


int main()
{
    int nV,nE;
    
    cin >> nV >> nE;
    GRAPH G(nV,true);

    int a,b;
    double c;

    for(int e=0;e<nE;e++)
    {
        cin>> a >> b >>c;
        Edge eg(a,b,c);
        G.insert(eg);
    }

    int inicial = 1;
    int destino = 89;
    

    //dijkstra<GRAPH> A;
    
    double t1, t2;
	t1 = clock();
    //A.execute(G,inicial,destino);
    G.dijkstra(inicial,destino);
    t2 = clock();
	printf("Tiempo: %f", (t2-t1) / CLOCKS_PER_SEC);
    cout<<endl;
    //A.print();
   
    return 0;
}