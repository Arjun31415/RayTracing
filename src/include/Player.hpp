#include <vector>
class Player
{
    int x, y, r;
    const static int DELTA = 5;

  public:
    Player();
    Player(int, int, int);
    void setPosition(int x, int y);
    std::pair<int, int> getPosition();
    void moveX();
    void moveY();
};
