#ifndef MOTIONCARD_H
#define MOTIONCARD_H

enum MotionCardErr
{
    MCE_OK
};

enum MotionAxias
{
    MA_XAxis
};

class MotionCard
{
public:
    MotionCard();
    virtual ~MotionCard();

    int open();
    int close();
    int relMove(int axis, int speed, int dist, bool check);
    int absMove(int axis,int speed,int dist,bool check);
};

#endif // MOTIONCARD_H
