#ifndef IUIDELEGATE_H
#define IUIDELEGATE_H

class IUIDelegate
{
public:
    IUIDelegate() {}
    virtual ~IUIDelegate() {}

    virtual void onSwitchStateClicked() = 0;
};

struct Stats
{
public:
    int total;
    int errors;
    bool on;
    int rpm;
};

class ICoreDelegate
{
public:
    ICoreDelegate() {}
    virtual ~ICoreDelegate() {}

    virtual void onStatisticsUpdated(const Stats& stats) = 0;
};




#endif // IUIDELEGATE_H
