#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class vertice
{
    public:
        int start_time;
        int end_time;
        string status;
        int value;
        float peso;
        vector<vertice> neighbors;
        vertice()
        {
            start_time = 0;
            end_time = 0;
            //status = "unvisited";
            value = 0;
        }
};

class Graph{
    int V; //Numero de vertices
    vector<vertice> *adj; //arreglo de vectoras de adyacencia
    vector<vertice> vert;
    bool *visited; //matriz de visitados.
public:
        Graph(int V); //Constructor
        void addEdge(int v,int w); //GRAFO Dirigido de v -> w
        int dfs(vertice v,int cur_time); //DFS iniciando de v
        void bfs(vertice v);
        int execute();
};


Graph::Graph(int V){
    this->V = V;
    
    for(int i=0;i<V;i++)
    {
        vertice n_w;
        n_w.value = i;
        n_w.status = "unvisited";
        this->vert.push_back(n_w);
    }

    adj = new vector<vertice>[V];
    this->visited = new bool[this->V];
    for(int i=0;i<this->V;i++) this->visited[i] = false;    
}


void Graph::addEdge(int v,int w)
{
    this->vert.at(v).neighbors.push_back(this->vert.at(w));
    this->vert.at(w).neighbors.push_back(this->vert.at(v));
}

int Graph::dfs(vertice u,int cur_time)
{
    u.start_time = cur_time;
    cur_time+=1;
    u.status = "in_progress";

    cout<<" ->"<<u.value;

    vector<vertice>::iterator v;

    for(v = u.neighbors.begin();v != u.neighbors.end();v++)
    { 
        if((*v).status == "unvisited")
        {
            cur_time = dfs((*v),cur_time);
            cur_time+=1;
        }
    }

    u.end_time = cur_time;
    u.status = "done";
    return cur_time;
}

void Graph::bfs(vertice s)
{
    vector< vector<vertice> > L(V);

    L[0].push_back(s);

    vector<vertice>::iterator v;
    vector<vertice>::iterator u;
    for(int i=0;i<V;i++)
    {
        for(u = L[i].begin();u != L[i].end();u++)
        {
            for(v = (*u).neighbors.begin();v != (*u).neighbors.end();v++)
            {
                if((*v).status == "unvisited")
                {
                   (*v).status = "visited";
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

int Graph::execute()
{
    int cur_time = 0;
    for(int i=0;i<V;i++)
    {
        cout<<"-> "<<vert[i].value<<endl;
        for(int j=0;j<vert[i].neighbors.size();j++)
        {       
            cout<<vert[i].neighbors[j].value<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    vertice v;
    v.value = 2;
   // int c = dfs(vert[2],cur_time);
   // cout<<endl;
    bfs(vert[2]);

    return 1; 
}

void leer()
{
    fstream archivo;
    string rows;
    archivo.open("grafo.txt",fstream::in|ios::binary);
    int Numero_vertice;
    int Numero_aristas;
    while(!archivo.eof())
    {
        getline(archivo,rows);
        size_t pos = rows.find(" ");
        Numero_vertice = stoi(rows.substr(0,pos));
        Numero_aristas = stoi(rows.substr(pos,rows.size));

    }

    archivo.close();
}


int main(){
    int V = 8;
    Graph G(V);
    G.addEdge(0,1);
    G.addEdge(0,2);
    G.addEdge(0,6);
    G.addEdge(1,3);
    G.addEdge(1,4);
    G.addEdge(1,5);
    G.addEdge(3,7);
    G.addEdge(4,7);    
    G.addEdge(5,7);
    G.addEdge(6,5);
    int cur_time = 0;

    cout<<"Time_curt :"<<G.execute()<<"\n"<<endl;

    return 0;
}