#pragma once
#include "monitor.h"
#include <QAtomicInt>
#include <QDialog>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QtConcurrent/QtConcurrent>

namespace Ui {
class Viewfinder;
}

class Viewfinder : public QDialog
{
  Q_OBJECT

public:
  explicit Viewfinder(QWidget *parent = nullptr);
  ~Viewfinder();

signals:
  // ����ͼ��
  void screenShotOk(QPixmap &screenShot);
  // ���߳��˳����
  void exitOk();

public slots:
  // �ı�Ŵ���
  void changeMagnification(bool zoomIn);
  // �ӵ��˳���֪ͨ������һ��
  void exitProgram();

protected:
  // ��ס���⴦�ƶ�����
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  // ESC�����˳�
  void keyPressEvent(QKeyEvent *event) override;

private:
  Ui::Viewfinder *ui;
  // �����������߳�Ҫ�˳���
  QAtomicInt mExit{false};
  // �������ƶ��¼���صı���
  // ������¼����Ƿ���ѡ������
  bool mOnSelector{false};
  // ������¼ѡ�����ĳ�ʼλ��
  QPoint mSelectorStartPos{this->frameGeometry().topLeft()};
  QPoint mMouseStartPoint;
};
