//
// Created by Jan Matějka on 2019-03-07.
//

#ifndef MI_PDP_POSITION_H
#define MI_PDP_POSITION_H

struct Position {
    int x;
    int y;

    Position() {}

    Position(int x, int y): x(x), y(y) { }
};

#endif //MI_PDP_POSITION_H
