#include <iostream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

enum attr_enum{
    r=1<<0, w=1<<1,
    a1=1<<2,
    read=1<<3, write=1<<4, add=1<<5, del=1<<6,
    rw_mask = r | w,
    opr_mask = read | write | add | del
};

struct Folder_attr{
    Folder_attr(): attr(){}
    char attr;
};

struct File_attr{
    File_attr(): local(), attr(){}
    string local;
    char attr;
};

struct Operation{
    Operation(): file(), local(), attr(){}
    string file, local;
    char attr;
};

streamsize unlimited = unsigned(-1)>>1;

inline void reset(stringstream &obj){
    obj.ignore(unlimited);
    obj.clear();
    obj.flush();
}

int main(){
    string input, temp;
    stringstream inbuf;

    map<string, Folder_attr> folders;
    map<string, File_attr> files;

    while (cin>> input, input!="[Folder_start]");
    while (cin>> input, input!="[Folder_end]"){
        Folder_attr folder;

        inbuf<< input;
        getline(inbuf, input, ',');
        inbuf.ignore(unlimited, ',');
        getline(inbuf, temp, ',');
        if (temp.find('r') != string::npos){
            folder.attr |= r;
            if (temp.find('w') != string::npos){
                folder.attr |= w;
            }
        }
        inbuf>> temp;
        if (temp == string("a1")){
            folder.attr |= a1;
        }

        folders.insert(pair<string, Folder_attr>(input, folder));

        reset(inbuf);
    }

    while (cin>> input, input!="[File_start]");
    while (cin>> input, input!="[File_end]"){
        File_attr file;

        inbuf<< input;
        getline(inbuf, input, ',');
        inbuf.ignore(unlimited, ',');
        getline(inbuf, temp, ',');
        if (temp.find('r') != string::npos){
            file.attr |= r;
        }
        if (temp.find('w') != string::npos){
            file.attr |= w;
        }
        getline(inbuf, temp, ',');
        if (temp == string("a1")){
            file.attr |= a1;
        }
        inbuf>> file.local;

        files.insert(pair<string, File_attr>(input, file));

        reset(inbuf);
    }

    while (cin>> input, input!="[Operation_start]");
    while (cin>> input, input!="[Operation_end]"){
        Operation opr;
        File_attr tar;
        Folder_attr loc;

        inbuf<< input;
        getline(inbuf, temp, ',');
        if (temp == string("a1")){
            opr.attr |= a1;
        }
        getline(inbuf, temp, ',');
        if (temp == string("read")){
            opr.attr |= read;
        } else if (temp == string("write")){
            opr.attr |= write;
        } else if (temp == string("add")){
            opr.attr |= add;
        } else if (temp == string("del")){
            opr.attr |= del;
        }
        getline(inbuf, opr.file, ',');
        inbuf>> opr.local;

        if (folders.find(opr.local) != folders.end()){
            loc = folders[opr.local];

            switch (opr.attr & opr_mask){
              case read:
                if ((!((loc.attr ^ opr.attr) & a1) || loc.attr & r) &&
                  files.find(opr.file) != files.end() &&
                  (tar = files[opr.file]).local == opr.local &&
                  (!((tar.attr ^ opr.attr) & a1) || tar.attr & r)){
                    goto Opr_Success;
                }
                break;
              case write:
                if ((!((loc.attr ^ opr.attr) & a1) || loc.attr & w) &&
                  files.find(opr.file) != files.end() &&
                  (tar = files[opr.file]).local == opr.local &&
                  (!((tar.attr ^ opr.attr) & a1) || tar.attr & w)){
                    goto Opr_Success;
                }
                break;
              case add:
                if ((!((loc.attr ^ opr.attr) & a1) || loc.attr & w)){
                    tar.local = opr.local;
                    tar.attr = r | w | (opr.attr & a1);
                    files.insert(pair<string, File_attr>(opr.file, tar));
                    goto Opr_Success;
                }
                break;
              case del:
                if ((!((loc.attr ^ opr.attr) & a1) || loc.attr & w) &&
                  files.find(opr.file) != files.end() &&
                  (tar = files[opr.file]).local == opr.local &&
                  (!((tar.attr ^ opr.attr) & a1) || tar.attr & r)){
                    files.erase(opr.file);
                    goto Opr_Success;
                }
                break;
              default:;
          }
        }

        cout<< "Fail\n";
        if (false){
          Opr_Success:
            cout<< "Success\n";
        }

        reset(inbuf);
    }
    return 0;
}