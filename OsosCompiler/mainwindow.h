#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QPushButton>
#include <QToolBar>
#include <Qt>
#include <QSplitter>
#include <scanner.h>
#include <QString>
#include <QDebug>
#include <scanner.h>
#include "parser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    //QPlainTextEdit *Input;
    //QPlainTextEdit *Output;
    QToolBar *Toolbar;
    QSplitter *Splitter ;
    Scanner *scanner;

    //QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rect;
    QGraphicsTextItem *textTitle;
    QGraphicsTextItem *textDetails;

    int TempX;
    int TempY;

    int W = 80;
    int H =50;

    int X;
    int Y;
public:
    MainWindow(QWidget *parent = nullptr);
    void IterateOverTree(Node* Current);
    void init_toolbar(void);
    void init_ui(void);
    ~MainWindow();
public slots:
    void start_Scan();
    void start_Scan_File();
    void parse();

};
#endif // MAINWINDOW_H
