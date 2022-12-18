#include <map>
#include <vector>

struct Node {
    int num;
    vector<int> paths;
}

using namespace std;

void initializeVect(vector<Node> vectorToInit);
int maxPathBetweenNodes(const Node &sourceNode, const Node &targetNode, const vector<Node> &vectorToSearch);

int main() {
    int N = 10;
    int E = 20;

    map<int, vector<int>> myGraph;

}

void initializeVect(map<int, vector<int> mapToInit);

int findMaxPath(const map<int, vector<int> &mapToSearch){
    int maxPath = 0;
    int maxPathCurNodes = 0;

    for (auto itExt = mapToSearch.begin(); itExt != mapToSearch.end(); itExt++)
        for (auto itInt = mapToSearch.begin(); itInt != mapToSearch.end(); itInt++)
            if ((*itExt).first == (*itInt).first)
                continue;

            maxPathCurNodes = maxPathBetweenNodes(decltype(mapToSearch)::iterator sourceNodeIt, decltype(mapToSearch)::iterator targetNodeIt, mapToSearch)
            if (maxPath < maxPathCurNodes)
                maxPath = maxPathCurNodes;
        }

    return maxPath;
}

int maxPathBetweenNodes(const Node &sourceNode, const Node &targetNode, const map<int, vector<int>  &mapToSearch){

    for (auto &nextPathToGo : sourceNode)

        if (nextPathToGo == targetNode.num)
            return 1;
        else
            maxPathBetweenNodex( , , vectorToSearch) + 1;



}