#include <iostream>
#include <string>

using namespace std;

int main(){
    string s;
    size_t s_len,
           k;

    cin>> s;
    k = s_len = s.length();

    for (char c = 'a'; c != 'z'+1; ++c){
        size_t cur     = s.find(c, 0),
               max_gap = min(cur, s_len)+1;
        if (max_gap >= k){continue;}

        while (cur != string::npos){
            size_t cur_next = s.find(c, cur+1),
                   gap      = min(cur_next, s_len) - cur;

            if (gap >= k){goto while_false;}
            max_gap = max(gap, max_gap);
            cur = cur_next;
        }

        k = max_gap;

      while_false:;
    }

    cout<< k<< endl;

    return 0;
}
