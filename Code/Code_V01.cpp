#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

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

    // Similarly, implement other moves "L", "L'", "R", "R'"
    return newState;
}
// A* Node structure to hold state, cost, and heuristic
struct Node 
{
    string state;
    int gCost; // Cost from start (number of moves)
    int hCost; // Heuristic value (Manhattan distance)
    int fCost() const { return gCost + hCost; } // f = g + h
    string move; // The move that led to this state

    bool operator>(const Node& other) const 
    { // Min-heap based on fCost
        return fCost() > other.fCost();
    }
};

// A* search function to solve the Rubik's Cube
vector<string> solveRubiksCube(const string& startState) 
{
    priority_queue<Node, vector<Node>, greater<Node>> openList; // Min-heap
    unordered_set<string> closedList; // Set to track visited states
    map<string, string> cameFrom; // To store the path
    map<string, int> gCosts; // To track the cost from the start for each state

    // Initialize the start node
    openList.push({ startState, 0, manhattanDistance(startState), "" });
    gCosts[startState] = 0;

    while (!openList.empty()) 
    {
        Node currentNode = openList.top();
        openList.pop();

        // If we reach the solved state, we reconstruct the path
        if (currentNode.state == solvedConfig) 
        {
            vector<string> solutionMoves;
            string state = currentNode.state;
            while (cameFrom.find(state) != cameFrom.end())
            {
                solutionMoves.push_back(cameFrom[state]);
                state = applyMove(state, cameFrom[state]);
            }
            reverse(solutionMoves.begin(), solutionMoves.end()); // Reverse to get correct order
            return solutionMoves;
        }

        closedList.insert(currentNode.state);

        // Try all possible moves (U, D, F, B, L, R)
        for (const string& move : moves) {
            string newState = applyMove(currentNode.state, move);
            if (closedList.find(newState) == closedList.end()) 
            {
                int tentativeGCost = currentNode.gCost + 1;
                if (gCosts.find(newState) == gCosts.end() || tentativeGCost < gCosts[newState])
                {
                    gCosts[newState] = tentativeGCost;
                    int newHCost = manhattanDistance(newState);
                    openList.push({ newState, tentativeGCost, newHCost, move });
                    cameFrom[newState] = move;
                }
            }
        }
    }

    return {}; // If no solution is found (which should not happen for a solvable cube)
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
