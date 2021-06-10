#include "viewfinder.h"
#include "ui_viewfinder.h"

Viewfinder::Viewfinder(QWidget *parent)
    : QDialog(parent), ui(new Ui::Viewfinder) {
  ui->setupUi(this);
  this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  this->setAttribute(Qt::WA_TranslucentBackground);
  this->setAttribute(Qt::WA_QuitOnClose, false);
  // 多线程开启，不断刷新监视器
  QFuture future = QtConcurrent::run([&] {
    forever {
      if (this->mExit) {
        emit exitOk();
        break;
      }
      // 获取选择器左上角的全局位置
      auto [selectorX, selectorY] = this->frameGeometry().topLeft();
      // 根据选择器的位置截屏
      QPixmap screenShot = QGuiApplication::primaryScreen()->grabWindow(
          0, selectorX, selectorY, this->width(), this->height());
      // 发出信号通知监视器把图片设置到监视器上
      emit this->screenShotOk(screenShot);
    }
  });
}

Viewfinder::~Viewfinder() { delete ui; }

void Viewfinder::changeMagnification(bool zoomIn) {
  if (zoomIn) {
    ui->selector->resize(this->width() / 2, this->height() / 2);
    this->resize(this->width() / 2, this->height() / 2);
  } else {
    ui->selector->resize(this->width() * 2, this->height() * 2);
    this->resize(this->width() * 2, this->height() * 2);
  }
}

void Viewfinder::exitProgram() { this->mExit = true; }

//处理取景框移动问题
void Viewfinder::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    // 设置鼠标在窗口上为真
    this->mOnSelector = true;
    // 记录窗口的初始位置
    this->mSelectorStartPos = this->frameGeometry().topLeft();
    // 记录鼠标的起始点
    this->mMouseStartPoint = event->globalPosition().toPoint();
  }
}

void Viewfinder::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() == Qt::LeftButton and this->mOnSelector) {
    QPoint delta = event->globalPosition().toPoint() - this->mMouseStartPoint;
    this->move(this->mSelectorStartPos + delta);
  }
}

void Viewfinder::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    this->mOnSelector = false;
  }
}

void Viewfinder::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape) {
    event->ignore();
  }
}
