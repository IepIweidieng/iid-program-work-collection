#include <iostream>
#include <vector>
using namespace std;

/*
      0
    1   2
      3
    4   5
      6
*/

char _2_Feel(int feel){
    char res = 0;
    for (short k=0; feel; ++k, feel/=10){
        if (feel%10){
            res |= 1<<k;
        }
    }
    return res;
}

char const digigum[11] = {_2_Feel(1110111), _2_Feel(100100), _2_Feel(1011101),  //0, 1, 2
                          _2_Feel(1101101), _2_Feel(101110), _2_Feel(1101011),  //3, 4, 5
                          _2_Feel(1111011), _2_Feel(100101), _2_Feel(1111111),  //6, 7, 8
                          _2_Feel(1101111), _2_Feel(     0)   //9, _
                         };

char const &_0 = digigum[0], &_1 = digigum[ 1], &_2  = digigum[2],
           &_3 = digigum[3], &_4 = digigum[ 4], &_5  = digigum[5],
           &_6 = digigum[6], &_7 = digigum[ 7], &_8  = digigum[8],
           &_9 = digigum[9], &__ = digigum[10];

/*
     1
    000
     1
*/

char pos = _2_Feel(11), neg = _2_Feel(1);

struct chew_5gum{char const *arr[5];};
struct tchan{unsigned char lost, gain;};

inline char const *gum2chew(char gum){
    switch (gum){
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': return &digigum[gum-'0'];
      case '+': return &pos;
      case '-': return &neg;
      case ' ':
      default:  return &__;
    }
}

chew_5gum How_It_Feels_2_Chew_5Gum(string &_5gum){
    size_t inds = _5gum.find('"');
    chew_5gum res = {
      gum2chew(_5gum[inds+1]),
      gum2chew(_5gum[inds+2]),
      gum2chew(_5gum[inds+3]),
      gum2chew(_5gum[inds+5]),
      gum2chew(_5gum[inds+6])
    };
    return res;
}

tchan Senses(char const _5gum, char const b4gum){
    tchan res = {0, 0};
    for (char k = 0; k <= 6; ++k){
        if (!(_5gum&(1<<k)) && (b4gum&(1<<k))){++res.lost;}
        if ((_5gum&(1<<k)) && !(b4gum&(1<<k))){++res.gain;}
    }
    return res;
}

size_t Stimul8_Ur_Senses(chew_5gum &_5gum){
    std::vector<std::vector<chew_5gum> > n5gums (0);
    int sum;
    for (short k=0; k < 10*10; ++k){
        sum = k/10 + k%10;
        n5gums.push_back(std::vector<chew_5gum>(0));
        if (sum >= 10){
            chew_5gum gum = {
              &digigum[k/10],
              &pos,
              &digigum[k%10],
              &digigum[sum/10],
              &digigum[sum%10]
            };
            n5gums.back().push_back(gum);
        } else {
            chew_5gum gum = {
              &digigum[k/10],
              &pos,
              &digigum[k%10],
              &__,
              &digigum[sum]
            };
            n5gums.back().push_back(gum);
            std::swap(gum.arr[3], gum.arr[4]);
            n5gums.back().push_back(gum);
        }

        sum = k/10 - k%10;
        if (sum >= 0){
            n5gums.push_back(std::vector<chew_5gum>());

            chew_5gum gum = {
              &digigum[k/10],
              &neg,
              &digigum[k%10],
              &__,
              &digigum[sum]
            };
            n5gums.back().push_back(gum);
            std::swap(gum.arr[3], gum.arr[4]);
            n5gums.back().push_back(gum);
        }
    }

    size_t res = 0;
    for (std::vector<std::vector<chew_5gum> >::iterator k = n5gums.begin(), n = n5gums.end(); k != n; ++k){
        for (std::vector<chew_5gum>::iterator m = k->begin(), p = k->end(); m != p; ++m){
            tchan legit = {0, 0},
                  pl;
            for (short t = 0; t < 5; ++t){
                pl = Senses(*m->arr[t], *_5gum.arr[t]);
                legit.lost += pl.lost;
                legit.gain += pl.gain;
                if (legit.lost > 2 || legit.gain > 2){continue;}
            }
            if (legit.lost != 2 || legit.gain != 2){continue;}
            ++res;
            goto n5gums_for_k2n_continue;
        }
      n5gums_for_k2n_continue:;
    }
    return res;
}

int main(){
    string gum;
    chew_5gum feel;

    while (getline(cin, gum)){
        feel = How_It_Feels_2_Chew_5Gum(gum);
        cout<< Stimul8_Ur_Senses(feel)<< endl;
    }

    return 0;
}