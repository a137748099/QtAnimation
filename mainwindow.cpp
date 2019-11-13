#include "mainwindow.h"
#include <QTabWidget>
#include <QDesktopWidget>
#include <QApplication>
#include "beatanimal.h"
#include "animaldemo1.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QRect screenRect = QApplication::desktop()->screenGeometry();
    this->resize(screenRect.size());
    initUi();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initUi()
{
    m_pTabWidget = new QTabWidget(this);
    m_pTabWidget->setGeometry(0, 0, this->width(), this->height());

    m_pBeatAnimalWidget = new BeatAnimal(this->width(), this->height());
    m_pTabWidget->addTab(m_pBeatAnimalWidget, tr("BeatAnimal"));

    m_pAnimalDemo1 = new AnimalDemo1(this->width(), this->height());
    m_pTabWidget->addTab(m_pAnimalDemo1, "demo1");

}
