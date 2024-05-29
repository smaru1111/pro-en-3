#include <iostream>
using namespace std;

//定数宣言
const int ROCK = 0;
const int EMPTY = 1;
const int GOAL = 2;

const int MAP_XSIZE = 13;
const int MAP_YSIZE = 11;

const int PLAYER_INIT_HP = 100;

//型宣言
struct Map {
    int data[MAP_XSIZE][MAP_YSIZE];
};

struct Player {
    int x, y;
    int hp;
};

//プロトタイプ宣言
void initAll();
void printAll();
void turn();
void mainLoop();
char getKeyChar();

void mapInit();
void mapPrint();
void mapCellPrint(int x, int y);

void playerInit();
void playerPrint();
bool playerCellPrint(int x, int y);
bool playerMoveTo(int dx, int dy);
void playerAction();

//グローバル変数
Map map;
Player player;

//実装
int main(int argc, const char * argv[]) {
    initAll();
    mainLoop();
    return 0;
}

void initAll() {
    mapInit();
    playerInit();
}

void printAll() {
    mapPrint();
    playerPrint();
    cout << endl;
}

void mainLoop() {
    printAll();
    while (true) {
        turn();
    }
}

void turn() {
    playerAction();
    printAll();
}

char getKeyChar() {
    char c;
    cout << "? " << flush;
    cin >> c;
    return c;
}


void mapInit() {
    for (int x = 0; x < MAP_XSIZE; x++) {  
        for (int y = 0; y < MAP_YSIZE; y++) {
            if ((x == 0)||(x == MAP_XSIZE-1)||
               (y == 0)||(y == MAP_YSIZE-1)||
               ((abs(x-MAP_XSIZE/2) <= 1)&&
                (abs(y-MAP_YSIZE/2) <= 1))) { 
                
                map.data[x][y] = ROCK; 
            }
            else { map.data[x][y] = EMPTY; }
        }
    }
    map.data[MAP_XSIZE-2][MAP_YSIZE-2] = GOAL;
}

void mapPrint() {
    for (int y = 0; y < MAP_YSIZE; y++) {
        for (int x = 0; x < MAP_XSIZE; x++) {
            if (playerCellPrint(x,y)) { continue; }
            mapCellPrint(x,y);
        }
        cout << endl;
    }
}

void mapCellPrint(int x, int y) {
    int e = map.data[x][y];
    if (e == ROCK) { cout << '#' << ' '; }
    else if (e == EMPTY) { cout << '.' << ' '; } 
    else if (e == GOAL) { cout << 'G' << ' '; }
    else { cout << 'E' << ' '; }
}


void playerInit() {
    player.x = 1; player.y = 1;
    player.hp = PLAYER_INIT_HP;
}

void playerPrint() {
    cout << "Player : (" << player.x << "," << player.y << ") " << player.hp << endl;
}

bool playerCellPrint(int x, int y) {
    if ((x == player.x)&&(y == player.y)) {
        cout << '@' << ' ';
        return true;
    }
    return false;
}

bool playerMoveTo(int dx, int dy) {
    int targetX = player.x+dx, targetY = player.y+dy;

    if (map.data[targetX][targetY] == ROCK) { return false; }

    player.x = targetX; player.y = targetY;
    return true;
}

void playerAction() {
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
    
    playerMoveTo(dx,dy);
}
