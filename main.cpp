#include <QtWidgets/QApplication>
#include <QMainWindow>
#include "mainWin.h"
#include "audiosource.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   MainWindow mWindow;
   audioSource audioInput;
   mWindow.resize( 800, 400 );
   mWindow.startTimer(100);
   mWindow.show();

   return app.exec();
}
