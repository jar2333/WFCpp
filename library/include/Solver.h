#include <Side>
#include <Grid>

#include <map>
#include <vector>
#include <list>
#include <functional>

class Solver {
  public:
    Solver(std::vector<int> tiles, std::map<Side, std::vector<int>> constraints, int seed=0);
    void setSeed(int seed);
    Grid<int> solve(int N);

    //calls registered function with tile in collapsed grid slot
    void onCollapse(std::function<void(int, int, int)> callback);

    //calls registered function with possible tiles in collapsed grid slot
    void onPropagate(std::function<void(std::vector<int>, int, int)> callback); 

  private:
    std::list<std::function<void(int, int, int)>> collapse_callbacks;
    std::list<std::function<void(int, int, int)>> propagate_callbacks;
};