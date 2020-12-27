#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <list>
using namespace std;
typedef list<char>::iterator it;
int n, m, pos, cnt = -1, sha;
int type[15];
char s[2005];
struct node
{
    int type;
    int show;
    int hp;
    int equip;
    int dead;
    list<char> card;
} p[15];
void init()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
    {
        char type[2];
        scanf("%s", type);
        if (type[0] == 'M')
            p[i].type = 1;
        else if (type[0] == 'Z')
            p[i].type = 2;
        else if (type[0] == 'F')
            p[i].type = 3;
        p[i].hp = 4;
        for (int j = 1; j <= 4; ++j)
        {
            char ch;
            scanf(" %c", &ch);
            p[i].card.push_back(ch);
        }
    }
    p[1].show = 1;
    scanf("%s", s + 1);
    return;
}
void P(int x)
{
    ++p[x].hp;
    return;
}
void K(int x)
{
    return;
}
void D(int x)
{
    return;
}
void F(int x)
{
    return;
}
void N(int x)
{
    return;
}
void W(int x)
{
    return;
}
void J(int x)
{
    return;
}
void Z(int x)
{
    p[id].equip = 1;
    sha = 1000;
    return;
}
void MP(int id)
{
    sha = 1;
    if (p[id].equip)
        sha = 1000000;
    while (!p[id].card.empty())
    {
        for (it i = p[id].card.begin(); i != p[id].card.end(); ++i)
            if (*i == 'P')
            {
                if (p[id].hp < 4)
                {
                    P(id);
                    break;
                }
                continue;
            }
            else if (*i == 'K')
            {
                if (sha)
                {
                    int lef = (id - 1 + n) % n, rig = (id + 1) % n;
                    if ((p[lef].type == 3 && p[lef].show) || (p[rig].type == 3 && p[rig].show))
                    {
                        K(id);
                        break;
                    }
                }
                continue;
            }
            else if (*i == 'D')
            {
                continue;
            }
            else if (*i == 'F')
            {
                int flg = 0;
                for (int j = 1; j <= n; ++j)
                    if (p[j].type == 3 && p[j].show)
                        flg = 1;
                if (flg)
                {
                    F(id);
                    break;
                }
                continue;
            }
            else if (*i == 'N')
            {
                N(id);
                break;
            }
            else if (*i == 'W')
            {
                W(id);
                break;
            }
            else if (*i == 'J')
            {
                continue;
            }
            else if (*i == 'Z')
            {
                Z(id);
                break;
            }
    }
    return;
}
void ZP(int id)
{
    sha = 1;
    if (p[id].equip)
        sha = 1000000;
    while (!p[id].card.empty())
    {
        for (it i = p[id].card.begin(); i != p[id].card.end(); ++i)
            if (*i == 'P')
            {
                if (p[id].hp < 4)
                {
                    P(id);
                    break;
                }
                continue;
            }
            else if (*i == 'K')
            {
                if (sha)
                {
                    int lef = (id - 1 + n) % n, rig = (id + 1) % n;
                    if ((p[lef].type == 3 && p[lef].show) || (p[rig].type == 3 && p[rig].show))
                    {
                        K(id);
                        break;
                    }
                }
                continue;
            }
            else if (*i == 'D')
            {
                continue;
            }
            else if (*i == 'F')
            {
                int flg = 0;
                for (int j = 1; j <= n; ++j)
                    if (p[j].type == 3 && p[j].show)
                        flg = 1;
                if (flg)
                {
                    F(id);
                    break;
                }
                continue;
            }
            else if (*i == 'N')
            {
                N(id);
                break;
            }
            else if (*i == 'W')
            {
                W(id);
                break;
            }
            else if (*i == 'J')
            {
                continue;
            }
            else if (*i == 'Z')
            {
                Z(id);
                break;
            }
    }
    return;
}
void FP(int id)
{
    sha = 1;
    if (p[id].equip)
        sha = 1000000;
    while (!p[id].card.empty())
    {
        for (it i = p[id].card.begin(); i != p[id].card.end(); ++i)
            if (*i == 'P')
            {
                if (p[id].hp < 4)
                {
                    P(id);
                    break;
                }
                continue;
            }
            else if (*i == 'K')
            {
                if (sha)
                {
                    int lef = (id - 1 + n) % n, rig = (id + 1) % n;
                    if (((p[lef].type == 1 || p[lef].type == 2) && p[lef].show) || ((p[rig].type == 1 || p[rig].type == 2) && p[rig].show))
                    {
                        K(id);
                        break;
                    }
                }
                continue;
            }
            else if (*i == 'D')
            {
                continue;
            }
            else if (*i == 'F')
            {
                int flg = 0;
                for (int j = 1; j <= n; ++j)
                    if ((p[j].type == 1 || p[j].type == 2) && p[j].show)
                        flg = 1;
                if (flg)
                {
                    F(id);
                    break;
                }
                continue;
            }
            else if (*i == 'N')
            {
                N(id);
                break;
            }
            else if (*i == 'W')
            {
                W(id);
                break;
            }
            else if (*i == 'J')
            {
                continue;
            }
            else if (*i == 'Z')
            {
                Z(id);
                break;
            }
    }
    return;
}
void play()
{
    while (1)
    {
        cnt = (cnt + 1) % n;
        pos = min(pos + 1, m);
        p[cnt].card.push_back(s[pos]);
        pos = min(pos + 1, m);
        p[cnt].card.push_back(s[pos]);
        if (p[cnt].type == 1)
            MP(cnt);
        else if (p[cnt].type == 2)
            ZP(cnt);
        else if (p[cnt].type == 3)
            FP(cnt);
    }
    return;
}
int main()
{
    init();
    play();
    return 0;
}