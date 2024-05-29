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
    void action();
};

//プロトタイプ宣言
void initAll();
void printAll();
void turn();
void mainLoop();
char getKeyChar();

//グローバル宣言
Map map;
Player player;

//実装
int main(int argc, const char * argv[]) {
    initAll();
    mainLoop();
    return 0;
}

void initAll() {
    map.init();
    player.init();
}

void printAll() {
    map.print();
    player.print();
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
    printAll();
}

char getKeyChar() {
    char c;
    cout << "? " << flush;
    cin >> c;
    return c;
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
            cellPrint(x,y);
        }
        cout << endl;
    }
}

void Map::cellPrint(int x, int y) {
    int e = data[x][y];
    if (e == ROCK) { cout << '#' << ' '; }
    else if (e == EMPTY) { cout << '.' << ' '; } 
    else if (e == GOAL) { cout << 'G' << ' '; }
    else { cout << 'E' << ' '; }
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

    x = targetX; y = targetY;
    return true;
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
    
    moveTo(dx,dy);
}
