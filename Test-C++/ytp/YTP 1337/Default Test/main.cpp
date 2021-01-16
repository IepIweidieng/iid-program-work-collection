#include <iostream>

using namespace std;

int main(){
    string card_default ("");
    getline(cin, card_default);
    string players[5] = {"", "", "", "", ""};

    for (int cur = 0, r = 0; cur<25; ++cur, ++r, r%=5){
        players[r].push_back(card_default[cur<<1]);
        players[r].push_back(card_default[(cur<<1)+1]);
    }

    string l_card (card_default.substr(50));

    bool dir = true;
    string outcard ("");

    while(getline(cin, outcard)){
        int next_player = 0;
        int maxout = outcard.length();
        int score = 0;
        int l_card_pos = 0;

        for (int cur_p = 0; cur_p < maxout, score <= 99; cur_p += 2){
            string oc ("");

            oc.push_back(outcard[cur_p]);
            oc.push_back(outcard[cur_p+1]);
            int pos = players[next_player].find(oc);
            players[next_player][pos] = l_card[l_card_pos];
            players[next_player][pos+1] = l_card[l_card_pos+1];

            l_card_pos += 2;

            switch(oc[1]){
              case '4':
                dir ^=1;
                next_player = ((next_player + ((dir<<1)-1)* 1)+5)%5;
                break;

              case '5':
                next_player = ((next_player + ((dir<<1)-1)* 2)+5)%5;
                break;

              case 'J':
                next_player = ((next_player + ((dir<<1)-1)* 1)+5)%5;
                break;

              case 'Q':
                next_player = ((next_player + ((dir<<1)-1)* 1)+5)%5;
                if (score < 80){
                    score += 20;
                } else {
                    score -= 20;
                }
                break;

              case 'T':
                next_player = ((next_player + ((dir<<1)-1)* 1)+5)%5;
                if (score < 90){
                    score += 10;
                } else {
                    score -= 10;
                }
                break;

              case 'K':
                next_player = ((next_player + ((dir<<1)-1)* 1)+5)%5;
                score = 99;
                break;

              case 'A':
                next_player = ((next_player + ((dir<<1)-1)* 1)+5)%5;
                ++score;
                break;

              default:
                next_player = ((next_player + ((dir<<1)-1)* 1)+5)%5;
                score += oc[1] - '0';
                break;
            }

        }

        if (maxout < l_card.length()){
            cout<< players[next_player]<< '\n';
            break;
        }

        getline (cin, l_card);
    }

    return 0;
}