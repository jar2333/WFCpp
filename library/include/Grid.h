#pragma once

template<typename T>
class Grid {
  public:
    Grid(int N) {
      for (int i = 0; i < N; i++) {
        grid.push_back(std::vector<T> row(N));
      }
    }
    
    inline int get(int i, int j) {
      return grid[i][j];
    }

    inline int set(int i, int j, T v) {
      grid[i][j] = v;
    }

  private:
    std::vector<std::vector<T>> grid; 
};
