#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
typedef pair<int,int> pii;
typedef set<pii> spii;
typedef pair<pair<int,int>,int> piii;
typedef set<piii> spiii;
#define bs "BASIC"
#define tn "TENTACLE"
#define hv "HARVESTER"
#define sp "SPORER"

spiii my_organs;
spii prot;
spii tentacles;
spii wall;
spiii root;
pii enemy;


void grow(int x, int y,int id,string type,char face){
    cout << "GROW " << id << " " << x << " " << y << " " << type << " " << face << endl;
}

char isaround(piii org, spii prote){
    int x = org.first.first;
    int y = org.first.second;
    for(auto key : prote){
        if(key.first == x && key.second == y) return 'Z';
        if (key.first == x + 1 && key.second == y) return 'E';
        if (key.first == x && key.second == y + 1) return 'W';
        if (key.first == x - 1 && key.second == y) return 'N';
        if (key.first == x && key.second == y - 1) return 'S';
    }
    return 'X';
}
char iscorner(int x , int y,spii prot){
    for(auto key:prot){
            if(key.first == x && key.second == y) return 'Z';
            if (key.first == x -1 && key.second == y -1) return 'N';
            if (key.first == x + 1 && key.second == y - 1) return 'W';
            if (key.first == x - 1 && key.second == y + 1) return 'E';
            if (key.first == x + 1 && key.second == y + 1) return 'S';   
        }
        return 'X';
}
char isupthere(pii set){
    if(prot.count({set.first+2,set.second})) return 'E';
    else if (prot.count({set.first,set.second + 2})) return 'S';
    else if (prot.count({set.first,set.second - 2})) return 'N';
    else if (prot.count({set.first - 2,set.second})) return 'W';
    else return 'X';
}

bool enemyaround(int x,int y){
    for(auto key:tentacles){
        if( ((key.first >= x+1 && key.first <= x-1) && 
            (key.second == y+1 || key.second == y-1) )
            ||( (key.first == x+1 || key.first == x-1) && y == key.second) )
            return true;  
    }
    return false;
}
string whomi(piii set){
    if(wall.count({set.first.first,set.first.second})) return "WALL";
    else if(prot.count({set.first.first,set.first.second})) return "PROTEIN";
    else if(my_organs.count(set)) return "MYORGAN";
    else return "NONE";
}
// this func is for growing harvesters depending on the place of the proteins
void growharvest(piii set){
    int x = set.first.first;
    int y = set.first.second;
    int id = set.second;
    //cerr << iscorner(x,y,prot) << " " <<iscorner(x,y-1,wall) << " "<<  whomi(x,y-1)<<endl;
    if(iscorner(x,y,prot) == 'N' && iscorner(x,y-1,wall) != 'Z'
        && (whomi(set) != "MYORGAN" && whomi(set) != "WALL"))
        cout << "GROW " << id << " " << x << " " << y - 1 << " HARVESTER " << 'W'<<endl;
    else if(iscorner(x,y,prot) == 'N' && iscorner(x,y-1,wall) == 'Z'
        && (whomi(set) != "MYORGAN" && whomi(set) != "WALL")) 
        cout << "GROW " << id << " " << x - 1 << " " << y << " HARVESTER " << 'N'<<endl;
    // check for west north ^^^^^^^^^^^^^
    if(iscorner(x,y,prot) == 'W' && iscorner(x,y-1,wall) != 'Z'
        && (whomi(set) != "MYORGAN" && whomi(set) != "WALL"))
        cout << "GROW " << id << " " << x << " " << y - 1 << " HARVESTER " << 'E'<<endl;
    else if(iscorner(x,y,prot) == 'W' && iscorner(x,y-1,wall) == 'Z'
        && (whomi(set) != "MYORGAN" && whomi(set) != "WALL"))
        cout << "GROW " << id << " " << x +1 << " " << y << " HARVESTER " << 'N'<<endl;
    // check for east north ^^^^^^^^^^^^^
    if(iscorner(x,y,prot) == 'S' && iscorner(x,y+1,wall) != 'Z'
        && (whomi(set) != "MYORGAN" && whomi(set) != "WALL")) 
        cout << "GROW " << id << " " << x << " " << y + 1 << " HARVESTER " << 'E'<<endl;
    else if(iscorner(x,y,prot) == 'S' && iscorner(x,y+1,wall) == 'Z'
        && (whomi(set) != "MYORGAN" && whomi(set) != "WALL")) 
        cout << "GROW " << id << " " << x+1 << " " << y << " HARVESTER " << 'S'<<endl;
    // check for east south ^^^^^^^^^^^^^
    if(iscorner(x,y,prot) == 'E' && iscorner(x,y+1,wall) != 'Z'
        && (whomi(set) != "MYORGAN" && whomi(set) != "WALL")) 
        cout << "GROW " << id << " " << x << " " << y + 1 << " HARVESTER " << 'W'<<endl;
    else if(iscorner(x,y,prot) == 'E' && iscorner(x,y+1,wall) == 'Z'
        && (whomi(set) != "MYORGAN" && whomi(set) != "WALL")) 
        cout << "GROW " << id << " " << x -1 << " " << y  << " HARVESTER " << 'S'<<endl;
    // check for west south ^^^^^^^^^^^^^
    if (isupthere({x,y}) == 'E'){
        grow(x+1,y,id,hv,'E');}
    else if (isupthere({x,y}) == 'N'){
        grow(x,y-1,id,hv,'S');}
    else if (isupthere({x,y}) == 'W'){
        grow(x-1, y, id, hv, 'W');}
    else if (isupthere({x,y}) == 'S'){
        grow(x, y + 1,id, hv, 'S');}

}

void growbasic(piii org){
    int x = org.first.first;
    int y = org.first.second;
    int id = org.second;
    if(isaround({{x,y},id},prot) == 'N' && whomi({{x,y -1},id}) != "MYORGAN")
        cout << "GROW " << 1 <<" " << x << " " <<  y - 1 << " BASIC" <<endl;
    else if (isaround({{x,y},id},prot) == 'E'  && whomi({{x +1,y},id}) != "MYORGAN")
        cout << "GROW " << 1 <<" " << x + 1 << " " <<  y << " BASIC" <<endl;
    else if (isaround({{x,y},id},prot) == 'S'  && whomi({{x,y + 1},id}) != "MYORGAN")
        cout << "GROW " << 1 <<" " << x << " " <<  y + 1<< " BASIC" <<endl;
    else if (isaround({{x,y},id},prot) == 'W'  && whomi({{x - 1, y},id}) != "MYORGAN")
        cout << "GROW " << 1 <<" " << x - 1<< " " <<  y << " BASIC" <<endl;
}
void actions(pii enemy,spiii my_organs){
    for(auto key : my_organs){
        int id = key.second;
        static int j = 1;
        growharvest(key);
        growbasic(key);
        //grow(enemy.first,enemy.second,id,bs, j++ % 2 ? 'E':'N');
        grow(enemy.first,enemy.second,id,tn, j++ % 2 ? 'E':'N');
        grow(enemy.first,enemy.second,key.second,sp, key.second % 2 ? 'E':'N');
        cout << "SPORE " << key.second <<" " << enemy.first << " " <<   enemy.second << endl;
    }
}

void controller(spiii root){
    for(auto key:root){
        actions(enemy, my_organs);
    }
}
int getsomewhere(piii p){
    
}

int main()
{
    int width; // columns in the game grid
    int height; // rows in the game grid
    cin >> width >> height; cin.ignore();

    // game loop
    int j = 1;
    string proteins ="ABCD"; 
    while (1) {
        int entity_count;
        cin >> entity_count; cin.ignore();
        int x;
        int y; // grid coordinate
        string type; // WALL, ROOT, BASIC, TENTACLE, HARVESTER, SPORER, A, B, C, D
        int owner; // 1 if your organ, 0 if enemy organ, -1 if neither
        int organ_id; // id of this entity if it's an organ, 0 otherwise
        string organ_dir; // N,E,S,W or X if not an organ
        int organ_parent_id;
        int organ_root_id;    
        for (int i = 0; i < entity_count; i++) {
            cin >> x >> y >> type >> owner >> organ_id >> organ_dir >> organ_parent_id >> organ_root_id; cin.ignore();
            if(type == "A" || type == "B" || type == "C" || type == "D")
               prot.insert({x,y});
            if(owner == 0) tentacles.insert({x,y});
            if(owner == 1) my_organs.insert({{x,y},organ_id});
            if(type == "WALL") wall.insert({x,y});
            if(type == "ROOT" && owner == 1) root.insert({{x,y},organ_id});
            if(type == "ROOT" && owner == 0) enemy = {x,y};
        }
        int my_a;
        int my_b;
        int my_c;
        int my_d; // your protein stock
        cin >> my_a >> my_b >> my_c >> my_d; cin.ignore();
        int opp_a;
        int opp_b;
        int opp_c;
        int opp_d; // opponent's protein stock
        cin >> opp_a >> opp_b >> opp_c >> opp_d; cin.ignore();
        int required_actions_count; // your number of organisms, output an action for each one in any order
        int flag = 1;
        int lign(2),col(0);
        int m  = 0;
        cin >> required_actions_count; cin.ignore();
        for (int i = 0; i < required_actions_count; i++) {
            pii num = {100,100};
            for(auto r:root){
                for(auto key: prot){
                    if(abs(num.first - r.first.first) + abs(num.second - r.first.second) >
                        abs(key.first - r.first.first) + abs(key.second - r.first.second))
                        num = {key.first,key.second};
                }
                int dis = abs(num.first - r.first.first) + abs(num.second - r.first.second);
                while(--dis){
                    grow(num.first,num.second,r.second,"BASIC",'E');
                    cerr << num.first << num.second << endl;}
                growharvest({{num.first,num.second},r.second});
            }
            controller(root);
        }

    }
}