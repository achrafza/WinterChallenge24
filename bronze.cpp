#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
bool protaround(int x , int y,set<pair<int,int>> prot){
    for(auto key:prot){
        if( ((key.first >= x+1 && key.first <= x-1) && 
            (key.second == y+1 || key.second == y-1) )
            ||( (key.first == x+1 || key.first == x-1) && y == key.second) )
            return true; 
    }
    return false;
}

int main()
{
    int width; // columns in the game grid
    int height; // rows in the game grid
    cin >> width >> height; cin.ignore();

    // game loop
    int j = 1;
    string proteins ="ABCD"; 
    set<pair<int,int>> prot;
    set<pair<int,int>> tentacles;
    set<pair<int,int>> wall;
    pair<int,int> root;
    pair<int,int> enemy;
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
            if(type == "WALL") wall.insert({x,y});
            if(type == "ROOT" && owner == 1) root = {x,y};
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
            cout << "GROW 1 "<<enemy.first<< " " << enemy.second << " BASIC\n";
            if(protaround(root.first,root.second,prot)){
                
            }
        }

    }
}