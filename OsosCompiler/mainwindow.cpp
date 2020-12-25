#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scanner.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
//    Input = new  QPlainTextEdit("{ Sample program in TINY language computes factorial }\n"
//                                "read x; {input an integer }\n"
//                                "if 0 < x then { don’t compute if x <= 0 }\n"
//                                "    fact := 1;\n"
//                                "    repeat\n"
//                                "        fact := fact * x;\n"
//                                "        x := x - 1\n"
//                                "    until x = 0;\n"
//                                "    write fact { output factorial of x }\n"
//                                "end ", this);
//    Output = new QPlainTextEdit(this);
    Toolbar = new QToolBar(this);
    //Splitter = new QSplitter(Qt::Vertical,this);
    scanner = new Scanner();
//    Output->setReadOnly(true);
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    X = 0;
    Y = 0;
}
void MainWindow::init_toolbar()
{
    this->addToolBar(Qt::TopToolBarArea,Toolbar);
    QAction * ScanAction = Toolbar->addAction("Scan");
    connect(ScanAction,SIGNAL(triggered(bool)),this,SLOT(start_Scan()));
    QAction * ParseAction = Toolbar->addAction("Parse");
    connect(ParseAction,SIGNAL(triggered(bool)),this,SLOT(parse()));
    QAction * OpenAction = Toolbar->addAction("Load File");
    connect(OpenAction,SIGNAL(triggered(bool)),this,SLOT(start_Scan_File()));
    //signal
}

void MainWindow::IterateOverTree(Node *Current)
{
    //colors

    QBrush cyanBrush(Qt::cyan);
    QBrush magentaBrush(Qt::red);
    QPen   black(Qt::black);
    QPen   line(Qt::yellow);
    black.setWidth(2);
    line.setWidth(3);

    //texts
    QString QTitle  = QString::fromStdString(Current->Title);
    QString QDetails  = QString::fromStdString(Current->Details);
    /*if((Current->Left == NULL) && (Current->Right == NULL) && (Current->ElsePart == NULL) && (Current->NextTo.size() == 0) )
    {
       scene->addLine((W/2+X),(H+Y),(TempX+W/2),TempY,line);
    }*/
    int bedayaX = X+40;
    int bedayaY= Y+50;
    if(Current->Type == Current->Box)
    {
        scene->addRect(X, Y,80,50,black,magentaBrush);
        scene->addText(QTitle, QFont())->setPos(X+10,Y+10);
        scene->addText(QDetails, QFont())->setPos(X+10,Y+25);
    }
    if(Current->Type == Current->Circle)
    {
        scene->addEllipse(X,Y,80,50,black,cyanBrush);
        scene->addText(QTitle, QFont())->setPos(X+10,Y+10);
        scene->addText(QDetails, QFont())->setPos(X+10,Y+25);
    }

    if (Current->Left != NULL)
    {
        scene->addLine(bedayaX,bedayaY,X+40,Y+100,line);
        Y+=100;
        TempY = Y;
        IterateOverTree(Current->Left);
        Y-=100;
    }
    if (Current->Right != NULL)
    {
        scene->addLine(bedayaX,bedayaY,X+140,Y+100,line);
        X+=100;
        Y+=100;
        TempX= X;
        TempY =Y;
        IterateOverTree(Current->Right);
        Y-=100;
    }
    if (Current->ElsePart != NULL)
    {
        scene->addLine(bedayaX,bedayaY,X+140,Y+100,line);
        X+=100;
        Y+=100;
        TempX= X;
        TempY =Y;
        IterateOverTree(Current->ElsePart);
        Y-=100;
    }
    if (Current->NextTo.size() != 0)
    {
        list<Node *> L = Current->NextTo;
        for (list<Node *>::iterator it = L.begin(); it != L.end(); ++it)
        {
            QPen   lin(Qt::red);
            scene->addLine(bedayaX+40,bedayaY-25,X+100,Y+25,lin);
            X+=100;
            TempX = X;

            IterateOverTree(*it);
        }
    }
}

void MainWindow::init_ui()
{
    //ui->Input->setPlaceholderText("{ Sample program in TINY language computes factorial }read x; {input an integer }if 0 < x then {don`t compute if x <= 0 }\nfact := 1;repeat fact := fact * x; x := x - 1 until x = 0; write fact { output factorial of x }end");
    ui->Output->setReadOnly(true);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::parse()
{
    ui->graphicsView->clearFocus();
    scene->clearSelection();
    scene->clear();
    scene->update();
    X = 0;
    Y = 0;
    TempY=0;
    TempX=0;

    QString result = this->scanner->printTokenList(ui->Input->toPlainText().toStdString());

    Node* Tree = new Node();
    Parser P;
    P.setDrawFlag(true);
    string parserIn = this->scanner->getParserInput();
    cout << "From Here" << endl;
    cout << parserIn << endl;
    P.cutting_parsing_input(parserIn);
    Tree = P.prog();
    if(P.getDrawFlag()){
    IterateOverTree(Tree);
    }
    delete Tree;
}

void MainWindow::start_Scan()
{

    QString result = this->scanner->printTokenList(ui->Input->toPlainText().toStdString());

    ui->Output->clear();
    ui->Output->setPlainText(result);
}
void MainWindow::start_Scan_File()
{
    QString result = this->scanner->getStringFile();
    ui->Input->setPlainText(result);

    ui->Output->clear();

}
