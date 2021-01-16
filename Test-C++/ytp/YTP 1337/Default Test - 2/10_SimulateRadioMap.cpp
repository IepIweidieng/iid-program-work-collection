#include <iostream>
#include <cmath>

using namespace std;

struct pos{
    int x, y;
};

int main(){
    string in;
    cin>> in;

    int all_field[10][10] = {};

    pos tar = {in[0]-'0', in[1]-'0'};

    for (int u = 3; u < in.length(); u+=3){
          pos h_pos = {in[u]-'0', in[u+1]-'0'};
          pos st_p = {h_pos.x - 4, h_pos.y - 4};

          for (int v = 0; v!=9; ++v){
              for (int p = 0; p!=9; ++p){
                  pos cur_p = {st_p.x+v, st_p.y+p};
                  unsigned int dis = round(sqrt((cur_p.x-h_pos.x)*(cur_p.x-h_pos.x)+(cur_p.y-h_pos.y)*(cur_p.y-h_pos.y)));

                  if (dis<5){
                      if (cur_p.x >= 0 && cur_p.y >= 0 && cur_p.x < 10 && cur_p.y < 10){
                          all_field[cur_p.x][cur_p.y] += 5-dis;
                      }
                  }
              }
          }
    }
/*    for(int u=0;u!=10;u++){
      for(int p=0;p!=10;p++){
          cout<< all_field[p][u];
      }
      cout<< endl;
    }
*/
    int out = all_field[tar.x][tar.y];

    if (out < 10) cout<< '0'<< out<< endl;
    else cout<< out<< endl;

    return 0;
}