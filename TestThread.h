
#pragma once
#include <QThread>

class TestThread : public QThread {
    Q_OBJECT

public:
    TestThread(bool buggy, uint seed);
    virtual ~TestThread();

protected:
    virtual void run();

private slots:
    void crash();

private:
    bool m_buggy;
};
