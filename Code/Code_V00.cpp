#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>
#include <cmath>
#include <map>

using namespace std;

// Directions for the Rubik's Cube moves (U, D, F, B, L, R)
const vector<string> moves = { "U", "D", "F", "B", "L", "R" };

// The solved configuration of the Rubik's Cube
const string solvedConfig = "WWWWWWWWWYYYYYYYYYBBBBBBBBBGGGGGGGGGRRRRRRRRROOOOOOOOO";

// Function to calculate Manhattan distance heuristic
int manhattanDistance(const string& cubeState) 
{
    int distance = 0;
    // Compare each face of the cube and calculate Manhattan distance for each piece
    for (int i = 0; i < 54; ++i)
    {
        if (cubeState[i] != solvedConfig[i])
        {
            distance += abs(i / 9 - solvedConfig[i] / 9); // Row difference
            distance += abs(i % 9 - solvedConfig[i] % 9); // Column difference
        }
    }
    return distance;
}

// Function to apply a move to the cube configuration
string applyMove(const string& cubeState, const string& move) 
{
    // (The exact code for applying the move would be specific to how you represent the cube)
    // This is a placeholder for applying a move and updating the cube state
    string newState = cubeState; // Implement the move logic here
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
