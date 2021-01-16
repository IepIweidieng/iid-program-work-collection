#include <iostream>
#include <string>

using namespace std;

int main(){
    string key, cont;
    size_t ocr=0, cur=0, klen;

    cin>> key, getline(cin, cont, '\b');
    for (klen = key.length(); (cur = cont.find(key, cur)) != string::npos && (++ocr, cur += klen, true););

    cout<< ocr<< endl;

    return 0;
}
