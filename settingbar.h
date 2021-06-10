#pragma once

#include "viewfinder.h"
#include <QDialog>

namespace Ui {
class SettingBar;
}

class SettingBar : public QDialog
{
  Q_OBJECT

public:
  explicit SettingBar(QWidget *parent = nullptr);
  ~SettingBar();

signals:
  void changeMagnification(bool zoomIn);

private:
  Ui::SettingBar *ui;

private slots:
  void on_ZoomIn_clicked();

  void on_ZoomOut_clicked();
};
