#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QToolBar>
#include <Qt>
#include <QSplitter>
#include <scanner.h>
#include <QString>
#include <QDebug>
#include <scanner.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QPlainTextEdit *Input;
    QPlainTextEdit *Output;
    QToolBar *Toolbar;
    QSplitter *Splitter ;
    Scanner *scanner;
public:
    MainWindow(QWidget *parent = nullptr);
    void init_toolbar(void);
    void init_ui(void);
    ~MainWindow();
public slots:
    void start_Scan();
    void start_Scan_File();

};
#endif // MAINWINDOW_H
