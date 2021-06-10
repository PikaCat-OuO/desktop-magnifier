#include "settingbar.h"
#include "ui_settingbar.h"

SettingBar::SettingBar(QWidget *parent)
    : QDialog(parent), ui(new Ui::SettingBar) {
  ui->setupUi(this);
  this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint |
                       Qt::WindowTitleHint);
  this->setAttribute(Qt::WA_QuitOnClose);
  this->move(
      (QGuiApplication::primaryScreen()->geometry().width() - this->width()) /
          2,
      0);
}

SettingBar::~SettingBar()
{
  delete ui;
}

void SettingBar::on_ZoomIn_clicked() { emit this->changeMagnification(true); }

void SettingBar::on_ZoomOut_clicked() { emit this->changeMagnification(false); }
