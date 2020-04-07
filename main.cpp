    /* same idea as the one provided by you: https://github.com/thecodingwizard/competitive-programming/blob/master/IZhO/IZhO%2018-treearray.cpp*/
    #include <bits/stdc++.h>
    using namespace std;
    const int N=2e5+5;
    int n,m,q,sprs[N][20],a[N],lvl[N];
    vector <int> v[N];
    set<int> s[N];
    void dfs (int x,int p)
    {
        sprs[x][0]=p;
        lvl[x]=lvl[p]+1;
        for (int i=1;i<20;i++)
            sprs[x][i]=sprs[sprs[x][i-1]][i-1];
        for (int i=0;i<v[x].size();i++)
        {
            if (v[x][i]!=p)
                dfs (v[x][i],x);
        }
    }
    int lca (int x,int y)
    {
        if (lvl[x]<lvl[y])
            swap(x,y);
        for (int i=19;i>=0;i--)
        {
            if (lvl[sprs[x][i]]>=lvl[y])
                x=sprs[x][i];
        }
        if (x==y)
            return x;
        for (int i=19;i>=0;i--)
        {
            if (sprs[x][i]!=sprs[y][i])
                x=sprs[x][i],y=sprs[y][i];
        }
        return sprs[x][0];
    }
    int main()
    {
        scanf("%d%d%d",&n,&m,&q);
        for (int i=0;i<n-1;i++)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            v[a].push_back(b);
            v[b].push_back(a);
        }
        dfs(1,0);
        for (int i=1;i<=m;i++)
        {
            scanf("%d",&a[i]);
            s[a[i]].insert(i);
            if (i>1)
            {
                int x= lca(a[i],a[i-1]);
                s[x].insert(i-1);
            }
        }
        for (int i=1;i<=n;i++)
            s[i].insert(m+1);
        while (q--)
        {
            int t;
            scanf("%d",&t);
            if (t==1)
            {
                int pos,x;
                scanf("%d%d",&pos,&x);
                s[a[pos]].erase(pos);
                if (pos>1)
                {
                    s[lca(a[pos],a[pos-1])].erase(pos-1);
                }
                if (pos<m)
                {
                    s[lca(a[pos],a[pos+1])].erase(pos);
                }
                a[pos]=x;
                s[a[pos]].insert(pos);
                if (pos>1)
                {
                    s[lca(a[pos],a[pos-1]   )].insert(pos-1);
                    s[a[pos-1]].insert(pos-1);
                }
                if (pos<m)
                {
                    s[lca(a[pos],a[pos+1])].insert(pos);
                    s[a[pos+1]].insert(pos+1);
                }
            }
            else
            {
                int l,r,x;
                scanf("%d%d%d",&l,&r,&x);
                int idx= *s[x].lower_bound(l);
                int o=0;
                if (a[idx]!=x)
                    r--,o++;
                if (idx<=r)
                    printf("%d %d\n",idx,idx+o);
                else
                    printf("-1 -1\n");
            }
        }
        return 0;
    }
    /*
    5 4 4
    1 2
    3 1
    3 4
    5 3
    4 5 2 3
    2 1 3 1
    1 3 5
    2 3 4 5
    2 1 3 1
    */
