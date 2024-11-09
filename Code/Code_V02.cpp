#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

const string solvedConfig = "WWWWWWWWWYYYYYYYYYBBBBBBBBBGGGGGGGGGRRRRRRRRROOOOOOOOO";

int manhattanDistance(const string& cubeState)
{
    int distance = 0;
    // Compare each face of the cube and calculate Manhattan distance for each piece
    for (int i = 0; i < 54; ++i)
    {
        if (cubeState[i] != solvedConfig[i])
        {
            // Find the target position of cubeState[i] in the solved configuration
            int targetIndex = solvedConfig.find(cubeState[i]);

            // Calculate row and column differences for Manhattan distance
            int currentRow = i / 9, currentCol = i % 9;
            int targetRow = targetIndex / 9, targetCol = targetIndex % 9;

            distance += abs(currentRow - targetRow); // Row difference
            distance += abs(currentCol - targetCol); // Column difference
        }
    }
    return distance;
}

// Helper function to rotate a 3x3 face clockwise
void rotateFaceClockwise(string& state, int startIndex) {
    char temp = state[startIndex];
    state[startIndex] = state[startIndex + 6];
    state[startIndex + 6] = state[startIndex + 8];
    state[startIndex + 8] = state[startIndex + 2];
    state[startIndex + 2] = temp;

    temp = state[startIndex + 1];
    state[startIndex + 1] = state[startIndex + 3];
    state[startIndex + 3] = state[startIndex + 7];
    state[startIndex + 7] = state[startIndex + 5];
    state[startIndex + 5] = temp;
}

// Helper function to rotate a 3x3 face counterclockwise
void rotateFaceCounterclockwise(string& state, int startIndex) {
    char temp = state[startIndex];
    state[startIndex] = state[startIndex + 2];
    state[startIndex + 2] = state[startIndex + 8];
    state[startIndex + 8] = state[startIndex + 6];
    state[startIndex + 6] = temp;

    temp = state[startIndex + 1];
    state[startIndex + 1] = state[startIndex + 5];
    state[startIndex + 5] = state[startIndex + 7];
    state[startIndex + 7] = state[startIndex + 3];
    state[startIndex + 3] = temp;
}

// Function to apply a move to the cube configuration
string applyMove(const string& cubeState, const string& move) {
    string newState = cubeState;

    if (move == "U") {
        rotateFaceClockwise(newState, 18); // Rotate Up face clockwise
        // Adjust the edges
        swap(newState[0], newState[36]);
        swap(newState[1], newState[37]);
        swap(newState[2], newState[38]);
        swap(newState[0], newState[45]);
        swap(newState[1], newState[46]);
        swap(newState[2], newState[47]);
        swap(newState[0], newState[9]);
        swap(newState[1], newState[10]);
        swap(newState[2], newState[11]);
    }
    else if (move == "U'") {
        rotateFaceCounterclockwise(newState, 18); // Rotate Up face counterclockwise
        // Adjust the edges
        swap(newState[0], newState[11]);
        swap(newState[1], newState[10]);
        swap(newState[2], newState[9]);
        swap(newState[0], newState[47]);
        swap(newState[1], newState[46]);
        swap(newState[2], newState[45]);
        swap(newState[0], newState[36]);
        swap(newState[1], newState[37]);
        swap(newState[2], newState[38]);
    }
    if (move == "D") {
        rotateFaceClockwise(newState, 27); // Rotate Down face clockwise
        // Adjust the edges
        swap(newState[6], newState[45]);
        swap(newState[7], newState[46]);
        swap(newState[8], newState[47]);
        swap(newState[6], newState[15]);
        swap(newState[7], newState[16]);
        swap(newState[8], newState[17]);
        swap(newState[6], newState[51]);
        swap(newState[7], newState[52]);
        swap(newState[8], newState[53]);
    }
    else if (move == "D'") {
        rotateFaceCounterclockwise(newState, 27); // Rotate Down face counterclockwise
        // Adjust the edges
        swap(newState[6], newState[53]);
        swap(newState[7], newState[52]);
        swap(newState[8], newState[51]);
        swap(newState[6], newState[17]);
        swap(newState[7], newState[16]);
        swap(newState[8], newState[15]);
        swap(newState[6], newState[45]);
        swap(newState[7], newState[46]);
        swap(newState[8], newState[47]);
    }
    if (move == "F") {
        rotateFaceClockwise(newState, 9); // Rotate Front face clockwise
        // Adjust the edges
        char temp1 = newState[6], temp2 = newState[7], temp3 = newState[8];

        newState[6] = newState[45];
        newState[7] = newState[48];
        newState[8] = newState[51];

        newState[45] = newState[24];
        newState[48] = newState[23];
        newState[51] = newState[22];

        newState[24] = newState[38];
        newState[23] = newState[37];
        newState[22] = newState[36];

        newState[36] = temp1;
        newState[37] = temp2;
        newState[38] = temp3;
    }
    else if (move == "F'") {
        rotateFaceCounterclockwise(newState, 9); // Rotate Front face counterclockwise
        // Adjust the edges
        char temp1 = newState[6], temp2 = newState[7], temp3 = newState[8];

        newState[6] = newState[36];
        newState[7] = newState[37];
        newState[8] = newState[38];

        newState[36] = newState[22];
        newState[37] = newState[23];
        newState[38] = newState[24];

        newState[22] = newState[51];
        newState[23] = newState[48];
        newState[24] = newState[45];

        newState[51] = temp3;
        newState[48] = temp2;
        newState[45] = temp1;
    }
    if (move == "B") {
        rotateFaceClockwise(newState, 18); // Rotate Back face clockwise
        // Adjust the edges
        char temp1 = newState[0], temp2 = newState[1], temp3 = newState[2];

        newState[0] = newState[47];
        newState[1] = newState[50];
        newState[2] = newState[53];

        newState[47] = newState[29];
        newState[50] = newState[28];
        newState[53] = newState[27];

        newState[29] = newState[42];
        newState[28] = newState[39];
        newState[27] = newState[36];

        newState[42] = temp1;
        newState[39] = temp2;
        newState[36] = temp3;
    }
    else if (move == "B'") {
        rotateFaceCounterclockwise(newState, 18); // Rotate Back face counterclockwise
        // Adjust the edges
        char temp1 = newState[0], temp2 = newState[1], temp3 = newState[2];

        newState[0] = newState[42];
        newState[1] = newState[39];
        newState[2] = newState[36];

        newState[42] = newState[27];
        newState[39] = newState[28];
        newState[36] = newState[29];

        newState[27] = newState[53];
        newState[28] = newState[50];
        newState[29] = newState[47];

        newState[53] = temp3;
        newState[50] = temp2;
        newState[47] = temp1;
    }
    if (move == "L") {
            rotateFaceClockwise(newState, 27); // Rotate Left face clockwise
            // Adjust the edges
            char temp1 = newState[0], temp2 = newState[3], temp3 = newState[6];

            newState[0] = newState[18];
            newState[3] = newState[21];
            newState[6] = newState[24];

            newState[18] = newState[45];
            newState[21] = newState[48];
            newState[24] = newState[51];

            newState[45] = newState[15];
            newState[48] = newState[12];
            newState[51] = newState[9];

            newState[15] = temp1;
            newState[12] = temp2;
            newState[9] = temp3;
    }
    else if (move == "L'") 
    {
        rotateFaceCounterclockwise(newState, 27); // Rotate Left face counterclockwise
        // Adjust the edges
        char temp1 = newState[0], temp2 = newState[3], temp3 = newState[6];
            newState[0] = newState[15];
            newState[3] = newState[12];
            newState[6] = newState[9];

            newState[15] = newState[51];
            newState[12] = newState[48];
            newState[9] = newState[45];

            newState[51] = newState[24];
            newState[48] = newState[21];
            newState[45] = newState[18];

            newState[24] = temp3;
            newState[21] = temp2;
            newState[18] = temp1;
    }
    if (move == "R") {
            rotateFaceClockwise(newState, 36); // Rotate Right face clockwise
            // Adjust the edges
            char temp1 = newState[2], temp2 = newState[5], temp3 = newState[8];

            newState[2] = newState[9];
            newState[5] = newState[12];
            newState[8] = newState[15];

            newState[9] = newState[45];
            newState[12] = newState[48];
            newState[15] = newState[51];

            newState[45] = newState[53];
            newState[48] = newState[50];
            newState[51] = newState[47];

            newState[53] = temp1;
            newState[50] = temp2;
            newState[47] = temp3;
        }
        else if (move == "R'") {
            rotateFaceCounterclockwise(newState, 36); // Rotate Right face counterclockwise
            // Adjust the edges
            char temp1 = newState[2], temp2 = newState[5], temp3 = newState[8];

            newState[2] = newState[53];
            newState[5] = newState[50];
            newState[8] = newState[47];

            newState[53] = newState[45];
            newState[50] = newState[48];
            newState[47] = newState[51];

            newState[45] = newState[9];
            newState[48] = newState[12];
            newState[51] = newState[15];

            newState[9] = temp1;
            newState[12] = temp2;
            newState[15] = temp3;
        }
    return newState;

};

// A* Node structure to hold state, cost, and heuristic
struct Node
{
    string state;      // The Rubik's Cube configuration
    int gCost;         // Cost from the start node (number of moves taken)
    int hCost;         // Heuristic cost (Manhattan distance)
    string move;       // Move that led to this state
    Node* parent;      // Pointer to the parent node for path reconstruction

    // Constructor
    Node(string s, int g, int h, string m = "", Node* p = nullptr)
        : state(s), gCost(g), hCost(h), move(m), parent(p) {}

    // fCost = g + h
    int fCost() const { return gCost + hCost; }

    // Comparison operator for priority queue (min-heap based on fCost)
    bool operator>(const Node& other) const
    {
        return fCost() > other.fCost();
    }
};// A* search function to solve the Rubik's Cube
vector<string> solveRubiksCube(const string& startState)
{
    priority_queue<Node, vector<Node>, greater<Node>> openList;
    unordered_set<string> closedList;
    map<string, pair<string, string>> cameFrom; // Map state -> (previous state, move)
    map<string, int> gCosts;

    openList.push({ startState, 0, manhattanDistance(startState), "" });
    gCosts[startState] = 0;

    while (!openList.empty()) {
        // Get the node with the lowest fCost from openList
        Node currentNode = openList.top();
        openList.pop();

        // Check if the current node's state is the goal state
        if (currentNode.state == goalState) {
            std::cout << "Solution found! Moves: " << currentNode.path << std::endl;
            break;
        }

        // Add the current node's state to closedList to mark it as visited
        closedList.insert(currentNode.state);

        // Expand the current node (add this section here)
        for (const auto& move : possibleMoves) {
            // 1. Apply move to get a new state
            std::string newState = applyMove(currentNode.state, move);

            // 2. Check if this new state is already in closedList
            if (closedList.find(newState) != closedList.end()) {
                continue; // Skip this state if already visited
            }

            // 3. Compute costs
            int gCost = currentNode.gCost + 1; // Increment gCost by 1 for each move
            int hCost = calculateHeuristic(newState, goalState); // Calculate heuristic cost
            int fCost = gCost + hCost;

            // Create a new node for the resulting state
            Node newNode(newState, currentNode.path + move + " ", gCost, hCost);

            // Add the new node to openList (priority queue based on fCost)
            openList.push(newNode);
        }
    }



    return {}; // No solution found
}
int main()
{
    string scrambledCube;
    cout << "Enter the scrambled Rubik's Cube configuration: ";
    cin >> scrambledCube;

    if (scrambledCube.length() != 54)
    {
        cout << "Invalid input! Please make sure the configuration has exactly 54 characters." << endl;
        return 1;
    }

    vector<string> solution = solveRubiksCube(scrambledCube);

    if (!solution.empty())
    {
        cout << "Solution found!" << endl;
        cout << "Moves: ";
        for (const string& move : solution)
        {
            cout << move << " ";
        }
        cout << endl;
    }
    else {
        cout << "No solution found!" << endl;
    }

    return 0;
}