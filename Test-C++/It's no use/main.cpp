#include <iostream>
#include <string>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false), cin.tie((iostream*)NULL), cout.unsetf(ios::unitbuf);

    string keyword, context;
    size_t occur_count=0, cursor=0, keyword_length;

    cout<< "*Input the keyword:"<< endl, cin>> keyword;
    cout<< "*Input the context:"<< endl, getline(cin>> ws, context, '\b');
    for (keyword_length = keyword.length(); (cursor = context.find(keyword, cursor)) != string::npos && (++occur_count, cursor += keyword_length, true);){
        size_t line_head = context.rfind('\n', cursor-keyword_length)+1;
        size_t line_end = min(context.find('\n', cursor-keyword_length), context.length()-1);
        cout<< "\n*Find #"<< occur_count<< ":\n"<< context.substr(0, line_end)<< '\n'<<
          string(cursor-line_head-keyword_length, ' ')<< string(keyword_length, '^')<< " H E R E .\n"<<
          context.substr(line_end+1)<< "\n\n";
    }

    cout<< "*Total occurrence: "<< occur_count<< endl;

    return 0;
}