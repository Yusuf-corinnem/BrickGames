#include <QApplication>

#include "menuwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MenuWindow w;
  w.show();
  QPalette pal = QPalette();
  pal.setColor(QPalette::Window, QColor(160, 172, 134));
  w.setAutoFillBackground(true);
  w.setPalette(pal);
  return a.exec();
}
