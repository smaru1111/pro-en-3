#include <iostream>
using namespace std;

//クラス名の宣言
class Map;
class Player;
class Monster;

class Game {
  public:
    Map *map;
    Player *player;
    Monster *monster1;
    Monster *monster2;
    
    void init();
    void print();
    void mainLoop();
    void turn();
    static char getKeyChar();
    static int signum(int a);
};


class Map {
  public:
    static const int ROCK = 0;
    static const int EMPTY = 1;
    static const int GOAL = 2;

    static const int XSIZE = 13;
    static const int YSIZE = 11;

    Game *game;
    int data[XSIZE][YSIZE];
    
    void init(Game *game);
    void print();
    void cellPrint(int x, int y);
};

class Player {
  public:
    static const int INIT_HP = 100;

    Game *game;
    int x, y;
    int hp;
    
    void init(Game *game);
    void print();
    bool cellPrint(int x, int y);
    bool moveTo(int dx, int dy);   
    void attackTo(int dx, int dy);
    void action();
};

class Monster {
  public:
    static const int INIT_HP = 150;

    Game *game;
    int x, y;
    int hp;
    
    void init(Game *game, int x, int y);
    void print();
    bool cellPrint(int x, int y);
    bool moveTo(int dx, int dy);   
    void attackTo(int dx, int dy);
    void action();
};

//プロトタイプ宣言

//グローバル宣言

//実装
int main(int argc, const char * argv[]) {
    Game *game = new Game;
    game->init();
    game->mainLoop();
    return 0;
}

void Game::init() {
    map = new Map;
    map->init(this);
    player = new Player;
    player->init(this);
    monster1 = new Monster;
    monster1->init(this, 1, Map::YSIZE-2);
    monster2 = new Monster;
    monster2->init(this, 1, Map::YSIZE-2);
}

void Game::print() {
    map->print();
    player->print();
    monster1->print();
    monster2->print();
    cout << endl;
}

void Game::turn() {
    player->action();
    monster1->action();
    monster2->action();
    print();
}

void Game::mainLoop() {
    print();
    while (true) {
        turn();
    }
}

char Game::getKeyChar() {
    char c;
    cout << "? " << flush;
    cin >> c;
    return c;
}

int Game::signum(int a) {
    if (a < 0) return -1;
    else if (a > 0) return 1;
    else return 0;
}

void Map::init(Game *game_) {
    game = game_;
    for (int x = 0; x < XSIZE; x++) {  
        for (int y = 0; y < YSIZE; y++) {
            if ((x == 0)||(x == XSIZE-1)||
               (y == 0)||(y == YSIZE-1)||
               ((abs(x-XSIZE/2) <= 1)&&
                (abs(y-YSIZE/2) <= 1))) { 
                
                data[x][y] = ROCK; 
            }
            else { data[x][y] = EMPTY; }
        }
    }
    data[XSIZE-2][YSIZE-2] = GOAL;
}
    
void Map::print() {
    for (int y = 0; y < YSIZE; y++) {
        for (int x = 0; x < XSIZE; x++) {
            if (game->player->cellPrint(x,y)) { continue; }
            if (game->monster1->cellPrint(x,y)) { continue; }
            if (game->monster2->cellPrint(x,y)) { continue; }
            cellPrint(x,y);
        }
        cout << endl;
    }
}

void Map::cellPrint(int x, int y) {
    int e = data[x][y];
    if (e == ROCK)       { cout << '#' << ' '; }
    else if (e == EMPTY) { cout << '.' << ' '; } 
    else if (e == GOAL)  { cout << 'G' << ' '; }
    else                 { cout << 'E' << ' '; }
}

void Player::init(Game *game_) {
    game = game_;
    x = 1; y = 1;
    hp = INIT_HP;
}

void Player::print() {
    cout << "Player : (" << x << "," << y << ") " 
         << hp << endl;
}

bool Player::cellPrint(int x_, int y_) {
    if ((x_ == x)&&(y_ == y)) {
        cout << '@' << ' ';
        return true;
    }
    return false;
}

bool Player::moveTo(int dx, int dy) {
    int targetX = x+dx, targetY = y+dy;

    if (game->map->data[targetX][targetY] == Map::ROCK) { return false; }
    if ((targetX == game->monster1->x)&&(targetY == game->monster1->y)) { return false; } //!
    if ((targetX == game->monster2->x)&&(targetY == game->monster2->y)) { return false; } //!

    x = targetX; y = targetY;
    return true;
}

void Player::attackTo(int dx, int dy) {
    int targetX = x+dx, targetY = y+dy;
    if ((targetX == game->monster1->x)&&(targetY == game->monster1->y)) { game->monster1->hp -= 20; }
    if ((targetX == game->monster2->x)&&(targetY == game->monster2->y)) { game->monster2->hp -= 20; }
}

void Player::action() {
    int dx, dy;
    switch (Game::getKeyChar()) {
        case 'z': dx = -1; dy = +1; break;
        case 'x': dx =  0; dy = +1; break;
        case 'c': dx = +1; dy = +1; break;
        case 'a': dx = -1; dy =  0; break;
        case 'd': dx = +1; dy =  0; break;
        case 'q': dx = -1; dy = -1; break;
        case 'w': dx =  0; dy = -1; break;
        case 'e': dx = +1; dy = -1; break;
        default:  dx =  0; dy =  0; 
    }
    
    if (!moveTo(dx,dy)) { attackTo(dx,dy); }
}

void Monster::init(Game *game_, int x_, int y_) {
    game = game_;
    x = x_; y = y_;
    hp = INIT_HP;
}

void Monster::print() {
    cout << "Monster: (" << x << "," << y << ") " 
         << hp << endl;
}

bool Monster::cellPrint(int x_, int y_) {
    if ((x_ == x)&&(y_ == y)) {
        cout << 'M' << ' ';
        return true;
    }
    return false;
}

bool Monster::moveTo(int dx, int dy) {
    int targetX = x+dx, targetY = y+dy;
    
    if (game->map->data[targetX][targetY] == Map::ROCK) { return false; }
    if ((targetX == game->player->x)&&(targetY == game->player->y)) { return false; } 
    if ((targetX == game->monster1->x)&&(targetY == game->monster1->y)) { return false; } //!
    if ((targetX == game->monster2->x)&&(targetY == game->monster2->y)) { return false; } //!

    x = targetX; y = targetY;
    return true;
}

void Monster::attackTo(int dx, int dy) {
    int targetX = x+dx, targetY = y+dy;
    if ((targetX == game->player->x)&&(targetY == game->player->y)) { game->player->hp -= 30; }
}

void Monster::action() {    
    int dx = Game::signum(game->player->x - x);
    int dy = Game::signum(game->player->y - y);

    if (!moveTo(dx,dy)) { attackTo(dx,dy); }
}

