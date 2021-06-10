#include "viewfinder.h"
#include "ui_viewfinder.h"

Viewfinder::Viewfinder(QWidget *parent)
    : QDialog(parent), ui(new Ui::Viewfinder) {
  ui->setupUi(this);
  this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  this->setAttribute(Qt::WA_TranslucentBackground);
  this->setAttribute(Qt::WA_QuitOnClose, false);
  // ���߳̿���������ˢ�¼�����
  QFuture future = QtConcurrent::run([&] {
    forever {
      if (this->mExit) {
        emit exitOk();
        break;
      }
      // ��ȡѡ�������Ͻǵ�ȫ��λ��
      auto [selectorX, selectorY] = this->frameGeometry().topLeft();
      // ����ѡ������λ�ý���
      QPixmap screenShot = QGuiApplication::primaryScreen()->grabWindow(
          0, selectorX, selectorY, this->width(), this->height());
      // �����ź�֪ͨ��������ͼƬ���õ���������
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

//����ȡ�����ƶ�����
void Viewfinder::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    // ��������ڴ�����Ϊ��
    this->mOnSelector = true;
    // ��¼���ڵĳ�ʼλ��
    this->mSelectorStartPos = this->frameGeometry().topLeft();
    // ��¼������ʼ��
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
