#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <cmath>
#include <functional>

using namespace std;

const int N = 4;

struct State
{
    int board[N][N];
    int zero_x, zero_y;
    string path;
    int cost;

    bool operator<(const State &other) const
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (board[i][j] != other.board[i][j])
                {
                    return board[i][j] < other.board[i][j];
                }
            }
        }
        return false;
    }
};

bool isGoal(const State &state)
{
    int target = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == N - 1 && j == N - 1)
            {
                if (state.board[i][j] != 0)
                    return false;
            }
            else
            {
                if (state.board[i][j] != target++)
                    return false;
            }
        }
    }
    return true;
}

int manhattanDistance(const State &state)
{
    int distance = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int value = state.board[i][j];
            if (value != 0)
            {
                int target_x = (value - 1) / N;
                int target_y = (value - 1) % N;
                distance += abs(i - target_x) + abs(j - target_y);
            }
        }
    }
    return distance;
}

bool isSolvable(const State &state)
{
    vector<int> tiles;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (state.board[i][j] != 0)
            {
                tiles.push_back(state.board[i][j]);
            }
        }
    }

    int inversions = 0;
    for (int i = 0; i < tiles.size(); i++)
    {
        for (int j = i + 1; j < tiles.size(); j++)
        {
            if (tiles[i] > tiles[j])
            {
                inversions++;
            }
        }
    }

    int zero_row = N - state.zero_x;
    return (zero_row % 2 == 0) ? (inversions % 2 == 1) : (inversions % 2 == 0);
}

struct CompareCost
{
    bool operator()(const State &a, const State &b)
    {
        return a.cost > b.cost;
    }
};

string solvePuzzleAStar(const State &initial)
{
    if (!isSolvable(initial))
    {
        return "No solution";
    }

    priority_queue<State, vector<State>, CompareCost> pq;
    map<State, bool> visited;

    State start = initial;
    start.cost = manhattanDistance(start);
    pq.push(start);

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    char moves[4] = {'U', 'D', 'L', 'R'};

    while (!pq.empty())
    {
        State current = pq.top();
        pq.pop();

        if (visited[current])
            continue;
        visited[current] = true;

        if (isGoal(current))
        {
            return current.path;
        }

        for (int i = 0; i < 4; i++)
        {
            int nx = current.zero_x + dx[i];
            int ny = current.zero_y + dy[i];

            if (nx >= 0 && nx < N && ny >= 0 && ny < N)
            {
                State neighbor = current;
                swap(neighbor.board[current.zero_x][current.zero_y], neighbor.board[nx][ny]);
                neighbor.zero_x = nx;
                neighbor.zero_y = ny;
                neighbor.path += moves[i];

                if (!visited[neighbor])
                {
                    int g = neighbor.path.length();
                    int h = manhattanDistance(neighbor);
                    neighbor.cost = g + h;
                    pq.push(neighbor);
                }
            }
        }
    }

    return "No solution";
}

int main()
{
    State initial;
    // int test[N][N] = {
    //     {1, 2, 3, 4},
    //     {5, 6, 7, 8},
    //     {9, 10, 11, 12},
    //     {13, 14, 0, 15}};
    // следующий тест считается очень долго
    int test[N][N] = {
        {2, 1, 14, 12},
        {10, 11, 3, 8},
        {15, 5, 0, 7},
        {13, 9, 4, 6}};

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            initial.board[i][j] = test[i][j];
            if (test[i][j] == 0)
            {
                initial.zero_x = i;
                initial.zero_y = j;
            }
        }
    }
    initial.path = "";
    initial.cost = 0;

    cout << "Initial board:" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << (initial.board[i][j] < 10 ? "0" : "") << initial.board[i][j] << " ";
        }
        cout << endl;
    }

    string result = solvePuzzleAStar(initial);

    if (result == "No solution")
    {
        cout << "No solution exists" << endl;
    }
    else
    {
        cout << "Solution: " << result << endl;
        cout << "Number of moves: " << result.length() << endl;
    }

    return 0;
}