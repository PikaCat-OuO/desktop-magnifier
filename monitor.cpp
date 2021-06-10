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
  // 开启抗锯齿
  painter.setRenderHint(QPainter::SmoothPixmapTransform);
  painter.drawPixmap(this->rect(), this->mScreenShot);
  event->accept();
}

//处理监视器移动问题
void Monitor::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    // 设置鼠标在窗口上为真
    this->mOnSelector = true;
    // 记录窗口的初始位置
    this->mSelectorStartPos = this->frameGeometry().topLeft();
    // 记录鼠标的起始点
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
