#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isprot(int x,int y,vector<pair<int,int>> tentacles){
    for (int j = 0; j< tentacles.size();j++)
    {
        if(tentacles[j].first == y && tentacles[j].second == x)
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
    vector<pair<int,int>> set;
    vector<pair<int,int>> tentacles;
    while (1) {
        int entity_count;
        cin >> entity_count; cin.ignore();
        for (int i = 0; i < entity_count; i++) {
            int x;
            int y; // grid coordinate
            string type; // WALL, ROOT, BASIC, TENTACLE, HARVESTER, SPORER, A, B, C, D
            int owner; // 1 if your organ, 0 if enemy organ, -1 if neither
            int organ_id; // id of this entity if it's an organ, 0 otherwise
            string organ_dir; // N,E,S,W or X if not an organ
            int organ_parent_id;
            int organ_root_id;
            cin >> x >> y >> type >> owner >> organ_id >> organ_dir >> organ_parent_id >> organ_root_id; cin.ignore();
            if(type == "A" || type == "B" || type == "C" || type == "D")
                set.push_back({x,y});
            if(owner == 0) tentacles.push_back({x,y});
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
        cin >> required_actions_count; cin.ignore();
        for (int i = 0; i < required_actions_count; i++) {
            int fir = 2;
            int sec = 0;
            for (int k = 0; k < set.size();k++){

                if(!flag) break;
                //while(set[k].first -1> fir){
                //    cout << "GROW " << 1 <<" " << fir << " " <<  2 << " BASIC" <<endl;
                //    fir++;
                //}
                //GROW 2 1 7 SPORER E
                if(set[k].second == 1){
                    cout << "GROW " << 1 <<" " << 1 << " " <<  1 << " SPORER E" <<endl;
                    cout << "SPORE " << 3 <<" " << set[k].first-2 << " " <<  set[k].second  << endl;
                    fir = set[k].first;
                    sec = set[k].second;
                    cout << "GROW " << 5 <<" " << fir - 1 << " " <<  set[k].second << " HARVESTER" << " E"<<endl;
                }
                else if (set[k].second == 3){
                    cout << "GROW " << 1 <<" " <<1 << " " << 3 << " SPORER E" <<endl;
                    cout << "SPORE " << 3 <<" " << set[k].first -2 << " " <<  set[k].second <<endl;
                    fir = set[k].first;
                    sec = set[k].second;
                    cout << "GROW " << 5 <<" " << fir - 1 << " " <<  set[k].second << " HARVESTER" << " E"<<endl;
                }
                else{
                    cout << "GROW " << 1 <<" " <<2 << " " << 2 << " SPORER E" <<endl;
                    cout << "SPORE " << 3 <<" " << set[k].first-2 << " " <<  set[k].second << endl;
                    fir = set[k].first;
                    sec = set[k].second;
                    cout << "GROW " << 5 <<" " << fir - 1 << " " <<  set[k].second << " HARVESTER" << " E"<<endl;
                    }
                flag= 0;
            }
            while(1){
                if(sec == 1) {sec++;fir--;}
                if (sec ==3) {sec--;fir++;}
                if(sec == 2 && !flag){
                    cout << "GROW " << 5 <<" " << fir  << " " <<  3 << " BASIC" <<endl;
                    cout << "GROW " << 1 <<" " << j+1 << " " <<  1 <<  " BASIC" <<endl;
                    cout << "GROW " << 5 <<" " << fir << " " <<  4 << " HARVESTER" << " S"<<endl;
                    flag = 1;
                }
                cout << "GROW " << 1 <<" " << j+1 << " " <<  1 <<  " BASIC" <<endl;
                cout << "GROW " << 5 <<" " <<  fir << " " << sec - 1 << " BASIC" <<endl;


                cout << "GROW " << 1 <<" " << 2+j << " " <<  2 << " BASIC" <<endl;
                cout << "GROW " << 5 <<" " <<  fir - 1 - j << " " <<  sec -  j<< " BASIC" <<endl;


                cout << "GROW " << 1 <<" " << 1+j << " " <<  3 << " BASIC" <<endl;
                cout << "GROW " << 5 <<" " <<  fir - 2 - j<< " " <<  sec  - j<< " BASIC" <<endl;
                j++;
                cout << "GROW " << 5 << " " << j+1<< " " << 3 << " HARVESTER" << endl;
            }
            // try all possible four direction if an enemie's organ is there and then put a tentacle to slay the enemy
            /*cerr << isprot(j+4,2,tentacles)<< endl;
            if (!isprot(j + 4,2,tentacles)) cout << "GROW " << 1 <<" " << j+1 << " " <<  2 << " TENTACLE" << " S"<<endl;
            else cout << "GROW " << 1 <<" " << j+1 << " " <<  2 << " BASIC" <<endl;
            cerr << isprot(j + 3,3,tentacles)<< endl;
            if (isprot(j + 3,3,tentacles)) cout << "GROW " << 1 <<" " << j << " " <<  3 << " TENTACLE" << " S"<<endl;
            else cout << "GROW " << 1 <<" " << j << " " <<  3 << " BASIC" <<endl;
            cerr << isprot(j + 3,4,tentacles)<< endl;
            if (isprot(j + 3,4,tentacles)) cout << "GROW " << 1 <<" " << j << " " <<  4 << " TENTACLE" << " S"<<endl;
            else cout << "GROW " << 1 <<" " << j << " " <<  4 << " BASIC" <<endl;
            cerr << isprot(j + 3,5,tentacles)<< endl;
            if (isprot(j + 3,5,tentacles)) cout << "GROW " << 1 <<" " << j << " " <<  5 << " TENTACLE" << " S"<<endl;
            else cout << "GROW " << 1 <<" " << j << " " <<  5 << " BASIC" <<endl;
            j++;*/
        }

    }
}