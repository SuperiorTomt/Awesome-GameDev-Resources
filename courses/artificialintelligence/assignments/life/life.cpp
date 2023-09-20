#include <iostream>

int main() {
  int C, L, T;

  std::cin >> C >> L >> T;

  bool *grid = new bool[C * L];
  bool *newGrid = new bool[C * L];

  for (int i = 0; i < L; i++)
  {
    for (int j = 0; j < C; j++)
    {
      char temp;

      std::cin >> temp;

      if (temp == '#')
        grid[C * i + j] = true;
      else
        grid[C * i + j] = false;

      newGrid[C * i + j] = false;
    }
  }

  // Check for neighbors, update each cell accordingly, and repeat T times
  for (int n = 0; n < T; n++)
  {
    for (int i = 0; i < L; i++)
    {
      for (int j = 0; j < C; j++)
      {
        int xPos;
        int yPos;
        int numNeighbours = 0;

        // -1, -1
        xPos = j - 1;
        yPos = i - 1;
        if (xPos < 0)
          xPos = C - 1;
        if (yPos < 0)
          yPos = L - 1;
        if (grid[C * yPos + xPos])
          numNeighbours++;

        // 0, -1
        xPos = j;
        yPos = i - 1;
        if (yPos < 0)
          yPos = L - 1;
        if (grid[C * yPos + xPos])
          numNeighbours++;

        // 1, -1
        xPos = j + 1;
        yPos = i - 1;
        if (xPos >= C)
          xPos = 0;
        if (yPos < 0)
          yPos = L - 1;
        if (grid[C * yPos + xPos])
          numNeighbours++;

        // -1, 0
        xPos = j - 1;
        yPos = i;
        if (xPos < 0)
          xPos = C - 1;
        if (grid[C * yPos + xPos])
          numNeighbours++;

        // 1, 0
        xPos = j + 1;
        yPos = i;
        if (xPos >= C)
          xPos = 0;
        if (grid[C * yPos + xPos])
          numNeighbours++;

        // -1, 1
        xPos = j - 1;
        yPos = i + 1;
        if (xPos < 0)
          xPos = C - 1;
        if (yPos >= L)
          yPos = 0;
        if (grid[C * yPos + xPos])
          numNeighbours++;

        // 0, 1
        xPos = j;
        yPos = i + 1;
        if (yPos >= L)
          yPos = 0;
        if (grid[C * yPos + xPos])
          numNeighbours++;

        // 1, 1
        xPos = j + 1;
        yPos = i + 1;
        if (xPos >= C)
          xPos = 0;
        if (yPos >= L)
          yPos = 0;
        if (grid[C * yPos + xPos])
          numNeighbours++;

        // Update based on rules
        if (grid[C * i + j] && numNeighbours == 2)
          newGrid[C * i + j] = true;
        else if (numNeighbours == 3)
          newGrid[C * i + j] = true;
        else
          newGrid[C * i + j] = false;
      }
    }

    for (int a = 0; a < C * L; a++) {
      grid[a] = newGrid[a];
    }
  }

  for (int i = 0; i < L; i++)
  {
    for (int j = 0; j < C; j++)
    {
      if (grid[C * i + j])
        std::cout << "#";
      else
        std::cout << ".";
    }

    std::cout << std::endl;
  }

  delete[] grid;
  delete[] newGrid;

  return 0;
}