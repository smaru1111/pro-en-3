# pro-en-3
## 1. ターン毎にプレイヤーの HP が c だけ上昇する。
変更前

```c
void Game::turn()
{
    player->action();
    monster1->action();
    monster2->action();
    print();
}
```

変更後
```c  
void Game::turn()
{
    player->hp += 30;
    player->action();
    monster1->action();
    monster2->action();
    print();
}
```

## 2-1. モンスターの HP が 0 以下になったならば、モンスターは活動を停止する。モンスターを消滅させる必要はない（そのプログラム改造は少し難しい）。
変更前

```c
void Game::turn()
{
    player->hp += 30;
    player->action();
    monster1->action();
    monster2->action();
    print();
}

void Monster::print()
{
    cout << "Monster : (" << x << "," << y << ") "
         << hp << endl;
}

bool Monster::cellPrint(int x_, int y_)
{
    if ((x_ == x) && (y_ == y))
    {
        cout << 'M' << ' ';
        return true;
    }
    return false;
}

```

変更後
```c
void Game::turn()
{
    player->hp += 30;
    player->action();
    if (monster1->hp > 0)
    {
        monster1->action();
    }
    if (monster2->hp > 0)
    {
        monster2->action();
    }
    print();
}

void Monster::print()
{
    if (hp > 0)
    {
        cout << "Monster : (" << x << "," << y << ") "
             << hp << endl;
    }
}

bool Monster::cellPrint(int x_, int y_)
{
    if ((x_ == x) && (y_ == y) && hp > 0)
    {
        cout << 'M' << ' ';
        return true;
    }
    return false;
}

```



## 2-2. プレーヤーがゴール（右下のセル）に辿り着いたならば、ゲームが終了する。
追加

```c
void Game::checkGameFinish()
{
    if (player->x == Map::XSIZE - 2 && player->y == Map::YSIZE - 2)
    {
        cout << "Game Over: Player reached the goal." << endl;
        exit(0);
    }
}
```
修正前
```c
void Game::mainLoop()
{
    print();
    while (true)
    {
        turn();
    }
}
```
  
修正後
```c
void Game::mainLoop()
{
    print();
    while (true)
    {
        turn();
        checkGameFinish();
    }
}
```

## 2-3. プレイヤーの HP が 0 以下になったならば、ゲームが終了する
修正前
```c
void Game::checkGameFinish()
{
    if (player->x == Map::XSIZE - 2 && player->y == Map::YSIZE - 2)
    {
        cout << "Game Over: Player reached the goal." << endl;
        exit(0);
    }
}
```

修正後

```c
void Game::checkGameFinish()
{
    if (player->hp <= 0)
    {
        cout << "Game Over: Player's HP reached 0." << endl;
        exit(0);
    }
    if (player->x == Map::XSIZE - 2 && player->y == Map::YSIZE - 2)
    {
        cout << "Game Over: Player reached the goal." << endl;
        exit(0);
    }
}
```
