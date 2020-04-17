#ifndef BIRD_H
#define BIRD_H

class bird
{
public:
    float x, y, dy;
    bool lose = false;
    float acc = 0.005;
    float speed = 0;

    void set_bird(int, int);

} bird1;

void bird::set_bird(int X, int Y)
{
    x = X;
    y = Y;
}

#endif