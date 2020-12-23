#include <scanner.h>


string token;
stateType state = idle;
string out = "";
string parserInput = "";
ofstream ofile;
string RES_WORDS[8] = { "if","then","else","end","repeat","until","read","write" };

bool Scanner::isDigit(char d) { return (d >= '0' && d <= '9'); }
bool Scanner::isLetter(char l) { return (l >= 'a' && l <= 'z' || l >= 'A' && l <= 'Z'); }
bool Scanner::isSpace(char s) { return (s == ' ' || s == '\t' || s == '\n'); }
bool Scanner::isSymbol(char c) { return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '(' || c == ')' || c == ';'); }
Scanner::Scanner()
{

}

string Scanner::getParserInput()
{
    return parserInput;
}

void Scanner::done()
{
    if (state == start)
    {
        ofile << "unexpected output at token \n"
              << token;
        out += "unexpected output at token \n" + token;
    }
    else if (state == num)
    {
        ofile << token << " , NUMBER \n";
        out += token + " , NUMBER \n";
        parserInput += "number{" + token + "} ";
    }
    else if (state == id)
    {
        ofile << token << " , IDENTIFIER \n";
        out += token + " , IDENTIFIER \n";
        parserInput += "identifier{" + token + "} ";
    }
    else if (state == comment)
    {
        ofile << token << " , COMMENT \n";
        out += token + " , COMMENT \n";
    }
    else if (state == special)
    {
        if (token==":="){
            ofile << token << " , ASSIGN \n";
            out += token + " , ASSIGN \n";
            parserInput += ":= ";
        }
        else if(token=="-"){
            ofile << token << " , MINUS \n";
            out += token + " , MINUS \n";
            parserInput += "- ";
        }
        else if(token=="+"){
            ofile << token << " , PLUS \n";
            out += token + " , PLUS \n";
            parserInput += "+ ";
        }
        else if(token==";"){
            ofile << token << " , SEMICOLON \n";
            out += token + " , SEMICOLON \n";
            parserInput += "; ";
        }
        else if(token=="("){
            ofile << token << " , OPENBRACKET \n";
            out += token + " , OPENBRACKET \n";
            parserInput += "( ";
        }
        else if(token==")"){
            ofile << token << " , CLOSEDBRACKET \n";
            out += token + " , CLOSEDBRACKET \n";
            parserInput += ") ";
        }
        else if(token=="*"){
            ofile << token << " , MULT \n";
            out += token + " , MULT \n";
            parserInput += "* ";
        }
        else if(token=="/"){
            ofile << token << " , DIV \n";
            out += token + " , DIV \n";
            parserInput += "/ ";
        }
        else if(token=="="){
            ofile << token << " , EQUAL \n";
            out += token + " , EQUAL \n";
            parserInput += "= ";
        }
        else if(token=="<"){
            ofile << token << " , LESSTHAN \n";
            out += token + " , LESSTHAN \n";
            parserInput += "< ";
        }
    }
    else if (state == reserved)
    {
        if (token=="if"){
            ofile << token << " , IF \n";
            out += token + " , IF \n";
            parserInput += "if ";
        }
        else if(token=="then"){
            ofile << token << " , THEN \n";
            out += token + " , THEN \n";
            parserInput += "then ";
        }
        else if(token=="repeat"){
            ofile << token << " , REPEAT \n";
            out += token + " , REPEAT \n";
            parserInput += "repeat ";
        }
        else if(token=="until"){
            ofile << token << " , UNTIL \n";
            out += token + " , UNTIL \n";
            parserInput += "until ";
        }
        else if(token=="read"){
            ofile << token << " , READ \n";
            out += token + " , READ \n";
            parserInput += "read ";
        }
        else if(token=="write"){
            ofile << token << " , WRITE \n";
            out += token + " , WRITE \n";
            parserInput += "write ";
        }
        else if(token=="end"){
            ofile << token << " , END \n";
            out += token + " , END \n";
            parserInput += "end ";
        }
        else if(token=="else"){
            ofile << token << " , ELSE \n";
            out += token + " , ELSE \n";
            parserInput += "else ";
        }
//        else {
//            ofile << token << " , Reserved Word \n";
//        out += token + " , Reserved Word \n";
//        }
    }
    else if (state = error)
    {
        //ofile << "ERROR, unexpected output at :" << token;
        //out += "ERROR, unexpected output at :" + token;
    }
}
QString Scanner::printTokenList(string input)
{
    ofile.open("scanner_output.txt");
    out = "";
    char x;
    state = start;
    for (int i = 0; i < input.size(); i++)
    {
        x = input[i];
        if (x == ' ' && state != comment)
        {
            state = start;
        }
        else if (x == '{')
        {
            token = x;
            state = comment;
        }
        else if (state == start)
        {
            if (isDigit(x))
            {
                state = num;
                token = "";
                token.push_back(x);
                if (!isDigit(input[i + 1]))
                {
                    done();
                    state = start;
                }
            }
            else if (isSymbol(x))
            {
                token = x;
                state = special;
                done();
                state = start;
            }
            else if (x == ':')
            {

                if (input[i + 1] == '=')
                {
                    token = "";
                    token.push_back(x);
                    token.push_back(input[i + 1]);
                    state = special;
                    done();
                    input[i + 1] = ' ';
                    state = start;
                }
                else
                {
                    token = x;
                    state = error;
                    done();
                    state = start;
                }
            }
            else if (isLetter(x))
            {
                token = "";
                state = id;

                if (!isLetter(input[i + 1]))
                {
                    token.push_back(x);
                    state = id;
                    for (int j = 0; j < 8; j++)
                    {
                        if (RES_WORDS[j] == token)
                            state = reserved;
                    }
                    done();
                    state = start;
                }

                else
                {
                    token.push_back(x);
                    if (isalnum(input[i + 1]) || input[i + 1] == '_')
                    {
                        state = id;
                    }
                    else
                    {
                        state = id;
                        done();
                        state = start;
                    }
                }
            }

            else
            {
                token = x;
                state = error;
                done();
                state = start;
            }
        }
        else if (state == comment)
        {
            if (x == '}')
            {
                token += x;
                done();
                state = start;
            }
            else
            {
                token += x;
                state = comment;
            }
        }
        else if (state == num)
        {
            token.push_back(x);
            if (isDigit(input[i + 1]))
            {
                state = num;
            }
            else
            {
                done();
                state = start;
            }
        }
        else if (state == id)
        {
            token.push_back(x);
            if (isLetter(input[i + 1]))
            {
                state = id;
            }
            else
            {
                for (int j = 0; j < 8; j++)
                {
                    if (RES_WORDS[j] == token)
                        state = reserved;
                }
                done();
                state = start;
            }
        }
    }
    ofile.close();
    return QString::fromStdString(out);
}
QString Scanner::getStringFile(void)
{
    QString path=QFileDialog::getOpenFileName(NULL,QString("open file"),QString("/") ,QString("Text files (*.txt)"));
    if(path==""){
        QMessageBox::warning(NULL,"Error No File Selected ","Please select a valid path");
        return "";
    }

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return "";
    }

    QString input;
    QTextStream in(&file);
    QString line = in.readLine();

    while (!line.isNull()) {
        input += line+"\n" ;
        line = in.readLine();
    }
    return (input);
}

