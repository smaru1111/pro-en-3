#include <iostream>
using namespace std;

class Map {
  public:
    static const int ROCK = 0;
    static const int EMPTY = 1;
    static const int GOAL = 2;

    static const int XSIZE = 13;
    static const int YSIZE = 11;

    int data[XSIZE][YSIZE];
    
    void init();
    void print();
    void cellPrint(int x, int y);
};

class Player {
  public:
    static const int INIT_HP = 100;

    int x, y;
    int hp;
    
    void init();
    void print();
    bool cellPrint(int x, int y);
    bool moveTo(int dx, int dy);   
    void attackTo(int dx, int dy);
    void action();
};

class Monster {
  public:
    static const int INIT_HP = 150;

    int x, y;
    int hp;
    
    void init(int x, int y);
    void print();
    bool cellPrint(int x, int y);
    bool moveTo(int dx, int dy);   
    void attackTo(int dx, int dy);
    void action();
};

//プロトタイプ宣言
void initAll();
void printAll();
void mainLoop();
void turn();
char getKeyChar();
int signum(int a);

//グローバル宣言
Map map;
Player player;
Monster monster1;
Monster monster2;

//実装
int main(int argc, const char * argv[]) {
    initAll();
    mainLoop();
    return 0;
}

void initAll() {
    map.init();
    player.init();
    monster1.init(1,Map::YSIZE-2);
    monster2.init(Map::XSIZE-2,1);
}

void printAll() {
    map.print();
    player.print();
    monster1.print();
    monster2.print();
    cout << endl;
}

void mainLoop() {
    printAll();
    while (true) {
        turn();
    }
}

void turn() {
    player.action();
    monster1.action();
    monster2.action();
    printAll();
}

char getKeyChar() {
    char c;
    cout << "? " << flush;
    cin >> c;
    return c;
}

int signum(int a) {
    if (a < 0) return -1;
    else if (a > 0) return 1;
    else return 0;
}


void Map::init() {
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
            if (player.cellPrint(x,y)) { continue; }
            if (monster1.cellPrint(x,y)) { continue; }
            if (monster2.cellPrint(x,y)) { continue; }
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



void Player::init() {
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

    if (map.data[targetX][targetY] == Map::ROCK) { return false; }
    if ((targetX == monster1.x)&&(targetY == monster1.y)) { return false; }
    if ((targetX == monster2.x)&&(targetY == monster2.y)) { return false; }

    x = targetX; y = targetY;
    return true;
}

void Player::attackTo(int dx, int dy) {
    int targetX = x+dx, targetY = y+dy;
    if ((targetX == monster1.x)&&(targetY == monster1.y)) { monster1.hp -= 20; }
    if ((targetX == monster2.x)&&(targetY == monster2.y)) { monster2.hp -= 20; }
}

void Player::action() {
    int dx, dy;
    switch (getKeyChar()) {
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

void Monster::init(int x_, int y_) {
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
    
    if (map.data[targetX][targetY] == Map::ROCK) { return false; }
    if ((targetX == player.x)&&(targetY == player.y)) { return false; } 
    if ((targetX == monster1.x)&&(targetY == monster1.y)) { return false; }
    if ((targetX == monster2.x)&&(targetY == monster2.y)) { return false; }

    x = targetX; y = targetY;
    return true;
}

void Monster::attackTo(int dx, int dy) {
    int targetX= x+dx, targetY = y+dy;
    if ((targetX == player.x)&&(targetY == player.y)) { player.hp -= 30; }
}

void Monster::action() {    
    int dx = signum(player.x - x);
    int dy = signum(player.y - y);

    if (!moveTo(dx,dy)) { attackTo(dx,dy); }
}

