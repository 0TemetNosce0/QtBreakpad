
#include "reporter.h"
#include "TestThread.h"
#include "ui_reporter.h"

#include <QDateTime>
#include <QTimer>

#include <handler/QBreakpadHandler.h>

ReporterExample::ReporterExample(QWidget *parent) : QDialog(parent), ui(new Ui::ReporterExample) {
    // Create and configure the user interface
    ui->setupUi(this);
    this->setWindowTitle("ReporterExample (qBreakpad v." + QBreakpadHandler::version() + ")");
    ui->urlLineEdit->setText(QBreakpadInstance.uploadUrl());

    ui->dumpFilesTextEdit->appendPlainText(QBreakpadInstance.dumpFileList().join("\n"));

    // Force crash app when the close button is clicked
    connect(ui->crashButton, SIGNAL(clicked()), this, SLOT(crash()));

    // upload dumps when the updates button is clicked
    connect(ui->uploadButton, SIGNAL(clicked()), this, SLOT(uploadDumps()));
}

ReporterExample::~ReporterExample() {
    delete ui;
}

void ReporterExample::crash() {
    qsrand(QDateTime::currentDateTime().toTime_t());
    TestThread t1(false, qrand());
    TestThread t2(true, qrand());

    t1.start();
    t2.start();

    QTimer::singleShot(3000, qApp, SLOT(quit()));
}

void ReporterExample::uploadDumps() {
    QBreakpadInstance.sendDumps();
}
