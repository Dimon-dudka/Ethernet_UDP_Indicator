#include "widget_manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    widget_manager App;
    App.show();
   
    return a.exec();
}
