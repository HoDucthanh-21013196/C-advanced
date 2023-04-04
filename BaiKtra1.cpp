#include <bits/stdc++.h>
using namespace std;
;
struct Node
{
    int id;
    float x, y;
};

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        cout << "Invalid input";
        exit(0);
    }
    string path;
    int nodeID;
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == string("-i"))
        {
            nodeID = stoi(argv[i + 1]);
        }
        if (string(argv[i]) == string("-p"))
        {
            path = argv[i + 1];
        }
    }
    vector<Node> allNodes;
    ifstream inFile;
    inFile.open(path);
    string Line;
    getline(inFile, Line);
    while (getline(inFile, Line))
    {
        Node n;
        istringstream iss(Line);
        string token;
        getline(iss, token, ',');
        n.id = stoi(token);
        getline(iss, token, ',');
        n.x = stod(token);
        getline(iss, token, ',');
        n.y = stod(token);
        allNodes.push_back(n);
    }
    Node n;
    for (auto x : allNodes)
    {
        if (x.id == nodeID)
        {
            n = x;
            break;
        }
    }
    float max_kc = -999, min_kc = 999;
    int max_id = -1, min_id = 1;
    for (auto &otherNode : allNodes)
    {
        if (nodeID == otherNode.id)
        {
            continue;
        }
        // Tim max_kc, max_id
        float kc = sqrt(pow(otherNode.x - n.x, 2) + pow(otherNode.y - n.y, 2));
        float kc1 = sqrt(pow(otherNode.x - n.x, 2) + pow(otherNode.y - n.y, 2));
        if (kc > max_kc)
        {
            max_kc = kc;
            max_id = otherNode.id;
        }
        // Tim min_kc, min_id
        if (kc1 < min_kc)
        {
            min_kc = kc1;
            min_id = otherNode.id;
        }
    }
    ofstream outFile;
    outFile.open("C:/File_Code/data1.txt");
    outFile << max_id << " " << max_kc << endl;
    outFile << min_id << " " << min_kc << endl;
    inFile.close();
    outFile.close();
}