#include <iostream>
#include <climits>
#define I INT_MAX

using namespace std;

// ------ PRIM'S MINIMUM COST SPANNING TREE---------

// Adjacency matrix starting from (1,1)
int cost[][8]={{I,I,I,I,I,I,I,I},
                {I,I,25,I,I,I,5,I},
                {I,25,I,12,I,I,I,10},
                {I,I,12,I,8,I,I,I},
                {I,I,I,8,I,16,I,14},
                {I,I,I,I,16,I,20,18},
                {I,5,I,I,I,20,I,I},
                {I,I,10,I,14,18,I,I}};

    // finds out it is connected to which vertex
int near[8]={I,I,I,I,I,I,I,I};
    // generates a spanning tree
int t[2][6];

void PrimsMST()
{
 // u,v - vertex
    int i, j, k, u, v, n=7, mn=I;

    // Step 1 - find minimum cost edge
    for(i=1; i<=n; i++)
    {
        // only from upper triangular part
        for(j=i; j<=n; j++)
        {
            // if cost is less than min, min=cost of i. We got an edge
            if(cost[i][j] < mn)
            {
                mn=cost[i][j];
                u=i;
                v=j;
            }
        }
    }
    t[0][0]=u;
    t[1][0]=v;
    near[u]=0;
    near[v]=0;

    // initialize near array - nearer to u or v
    for(i=1; i<=n; i++)
    {
        if(near[i]!=0)
        {
            if(cost[i][u] < cost[i][v])
                near[i]=u;
            else
                near[i]=v;
        }
    }

    for(i=1; i<n-1; i++)
    {
        mn=I;
     // find which is nearer from the near array
        for(j=1; j<=n; j++)
        {
            if(near[j]!=0 && cost[j][near[j]] < mn)
            {
                k=j;
                mn=cost[j][near[j]];
            }
        }
        t[0][i]=k;
        t[1][i]=near[k];
        near[k]=0;

        for(j=1; j<=n; j++)
        {
            if(near[j]!=0 && cost[j][k] < cost[j][near[j]])
                near[j]=k;
        }
    }
    for(i=0; i<n-1; i++)
    {
        cout<<"("<<t[0][i]<<","<<t[1][i]<<")"<<endl;
    }
}


// ----------- KRUSKAL'S MINIMUM COST SPANNING TREE-------------

int edges[3][9] = {{1,1,2,2,3,4,4,5,5},              // first vertex
                    {2,6,3,7,4,5,7,6,7},             // second vertex
                    {25,5,12,10,8,16,14,20,18}};     // cost of edges

int set[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
int included[9] = {0};
int tofk[2][6];          // solution where spanning tree is stored

void Myunion(int u, int v)
{
    if(set[u] < set[v])
    {
        set[u] += set[v];
        set[v] = u;
    }
    else
    {
        set[v] += set[u];
        set[u] = v;
    }
}

int find(int u)
{
    int x=u, v=0;
    while(set[x] > 0)
    {
        x = set[x];
    }

    // Collapsing Find - connect found vertex to the parent
    while(u != x)
    {
        v = set[u];
        set[u] = x;
        u = v;
    }
    return x;
}

void KruskalsMST()
{
    int i, j, k, u, v, mn=I, n=7, e=9;

    i = 0;
    while(i < n-1)
    {
        mn=I;
        for(j=0; j<e; j++)
        {
           if(included[j]==0 && edges[2][j] < mn)
           {
               mn = edges[2][j];
               u=edges[0][j];
               v=edges[1][j];
               k=j;             //record minimum value
           }
        }

        if(find(u) != find(v))
        {
            tofk[0][i] = u;
            tofk[1][i] = v;
            Myunion(find(u),find(v));           // join the parents
            i++;
        }
        included[k]=1;
    }

    // traverse and display
    for(i=0; i<n-1; i++)
    {
        cout<<"("<<tofk[0][i]<<","<<tofk[1][i]<<")"<<endl;
    }
}

int main()
{
    int x;
    cout<<"1 for Prim's and 2. for Kruskal's."<<endl;
    cin>>x;
    cout<<endl;

    if(x==1)
        PrimsMST();
    else
        KruskalsMST();
    cout<<"\n";
    return 0;
}
