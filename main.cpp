#include "monitor.h"
#include "settingbar.h"
#include "viewfinder.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  Monitor monitor;
  Viewfinder viewfinder;
  SettingBar settingBar;

  // 截完图了就通知监视器更新图片
  app.connect(&viewfinder, &Viewfinder::screenShotOk, &monitor,
              &Monitor::setScreenShot);
  // 改变方法倍数时通知选择器改变放大倍数
  app.connect(&settingBar, &SettingBar::changeMagnification, &viewfinder,
              &Viewfinder::changeMagnification);
  // 如果settingBar被关闭了就通知Viewfinder停止任务
  app.connect(&app, &QApplication::lastWindowClosed, &viewfinder,
              &Viewfinder::exitProgram);
  // 当收到Viewfinder的可以退出信号后，关闭窗口，程序结束
  app.connect(&viewfinder, &Viewfinder::exitOk, &app, &QApplication::quit);

  viewfinder.show();
  monitor.show();
  settingBar.show();

  return app.exec();
}
