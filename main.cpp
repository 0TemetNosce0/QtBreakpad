#include "TestThread.h"
#include "Widget.h"
#include "reporter.h"

#include <QApplication>
#include <QDateTime>
#include <QTimer>

#include <handler/QBreakpadHandler.h>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    Widget w;
//    w.show();

//    QBreakpadInstance.setDumpPath("d:/crashes");

//    qsrand(QDateTime::currentDateTime().toTime_t());
//    TestThread t1(false, qrand());
//    TestThread t2(true, qrand());

//    t1.start();
//    t2.start();

//    QTimer::singleShot(3000, qApp, SLOT(quit()));

//    return a.exec();
//}

//report
int main (int argc, char *argv[])
{
    QApplication app (argc, argv);

    QCoreApplication::setApplicationName("ReporterExample");
    QCoreApplication::setApplicationVersion("0.0.1");
    QCoreApplication::setOrganizationName("OrgName");
    QCoreApplication::setOrganizationDomain("name.org");

    // Set directory to store dumps and url to upload
    QBreakpadInstance.setDumpPath("crashes");
    // Set server type for uploading
#if defined(SOCORRO)
    QBreakpadInstance.setUploadUrl(QUrl("http://[your.site.com]/submit"));
#elif defined(CALIPER)
    QBreakpadInstance.setUploadUrl(QUrl("http://[your.site.com]/crash_upload"));
#endif

    // Create the dialog and show it
    ReporterExample example;
    example.show();

    // Run the app
    return app.exec();
}
