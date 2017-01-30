#include <QApplication>

#include "view.h"
#include "lifemodel.h"
#include "controller.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    Parser parser(&model);
    View viewer(&model);

    Controller controller(&model,&viewer);

    viewer.show();
    return a.exec();
}


//gui tread

