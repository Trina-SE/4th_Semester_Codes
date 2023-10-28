#include<bits/stdc++.h>
using namespace std;

string monoCipher;
string polyCipher;

void monoalphaCipher(string msg,string key){

 map<char,char>m;

 for(int i=0;i<26;i++){
    m['A'+i] = key[i];
    m['a'+i] = tolower(key[i]);
 }

 string monoEncrypt;

 for(int i=0;i<msg.size();i++){
    if(isalpha(msg[i])){
       monoEncrypt+=m[msg[i]];
    }
    else{
        monoEncrypt+=msg[i];
    }
 }
 monoCipher=monoEncrypt;
 cout<<monoEncrypt<<"\n";

}

string decryptMono(string msg, string key) {
    string decrypt;
    map<char, char> m;

    for (int i = 0; i < key.size(); i++) {
        m[tolower(key[i])] = 'a' + i;
        m[key[i]] = 'A' + i;
    }

    for (int i = 0; i < msg.size(); i++) {
        if (isalpha(msg[i])) {
            decrypt += m[msg[i]];
        } else {
            decrypt += msg[i];
        }
    }

    return decrypt;
}

void polyalpha(string msg,string key){

  string encrypt;

  for(int i=0;i<msg.size();i++){
    if(isalpha(msg[i])){

        int k_value= (key[i%key.size()])-'A';

        if(isupper(msg[i])){
            encrypt+= 'A' + (msg[i] - 'A' + k_value)%26 ;
        }
        else{
            encrypt+= 'a' + (msg[i] - 'a' + k_value)%26 ;
        }
    }
    else{
        encrypt+=msg[i];
    }
  }

  polyCipher=encrypt;

  cout<<encrypt<<"\n";


}

string decryptPoly(string msg,string key){

  string polyde;

  for(int i=0;i<msg.size();i++){
    if(isalpha(msg[i])){
        int k_value= (key[i%key.size()])-'A';

        if(isupper(msg[i])){
            polyde += 'A' + (msg[i] - 'A' - k_value + 26) % 26;
        }
        else{
             polyde += 'a' + (msg[i] - 'a' - k_value + 26) % 26;
        }
    }
    else{
        polyde+=msg[i];
    }
  }

  return polyde;

}


int main() {

   cout<<"What is your Secret Message?\n";
   string msg;
   getline(cin, msg);

   cout<<"Plain text to Monoalphabetic cipher : ";
   string key = "TASDFGHJKLMNBVCXZPOIUYQWER";
   monoalphaCipher(msg,key);

   string key2 = "TRINA";
   cout<<"Plain text to Polyalphabetic cipher : ";
   polyalpha(msg,key2);

  cout<<"Choose an option:\n";
  cout<<"1.Monoalphabetic cipher to Plain text\n2.Polyalphabetic cipher to Plain text\n";
  int op;
  cin>>op;

  if(op==1){
    cout<<"Secret message is: ";
    cout<<decryptMono(monoCipher,key)<<"\n";
  }
  else{
    cout<<"Secret message is: ";
    cout<<decryptPoly(polyCipher,key2)<<"\n";
  }


}


