#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace std;



class Graph{
private:
        priority_queue<Edge, vector<Edge>, EdgeCompare> E_Sort;
        int V,E;
        vector<pair<double,pair<int,int> > > edges;
        vector<pair<double,pair<int,int> > > MST;
        double pesominimo;
public:
        Graph(int V,int E);
        void addEdge(int u,int v,double w);
        double kruskalMST();
        void printMST();
};

Graph::Graph(int V,int E){
    this->V = V;
    this->E = E;
    this->pesominimo = 0;
}

void Graph::addEdge(int u,int v,double w){
    edges.push_back({w,{u,v}});
}

void Graph::printMST(){
    vector<pair<double,pair<int,int> > >::iterator it;
    for(it = MST.begin();it!=MST.end();it++){
        cout << it->second.first << " - " << it->second.second << " , ";
    }

}


struct Bosque{
    int *parent, *rnk;
    int n;
    Bosque(int n){
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];
        for(int i = 0; i <= n; i++){
            rnk[i] = 0;
            parent[i] = i;
        }
    }
    int Find(int u){
        if(u != parent[u])
            parent[u] = Find(parent[u]);
        return parent[u];
    }
    
    void Union(int u, int v)
    {
        u = Find(u), v = Find(v);
        if (rnk[u] > rnk[v])
            parent[v] = u;
        else
            parent[u] = v;
        
        if (rnk[u] == rnk[v])
            rnk[v]++;
    }
};



struct DisjointSet{
    int *parent,*rnk;
    int n;

    DisjointSet(int n){
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];

        for(int i=0;i<=n;i++){
            rnk[i] = 0;
            parent[i] = i;
        }
    }
    int Find(int u){
        if(u == parent[u]) return parent[u];
        else return Find(parent[u]);
    }

    void Union(int x,int y){
        x = Find(x);
        y = Find(y);
        if(x != y){
            if(rnk[x] < rnk[y]){
                rnk[y] += rnk[x];
                parent[x] = y;
            }
            else{
                rnk[x] += rnk[y];
                parent[y] = x;
            }
        }
    }
    

};

class UF
{
    int *id, cnt,*sz;
    public:
        UF(int N)
        {
            cnt = N;id = new int[N];sz = new int[N];
            for(int i=0;i<N;i++) id[i] = i,sz[i] = 1;

        }
        ~UF()
        {
            delete[] id;
            delete[] sz;
        }
        int find(int p)
        {
            int root = p;
            while(root != id[root])
                root = id[root];
            while(p != root)
            {
                int newp = id[p];
                id[p] = root;
                p = newp;
            }
            return root;
        }

        void merge(int x,int y)
        {
            int i = find(x);int j = find(y);
            if(i==j)
                return;
            if(sz[i] < sz[j])
            {
                id[i] = j;
                sz[j] += sz[i];
            }
            else
            {
                id[j] = i,sz[i] += sz[j];
            }
            cnt--;
        }
        bool connected(int x,int y)
        {
            return find(x) == find(y);
        }
        int count()
        {
            return cnt;
        }
};
class Op
{   public:
        int padre[10000009];
        void Ini(int m)
        {
            for(int i=0;i<m;i++)
                padre[i] = i;
        }

        int Find(int x)
        {
            if(x == padre[x]) return x;
            else return Find(padre[x]);
        }

        int Union(int x,int y)
        {
            padre[Find(x)] = padre[Find(y)];
        }
};

struct EdgeCompare
{
    inline bool operator()(const pair<double,pair<int,int> > &t1,const pair<double,pair<int,int> > &t2)
    {
        return t1.first > t2.first;
    }
};

double Graph::kruskalMST(){
    /*
    double MSTWeight = 0; //sum of all vertex weights

    sort(edges.begin(),edges.end());
    cout<<"Numero de Edges : "<<edges.size()<<endl;


    Bosque b(this->V);
    vector<pair<double,pair<int,int> > >::iterator it;
    // for all edges in G
    for(it = edges.begin(); it!=edges.end();it++){
        int u = it->second.first;
        int v = it->second.second;

        int setU = b.Find(u);
        int setV = b.Find(v);

        if(setU != setV){
            double w = it->first;
            MST.push_back({w,{u,v}});
            MSTWeight =MSTWeight + it->first;

            b.Union(setU,setV);    
        }
    }
    //MSTWeight = 2027.94;
    cout<<"Numero MST :"<<MST.size()<<endl;
    return MSTWeight;*/
    vector<pair<double,pair<int,int> > >::iterator IT;
    for()


}
int main(){
    int V,E;
    double t1,t2;
    double weight=0;
    cin >> V >>E;

    Graph g(V,E);
    
    int u,v;
    double w;
    
    for(int i=0;i<E;i++){
        cin >> u >> v >> w;
        g.addEdge(u,v,w);
    }

    t1 = clock();
    weight = g.kruskalMST();
    t2 = clock();
    cout << "MST: " << endl;
    //g.printMST();
    cout<<endl;
    cout<<(t2-t1)/CLOCKS_PER_SEC)<<endl;
    cout << "Weight of MST is: " << weight<<endl;

    return 0;
}
