#include <stack>
#include <string>
#include <iostream>
#include <set>
using namespace std;

int main(){

    string s;
    stack<string> st;
    set<string> tags;
    set<int> levels;
    int level =-1;
    getline(cin,s,'\n');
    for(int i=0;i<s.size();i++){
        if (s[i]=='<'){
            if ((i+6>=s.size())){
                cout<<"NO";
                return 0;
            }

            if (s[i+1] == '/'){
                int k = i;
                string ss;
                while (k<s.size() && s[k]!='>'){
                    if (k!=i+1)ss+=s[k];
                    k++;
                }
                if (st.top()!=ss || k== s.size()){
                    cout<<"NO";
                    return 0;
                }
                level--;
                st.pop();
            }else {
                if (levels.find(level+1)!=levels.end()){
                    cout<<"NO";
                    return 0;
                }
                int k = i;
                string ss;
                while (k<s.size() && s[k]!='>'){
                    if (s[k]=='/'){
                        cout<<"NO";
                        return 0;
                    }
                    ss+=s[k];
                    k++;
                }

                if (tags.find(ss)!=tags.end() || k == s.size() || ss=="<>"){
                    cout<<"NO";
                    return 0;
                }

                level++;
                levels.insert(level);
                tags.insert(ss);
                st.push(ss);
            }
        }
    }
    cout<<"YES";
    return 0;
}
//<tag1>content and <tag2>another <tag1>content and <tag2>another content</tag2></tag1> content</tag2></tag1>