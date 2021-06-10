#include "monitor.h"
#include "ui_monitor.h"

Monitor::Monitor(QWidget *parent)
    : QDialog(parent)
      , ui(new Ui::Monitor)
{
  ui->setupUi(this);
  this->move(0, 0);
  this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  this->setAttribute(Qt::WA_QuitOnClose, false);
}

Monitor::~Monitor() { delete ui; }

void Monitor::setScreenShot(const QPixmap &screenShot) {
  this->mScreenShot = screenShot;
  this->update();
}

void Monitor::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  // ���������
  painter.setRenderHint(QPainter::SmoothPixmapTransform);
  painter.drawPixmap(this->rect(), this->mScreenShot);
  event->accept();
}

//����������ƶ�����
void Monitor::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    // ��������ڴ�����Ϊ��
    this->mOnSelector = true;
    // ��¼���ڵĳ�ʼλ��
    this->mSelectorStartPos = this->frameGeometry().topLeft();
    // ��¼������ʼ��
    this->mMouseStartPoint = event->globalPosition().toPoint();
  }
}

void Monitor::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() == Qt::LeftButton and this->mOnSelector) {
    QPoint delta = event->globalPosition().toPoint() - this->mMouseStartPoint;
    this->move(this->mSelectorStartPos + delta);
  }
}

void Monitor::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    this->mOnSelector = false;
  }
}

void Monitor::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape) {
    event->ignore();
  }
}
