#include <iostream>
#include <stack>
#include <vector>
#include <cstdint>

// Using stack.h from CSI-281, Data Structures & Algorithms with minor changes
  template <typename T> class Stack {
  private:
    template <typename R> struct Node {
      R mData;
      Node<R> *mNext;

      /* Pre: None
     * Post: This object is initialized using default values
     * Purpose: To initialize node object
     *************************************************************************/
      Node() {
        mData = R();
        mNext = NULL;
      }

      /* Pre: None
     * Post: This object is initialized using specified data
     * Purpose: To initialize node object
     *************************************************************************/
      Node(R data) {
        mData = data;
        mNext = NULL;
      }
    };
    Node<T> *mTop, *mBottom;
    int mCount;

  public:
    Stack();
    ~Stack();
    void clear();
    bool isEmpty();
    T pop();
    T top();
    void push(T data);
  };

  template <typename T> Stack<T>::Stack() {
    mTop = NULL;
    mBottom = NULL;
    mCount = 0;
  }

  template <typename T> Stack<T>::~Stack() { clear(); }

  template <typename T> void Stack<T>::clear() {
    Node<T> *tmp;
    while (mTop != NULL) {
      tmp = mTop;
      mTop = mTop->mNext;
      tmp->mNext = NULL;
      delete tmp;
    }
    mBottom = NULL;
    mCount = 0;
  }

  template <typename T> bool Stack<T>::isEmpty() { return mCount == 0; }

  template <typename T> T Stack<T>::top() { return mTop->mData; }

  template <typename T> T Stack<T>::pop() {
    T data = T();
    Node<T> *tmp;
    if (mTop != NULL) {
      tmp = mTop;
      mTop = mTop->mNext;
      tmp->mNext = NULL;
      data = tmp->mData;
      delete tmp;
      if (mTop == NULL) mBottom = NULL;
      mCount--;
    }
    return data;
  }

  template <typename T> void Stack<T>::push(T data) {
    Node<T> *newNode;
    newNode = new Node<T>(data);
    if (newNode != NULL) {
      if (mTop == NULL) {
        mBottom = newNode;
      } else {
        newNode->mNext = mTop;
      }
      mTop = newNode;
      mCount++;
    }
  }

int randIndex = 0;
int randVec[] = {72, 99, 56, 34, 43, 62, 31, 4,  70, 22, 6,  65, 96, 71, 29, 9,  98, 41, 90, 7,
                 30, 3,  97, 49, 63, 88, 47, 82, 91, 54, 74, 2,  86, 14, 58, 35, 89, 11, 10, 60,
                 28, 21, 52, 50, 55, 69, 76, 94, 23, 66, 15, 57, 44, 18, 67, 5,  24, 33, 77, 53,
                 51, 59, 20, 42, 80, 61, 1,  0,  38, 64, 45, 92, 46, 79, 93, 95, 37, 40, 83, 13,
                 12, 78, 75, 73, 84, 81, 8,  32, 27, 19, 87, 85, 16, 25, 17, 68, 26, 39, 48, 36};

int getRand() {
  int old = randIndex;
  randIndex++;
  randIndex %= 100;
  return randVec[old];
}

struct Point2D {
  bool wallS = true, wallE = true, visited = false;

  int xPos = 0, yPos = 0;
};

void generateMaze(Point2D board[], int C, int L);
std::vector<Point2D> getVisitableNeighbors(Point2D board[], int C, int L, int xPos, int yPos);
void breakWall(Point2D board[], int C, Point2D p1, Point2D p2);
void printBoard(Point2D board[], int C, int L);

int main() {
  uint32_t C, L;

  // Take input for parameters
  std::cin >> C >> L >> randIndex;

  // Initialize maze grid array
  Point2D* mazeGrid = new Point2D[C * L];

  std::stack<Point2D> newStack;

  // Set each tile's coordinates
  for (int i = 0; i < L; i++) {
    for (int j = 0; j < C; j++) {
      mazeGrid[i * C + j].xPos = j;
      mazeGrid[i * C + j].yPos = i;
    }
  }

  // Generate the maze
  generateMaze(mazeGrid, C, L);

  // Output the maze
  printBoard(mazeGrid, C, L);

  delete[] mazeGrid;
}

// to navigate and chose which neighbor no visit in the visitables vector, you have to follow
// something like that: breakWall breaks the wall between 2 points stk is stack data structure
// boardlimits is the limits for the size of the board
// getVisitableNeightbors gives me a vector of directions that can be visted. up, down, left, right
// getNeighbor gets the neighbor in that direction
void generateMaze(Point2D board[], int C, int L) {
  Stack<Point2D> stk;
  stk.push(board[0]);

  while (!stk.isEmpty()) {
    // visit the top
    Point2D temp = stk.top();
    board[temp.yPos * C + temp.xPos].visited = true;

    std::vector<Point2D> visitables = getVisitableNeighbors(board, C, L, temp.xPos, temp.yPos);

    if (visitables.empty())
      stk.pop();  // backtrack
    else if (visitables.size() == 1) {
      // no need to call rand for visitables.
      breakWall(board, C, stk.top(), visitables[0]);
      stk.push(visitables[0]);
    } else {
      // get the rand to get the random one to break the wall
      int i = getRand() % visitables.size();
      breakWall(board, C, stk.top(), visitables[i]);
      stk.push(visitables[i]);
    }
  }
}

std::vector<Point2D> getVisitableNeighbors(Point2D board[], int C, int L, int xPos, int yPos) {
  std::vector<Point2D> neighbors;

  int nbrX, nbrY;

  // UP (x, y - 1)
  nbrX = xPos, nbrY = yPos - 1;
  if (nbrY >= 0)
    if (!board[nbrY * C + nbrX].visited) neighbors.push_back(board[nbrY * C + nbrX]);

  // RIGHT (x + 1, y)
  nbrX = xPos + 1, nbrY = yPos;
  if (nbrX < C)
    if (!board[nbrY * C + nbrX].visited) neighbors.push_back(board[nbrY * C + nbrX]);

  // DOWN (x, y + 1)
  nbrX = xPos, nbrY = yPos + 1;
  if (nbrY < L)
    if (!board[nbrY * C + nbrX].visited) neighbors.push_back(board[nbrY * C + nbrX]);

  // LEFT (x - 1, y)
  nbrX = xPos - 1, nbrY = yPos;
  if (nbrX >= 0)
    if (!board[nbrY * C + nbrX].visited) neighbors.push_back(board[nbrY * C + nbrX]);

  return neighbors;
}

void breakWall(Point2D board[], int C, Point2D p1, Point2D p2) {
  if (p1.xPos < p2.xPos)
    board[p1.yPos * C + p1.xPos].wallE = false;
  else if (p1.xPos > p2.xPos)
    board[p2.yPos * C + p2.xPos].wallE = false;
  else if (p1.yPos < p2.yPos)
    board[p1.yPos * C + p1.xPos].wallS = false;
  else if (p1.yPos > p2.yPos)
    board[p2.yPos * C + p2.xPos].wallS = false;
}

void printBoard(Point2D board[], int C, int L) {
  for (int i = 0; i < C; i++) {
    std::cout << " _";
  }

  std::cout << "  " << std::endl;

  for (int i = 0; i < L; i++) {
    std::cout << "|";
    for (int j = 0; j < C; j++) {
      if (board[i * C + j].wallS)
        std::cout << "_";
      else
        std::cout << " ";

      if (board[i * C + j].wallE)
        std::cout << "|";
      else
        std::cout << " ";
    }
    std::cout << " " << std::endl;
  }
}