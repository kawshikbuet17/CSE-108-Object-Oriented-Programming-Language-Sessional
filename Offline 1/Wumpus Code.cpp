#include <iostream>
#include<ctime>
#include<cstdlib>
#include <cmath>
#include <sstream>
//#include<stdio.h>

using namespace std;

#define GRIDSIZE 4
#define UP      0
#define DOWN    2
#define LEFT    3
#define RIGHT   1
#define MAX_SHOTS 3


string tostring(int x) {
    std::string out_string;
    std::stringstream ss;
    ss << x;
    return ss.str();
}


class Position {

    int x, y;

public:

    Position (int x, int y) {
        this->x = x;
        this->y = y;
    }

    Position() {
    }

    // Modify the following four so that the resulting position does not leave the grid
    void moveRight() {
        if(x<3)
            x++;
    }

    void moveLeft() {
        if(x>0)
            x--;
    }

    void moveUp() {
        if(y<3)
            y++;
    }

    void moveDown() {
        if(y>0)
            y--;
    }

    bool isAdjacent(Position p) {
        //implement the function
        if(abs(x-p.x)==1&&abs(y-p.y)==0)
            return 1;
        if(abs(x-p.x)==0&&abs(y-p.y)==1)
            return 1;
        else
            return 0;
    }

    bool isSamePoint(Position p) {
        //implement the function
        if(abs(x-p.x)==0&&abs(y-p.y)==0)
            return 1;
        else
            return 0;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

};



class Wumpus {

    bool killed;
    Position p;

public:

    Wumpus(int x, int y) {
        p = Position(x, y);
        killed = false;
    }

    Wumpus() {
        int t, t1;
        t = rand()%4;
        t1 = rand()%4;
        if(t1==0&&t==0)
            t1=1;
        p  = Position(t, t1);
        killed = false;
        //...
    }

    bool wumkilled()
    {
        return killed;
    }

    void kill() {
        killed = true;
    }

    Position getPosition() {
        return p;
    }
    void setPosition(int x, int y)
    {
        p = Position(x, y);
    }

};

class Pit {
    Position p;
public:
    Pit() {
        int t, t1;
        t = rand()%4;
        t1 = rand()%4;
        if(t==0&&t1==0)
            t1 = 1;
        p = Position(t, t1);
    }
    Position getPosition() {
        return p;
    }
    void setPosition(int x, int y)
    {
        p = Position(x, y);
    }
};

class Player {

    int direction;
    int total_shots;
    bool killed;
    Position p;

public:

    Player() {
        //...
        p = Position(0, 0);
        killed = false;
        total_shots = MAX_SHOTS;
        direction=UP;

    }
    void Bullet()
    {
        if(total_shots>0)
            total_shots--;
    }
    int BulletLeft()
    {
        return total_shots;
    }

    void turnLeft() {
        //...

        direction+=3;
        direction%=4;


    }

    void turnRight() {
        //...
        direction=(direction+1)%4;

    }

    void moveForward() {
        //...
        if(direction==UP)
            p.moveUp();
        else if(direction==DOWN)
            p.moveDown();

        else if(direction==LEFT)
            p.moveLeft();
        else
            p.moveRight();
    }

    bool isAdjacent(Position pos) {
        return p.isAdjacent(pos);
    }

    bool isSamePoint(Position pos) {
        return p.isSamePoint(pos);
    }

    void kill() {
        killed = true;
    }
    Position getPosition()
    {
        return p;
    }

    int getDirection()
    {
        return direction;
    }

    string getPositionInfo() {
        return "Player is now at " + tostring(p.getX()) + ", " + tostring(p.getY());
    }

    string getDirectionInfo() {
        string s;
        if (direction == UP) s = "up";
        if (direction == DOWN) s = "down";
        if (direction == LEFT) s = "left";
        if (direction == RIGHT) s = "right";
        return "Player is moving at direction: " + s;
    }

};



class WumpusWorld {

private:

    Player player;
    Pit pit;
    Wumpus wumpus;
    Position gold_position;
    bool ended;

public:

    WumpusWorld() {
        //...
        Position temp;
        temp = pit.getPosition();
        while(temp.isSamePoint(wumpus.getPosition()))
        {
            wumpus.setPosition((temp.getX()+1)%4, temp.getY());
        }

        Position temp2;
        temp2 = wumpus.getPosition();

        Position temp3 = Position(0, 0);
        gold_position = Position(rand()%4, rand()%4);
        while(gold_position.isSamePoint(temp)||gold_position.isSamePoint(temp2)||gold_position.isSamePoint(temp3))
            gold_position = Position(rand()%4, rand()%4);
        ended = false;

    }

    WumpusWorld(int wumpus_x, int wumpus_y) {
        //...
        wumpus.setPosition(wumpus_x, wumpus_y);
        int gold_x, gold_y;
        gold_x =rand()%4;
        gold_y = rand()%4;
        while((gold_x==wumpus_x&&gold_y==wumpus_y)||(gold_x==0&&gold_y==0))
        {
            gold_x =rand()%4;
            gold_y = rand()%4;
        }
        gold_position = Position(gold_x, gold_y);
        int t, t1;
        t = rand()%4;
        t1 = rand()%4;
        while((t==0 && t1==0)||(t==wumpus_x&&t1==wumpus_y)||(t==gold_x&&t1==gold_y))
        {
            t = rand()%4;
            t1 = rand()%4;
        }
        pit.setPosition(t, t1);
        ended = false;
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y) {

        //...
        wumpus.setPosition(wumpus_x, wumpus_y);
        gold_position = Position(gold_x, gold_y);
        int t, t1;
        t = rand()%4;
        t1 = rand()%4;
        while((t==0 && t1==0)||(t==wumpus_x&&t1==wumpus_y)||(t==gold_x&&t1==gold_y))
        {
            t = rand()%4;
            t1 = rand()%4;
        }
        pit.setPosition(t, t1);
        ended = false;
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y, int pit_x, int pit_y) {
        //...
        gold_position = Position(gold_x, gold_y);
        wumpus = Wumpus(wumpus_x, wumpus_y);
        pit.setPosition(pit_x, pit_y);
        ended = false;

    }


    void moveForward() {
        player.moveForward();
        return showGameState();
    }

    void turnLeft() {
        player.turnLeft();
        return showGameState();
    }

    void turnRight() {
        player.turnRight();
        return showGameState();
    }

    void shoot() {
        //...
        if(player.BulletLeft()>0){
        player.Bullet();
        cout<<"Bullet Left: "<<player.BulletLeft()<<endl;
        Position temp = player.getPosition();
        Position temp2 = wumpus.getPosition();
            //cout<<"Player direction"<<player.getDirection()<<endl;
            //cout<<temp2.getX()<<endl;
            if((player.getDirection()==UP) && (temp.getX()==temp2.getX()) && (temp2.getY()>temp.getY()))
                {
                    wumpus.kill();
                    cout<<"WumpusKilled"<<endl;
                }
            if((player.getDirection()==RIGHT) && (temp.getY()==temp2.getY()) && (temp2.getX()>temp.getX()))
                {
                    wumpus.kill();
                    cout<<"WumpusKilled"<<endl;
                }
            if((player.getDirection()==LEFT) && (temp.getY()==temp2.getY()) && (temp2.getX()<temp.getX()))
                {
                    wumpus.kill();
                    cout<<"WumpusKilled"<<endl;
                }
            if((player.getDirection()==DOWN) && (temp.getX()==temp2.getX()) && (temp2.getY()<temp.getY()))
                {
                    wumpus.kill();
                    cout<<"WumpusKilled"<<endl;
                }
        }

    }

    void showGameState() {
        cout << player.getPositionInfo() << endl;
        cout << player.getDirectionInfo() << endl;

        if (player.isAdjacent(wumpus.getPosition())&&wumpus.wumkilled()==0) {
            cout << "stench!" << endl;
        }

        if (player.isAdjacent(pit.getPosition())) {
            cout << "Breeze!" << endl;
        }

        if (player.isSamePoint(wumpus.getPosition())&&wumpus.wumkilled() != 1) {
            cout << "Player is killed by WUMPUS!" << endl;
            player.kill();
            cout << "Game over!" << endl;
            ended = true;
        }
        if (player.isSamePoint(pit.getPosition())) {
            cout << "Player is killed by PIT!" << endl;
            player.kill();
            cout << "Game over!" << endl;
            ended = true;
        }

        if (player.isSamePoint(gold_position)) {
            cout << "Got the gold!" << endl;
            cout << "Game ended, you won!" << endl;
            ended = true;
        }
    }

    bool isOver() {
        return ended;
    }

};


int main()
{
    srand(time(NULL));
    int c, wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y;

    // take the six integers input from file
    FILE *fp;

    fp = fopen("wumpusfile.txt", "r");
    if(fp==NULL)
    {
        cout<<"No file. So play with random value..."<<endl;
        WumpusWorld w;
        w.showGameState();
        while (!w.isOver()) {
            cout << "1: move forward" << endl;
            cout << "2: Turn left" << endl;
            cout << "3: Turn right" << endl;
            cout << "4: Shoot" << endl;
            cin >> c;
            if (c == 1) {w.moveForward();}
            else if (c == 2) {w.turnLeft();}
            else if (c == 3) {w.turnRight();}
            else if (c == 4) {w.shoot();}
        }
        fclose(fp);
        return 0;
    }
    else
    {
        cout<<"Got the input file. Play now..."<<endl;
        fscanf(fp, "%d %d %d %d %d %d", &wumpus_x, &wumpus_y, &gold_x, &gold_y, &pit_x, &pit_y );
        WumpusWorld w(wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y);
        w.showGameState();
        while (!w.isOver()) {
            cout << "1: move forward" << endl;
            cout << "2: Turn left" << endl;
            cout << "3: Turn right" << endl;
            cout << "4: Shoot" << endl;
            cin >> c;
            if (c == 1) {w.moveForward();}
            else if (c == 2) {w.turnLeft();}
            else if (c == 3) {w.turnRight();}
            else if (c == 4) {w.shoot();}
        }
        fclose(fp);
        return 0;
    }
}
