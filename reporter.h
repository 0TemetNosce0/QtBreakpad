
#pragma once

#include <QDialog>

namespace Ui {
class ReporterExample;
}

class ReporterExample : public QDialog {
    Q_OBJECT

public:
    explicit ReporterExample(QWidget *parent = 0);
    ~ReporterExample();

public slots:
    void crash();
    void uploadDumps();

private:
    Ui::ReporterExample *ui;
};
