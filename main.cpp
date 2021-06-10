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

  // ����ͼ�˾�֪ͨ����������ͼƬ
  app.connect(&viewfinder, &Viewfinder::screenShotOk, &monitor,
              &Monitor::setScreenShot);
  // �ı䷽������ʱ֪ͨѡ�����ı�Ŵ���
  app.connect(&settingBar, &SettingBar::changeMagnification, &viewfinder,
              &Viewfinder::changeMagnification);
  // ���settingBar���ر��˾�֪ͨViewfinderֹͣ����
  app.connect(&app, &QApplication::lastWindowClosed, &viewfinder,
              &Viewfinder::exitProgram);
  // ���յ�Viewfinder�Ŀ����˳��źź󣬹رմ��ڣ��������
  app.connect(&viewfinder, &Viewfinder::exitOk, &app, &QApplication::quit);

  viewfinder.show();
  monitor.show();
  settingBar.show();

  return app.exec();
}
