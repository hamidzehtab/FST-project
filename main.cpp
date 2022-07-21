#include<bits/stdC++.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/*** Hamid Reza Zehtab - 9912762541 - Languages and Automata - Spring 2022 ***/


string in_tape,out_tape = "";




class Graph {
public:
    map<string, list<pair<string,pair<string,string> > > > adj;
    map<string, bool > final;

    void add_transition(string v, string w,string input,string output);
    void add_set_transition(string in_state_name,string input_set,string out_state_name);
    void DFS(string v,int head_in,string local);
    void add_state(string state_name, bool is_final);

};
void Graph::add_transition(string v, string w,string input,string output)
{
    adj[v].push_back({w,{input,output}});
}
void Graph::add_state(string state_name, bool is_final){
    // is_final -> true or false
    if(is_final==true)final[state_name] = true ;
}

void Graph::add_set_transition(string in_state_name,string input_set,string out_state_name){
    for(int i=0;i<input_set.length();i++){
        string q;
        q.push_back(input_set[i]);
        add_transition(in_state_name,out_state_name,q,q);
    }
}

void Graph::DFS(string v,int head_in,string local)
{
    //cout<<"v: "<<v<<" head: "<<head_in<<" loc: "<<local<<endl;
    if((head_in==in_tape.length()) && (final[v]==true) ){
        out_tape += (local) + "\n";
    }
    list<pair<string,pair<string,string> > >::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i){
        string u = (*i).first;
        string input = (*i).second.first;
        string output = (*i).second.second;
        if(output == "LAMBDA") output = "";

        if(input=="LAMBDA"){
            DFS(u,head_in,local+output);
        }
        else{
            if(head_in<in_tape.length()){
                string q;
                q.push_back(in_tape[head_in]);
                if(q==input){
                    string new_local = local+output;
                    DFS(u,head_in+1,new_local);
                }
            }
        }
    }
}

void phase_1(){
    /***
    Graph g;
    g.add_state("st0",0);
    g.add_state("st1",0);
    g.add_state("st2",1);
    g.add_set_transition("st0" , "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ,"st0");
    g.add_set_transition("st0" , "ABCDEFGHIJKLMNOPQRTUVWXYZ" ,"st2");
    g.add_transition("st0", "st1","S","S");
    g.add_transition("st1", "st2","S","LAMBDA");
    g.add_transition("st1", "st2","LAMBDA","LAMBDA");

    g.DFS("st0",0,"");

     **/
    Graph g;
    g.add_state("st0",0);
    g.add_state("stf",1);
    g.add_transition("st0", "st0","a","LAMBDA");
    g.add_transition("st0", "st0","b","b");
    g.add_transition("st0", "stf","a","LAMBDA");
    g.add_transition("st0", "stf","LAMBDA","LAMBDA");

    g.DFS("st0",0,"");

}

void phase_2(){
    Graph g;
    g.add_state("st0",0);
    for(int ii='a'+0;ii<'a'+26;ii++){
        for(int ji='a'+0;ji<'a'+26;ji++){
            string i;
            i.push_back((ii));
            string j;
            j.push_back((ji));
            g.add_state("st"+i+"p"+j,0);
            g.add_state("st"+i+"p"+j+"v"+"2",0);
            g.add_state("st"+i+"p"+j+"v"+"3",0);
            g.add_state("st"+i+"p"+j+"v"+"4",0);
        }
    }
    g.add_state("stf",1);
    g.add_set_transition("st0" , "abcdefghijklmnopqrstuvwxyz" ,"st0");

    for(int ii='a'+0;ii<'a'+26;ii++){
        for(int ji='a'+0;ji<'a'+26;ji++){
            string i;
            i.push_back((ii));
            string j;
            j.push_back((ji));

            if(ji=='z' || ji=='x' || ji=='s' || ji=='o' ){
                g.add_transition("st0", "st"+i+"p"+j,i,i);
                g.add_transition("st"+i+"p"+j, "st"+i+"p"+j+"v"+"2",j,j);
                g.add_transition("st"+i+"p"+j+"v"+"2", "st"+i+"p"+j+"v"+"3" ,"LAMBDA","e");
                g.add_transition( "st"+i+"p"+j+"v"+"3" , "stf" ,"LAMBDA","s");
            }

            else if( (i=="c" && j=="h") || (i=="s" && j=="h") || (i=="s" && j=="s") ){
                g.add_transition("st0", "st"+i+"p"+j,i,i);
                g.add_transition("st"+i+"p"+j, "st"+i+"p"+j+"v"+"2",j,j);
                g.add_transition("st"+i+"p"+j+"v"+"2", "st"+i+"p"+j+"v"+"3" ,"LAMBDA","e");
                g.add_transition( "st"+i+"p"+j+"v"+"3" , "stf" ,"LAMBDA","s");
            }
            else if(j=="y" && !(i=="a" || i=="e" || i=="i" || i=="o" || i=="u" )){
                g.add_transition("st0", "st"+i+"p"+j,i,i);
                g.add_transition("st"+i+"p"+j, "st"+i+"p"+j+"v"+"2" ,j,"i");
                g.add_transition( "st"+i+"p"+j+"v"+"2" , "st"+i+"p"+j+"v"+"3" ,"LAMBDA","e");
                g.add_transition( "st"+i+"p"+j+"v"+"3" , "stf" ,"LAMBDA","s");
            }
            else if(j=="f"){
                g.add_transition("st0", "st"+i+"p"+j,i,i);
                g.add_transition("st"+i+"p"+j, "st"+i+"p"+j+"v"+"2" ,j,"v");
                g.add_transition( "st"+i+"p"+j+"v"+"2" , "st"+i+"p"+j+"v"+"3" ,"LAMBDA","e");
                g.add_transition( "st"+i+"p"+j+"v"+"3" , "stf" ,"LAMBDA","s");
            }
            else if((i=="f" && j=="e")){
                g.add_transition("st0", "st"+i+"p"+j,i,"v");
                g.add_transition("st"+i+"p"+j, "st"+i+"p"+j+"v"+"2" ,j,"e");
                g.add_transition( "st"+i+"p"+j+"v"+"2" , "stf" ,"LAMBDA","s");
            }
            else{

                g.add_transition("st0", "st"+i+"p"+j,i,i);
                g.add_transition("st"+i+"p"+j, "st"+i+"p"+j+"v"+"2",j,j);
                g.add_transition("st"+i+"p"+j+"v"+"2","stf","LAMBDA","s");
            }

        }
    }


    g.DFS("st0",0,"");
}

string parse_input(bool phase2){

    if(phase2==true){
        in_tape = "";
        fstream newfile;
        ofstream filenew("E:\\university\\languages and automata\\project2finalpresent\\result2.txt",std::ofstream::out);
        newfile.open("E:\\university\\languages and automata\\project2finalpresent\\test.txt",ios::in); //open a file to perform read operation using file object
        if (newfile.is_open()){ //checking whether the file is open
            string tp;
            while(getline(newfile, tp)){ //read data from file object and put it into string.
                in_tape = tp;
                out_tape = "";
                phase_2();
                if(out_tape=="")out_tape = "FAIL\n";
                cout<<out_tape;
                filenew << in_tape << " -> " << out_tape << "\n";
            }
            newfile.close(); //close the file object.
        }
        newfile.close();
        filenew.close();
    }else{
        in_tape = "aaba";
        phase_1();
        if(out_tape=="")out_tape = "FAIL\n";
        cout<<out_tape;
    }
    return 0;

    //cin>>in_tape;
}

int main(){
    int j=0;
    cin >> j;
    parse_input(j);
    return 0 ;
}
