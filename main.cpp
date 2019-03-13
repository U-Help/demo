#include "widget.h"
#include <QApplication>
#include "malloc.h"
#include "wen.h"

using namespace std;

QTimer *timer=NULL;
QTimer *tim=NULL;
int *score=NULL;  //score is used for saveing the score of each exercise
extern int total;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    int x;
    for(x=0;x<10;x++)
        printf(x);
    w.show();    //displaying UI

    return a.exec();
}
