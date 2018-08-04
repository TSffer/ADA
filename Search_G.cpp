#include <iostream>
#include <vector>

using namespace std;

class vertice
{
    public:
        int start_time;
        int end_time;
        string status;
        int value;
        vector<vertice> neighbors;
        vertice()
        {
            start_time = 0;
            end_time = 0;
            status = "unvisited";
            value = 0;
        }
};


class Grafo
{
    int V; //Numero de vertices
    vector<vertice> *adj; //arreglo de vector de adyacencia
    bool *visited; //matriz de visitados.
public:
        Grafo(int V); //Constructor

        void addEdge(int v,int w); //GRAFO Dirigido de v -> w
        int dfs(vertice v,int cur_time); //DFS iniciando de v
        void bfs(vertice s);
        void execute();
};
Grafo::Grafo(int V)
{
    this->V = V;
    adj = new vector<vertice>[V];
    this->visited = new bool[this->V];
    for(int i=0;i<this->V;i++) this->visited[i] = false;
}
void Grafo::addEdge(int v,int w)
{
    vertice n_v;
    n_v.value = w;
    adj[v].push_back(n_v); //agrega w a la posicion v

}

int Grafo::dfs(vertice u,int cur_time)
{
    u.start_time = cur_time;
    cur_time += 1;
    this->visited[u.value] = true; //marca el nodo actual como visitado e imprimelo
    cout << u.value << " ";
    
    u.status = "in_progress";
    vector<vertice>::iterator it;
    for(it = adj[u.value].begin(); it!=adj[u.value].end();++it)  //nodos adyacentes
    {
        if(!this->visited[(*it).value])
        {
            cur_time = dfs(*it,cur_time);
            cur_time+=1;
        }
    }
    u.end_time = cur_time;
    u.status = "done";
    return cur_time;
}

void Grafo::bfs(vertice s)
{
    vector< vector<vertice> > L(V);
    L[0].push_back(s);

    vector<vertice>::iterator u;
    vector<vertice>::iterator v;
    this->visited[L[0][0].value] = true;

    for(int i=0;i<V;i++)
    {
        for(u=L[i].begin();u!=L[i].end();u++)
        {
            for(v=adj[(*u).value].begin();v!=adj[(*u).value].end();v++)
            {
                if(!this->visited[(*v).value])
                {
                    this->visited[(*v).value] = true;
                    L[i+1].push_back((*v));
                }
            }
        }        
    }

    for(int i=0;i<L.size();i++)
    {
        for(int j=0;j<L[i].size();j++)
        {
            cout<<L[i][j].value<<" ";
        }
    }

}

void Grafo::execute()
{
    int cur_time = 0;
    vertice v;
    v.value = 9;
    //cout<<"cur_time: "<<dfs(v,cur_time)<<endl;
    dfs(v,cur_time);
    cout<<endl;
    
    return ; 
}

int main()
{
    int V = 10;
    Grafo G(V);
    G.addEdge(0,4);
    G.addEdge(4,9);
    G.addEdge(2,9);
    G.addEdge(9,1);
    G.addEdge(1,3);
    G.addEdge(1,6);
    G.addEdge(6,7);
    G.addEdge(8,6);    
    G.addEdge(7,8);
    G.addEdge(5,7);
    

    int cur_time = 0;

    int src = 2;
    cout << "La DFS de G es (iniciando de el vertice 2): " << endl << endl;
    G.execute();



    return 0;
}