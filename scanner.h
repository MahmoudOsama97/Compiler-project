#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include <string>
#include <fstream>
#include <QString>
#include <QDebug>
#include <vector>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
using namespace std;
typedef enum
{
    idle,
    start,
    num,
    id,
    assign,
    comment,
    special,
    reserved,
    error
} stateType;

class Scanner
{
private:

public:
    Scanner();
    void done(void);
    QString getStringFile(void);
    QString printTokenList(string input);
    bool isDigit(char);
    bool isLetter(char);
    bool isSpace(char);
    bool isSymbol(char);
};

#endif // SCANNER_H
