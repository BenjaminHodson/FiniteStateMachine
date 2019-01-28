#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using namespace std;

ifstream input;

//Node Class
class Node
{
public:
    map<char, Node*> mMap;
    map<char, Node*>::iterator mit;
    string state;
    bool accepted = false;
    Node(string str)
    {state = str;}
    void mapCreate(char c, Node *n);
};


//Map Creator
    void Node::mapCreate(char c, Node *n)
    {
        mMap[c]=n;
    }


//Input Text File
ifstream inputF(char*file)
{
    ifstream inputs;
    inputs.open(file, ifstream::in);
    if(!inputs.is_open())
    {
        cerr << "File: " << file << " can't be opened" << endl;
        exit(1);
    }
    return inputs;
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Main
int main(int argc, char **argv)
{
input = inputF(argv[1]);
string firstNode, secondNode;
char transition;
map<string, Node*> mapState;            //Maps state
map<string, Node*>::iterator itState;           //Iterator state
vector<string> vState;


//Argument error handler
    if(argc != 4)
    {
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }

    while(input)
    {
         input >> firstNode >> transition >> secondNode;        //Reading from text file

         itState = mapState.find(firstNode);
         if(itState == mapState.end())          //if states are there
         {
             mapState[firstNode] = new Node(firstNode);
         }
         itState = mapState.find(secondNode);
         if(itState == mapState.end())
         {
                mapState[secondNode] = new Node(secondNode);
         }
         mapState[firstNode]->mapCreate(transition, mapState[secondNode]);
    }

    //printing FSM
    cout << "Finite State Machine" << endl << "Initial State: " << argv[2] << endl << "Final State: " << argv[3] << endl;
    for(itState = mapState.begin(); itState != mapState.end(); itState++)
    {
        string state = itState->first;
        cout << state << ":";
        Node *n = mapState[state];
        for (n->mit = n->mMap.begin(); n->mit != n->mMap.end(); n->mit++)
        {
         char nextTransition = n->mit->first;
         string nextState = n->mit->second->state;
         cout << "[" << nextTransition << ", " << nextState << "]";
        }
        cout << endl;
    }

    cout << "=========================" << endl;
    char c;
    mapState[argv[3]]->accepted = true;
    string current = mapState[argv[2]]->state;

    vState.push_back(current);
    cout << "Enter test: " << endl;

    while(cin >> c)
    {
        mapState[current]->mit = mapState[current]->mMap.find(c);
        if(mapState[current]->mit == mapState[current]->mMap.end())
        {
            cerr << "Input not accepted" << endl;
            return 1;
        }
        current = mapState[current]->mMap[c]->state;
        vState.push_back(current);
    }
    cout << "State Path: " << endl;
    for (int i = 0; i < vState.size() ; ++i)
    {
        cout << vState[i] << " ";
    }
    if(mapState[vState[vState.size()-1]]->accepted)
    {
        cout << "Accept!" << endl;
    }else{
        cout << "Reject!" << endl;
    }
   input.close();      //Closing the input file

return 0;
}