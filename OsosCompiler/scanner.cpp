#include <scanner.h>


string token;
stateType state = idle;
string out = "";
ofstream ofile;
string RES_WORDS[8] = { "if","then","else","end","repeat","until","read","write" };

bool Scanner::isDigit(char d) { return (d >= '0' && d <= '9'); }
bool Scanner::isLetter(char l) { return (l >= 'a' && l <= 'z' || l >= 'A' && l <= 'Z'); }
bool Scanner::isSpace(char s) { return (s == ' ' || s == '\t' || s == '\n'); }
bool Scanner::isSymbol(char c) { return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '(' || c == ')' || c == ';'); }
Scanner::Scanner()
{

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
    }
    else if (state == id)
    {
        ofile << token << " , IDENTIFIER \n";
        out += token + " , IDENTIFIER \n";
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
        }
        else if(token=="-"){
            ofile << token << " , MINUS \n";
            out += token + " , MINUS \n";
        }
        else if(token=="+"){
            ofile << token << " , PLUS \n";
            out += token + " , PLUS \n";
        }
        else if(token==";"){
            ofile << token << " , SEMI \n";
            out += token + " , SEMI \n";
        }
        else if(token=="("){
            ofile << token << " , LEFTBRACKET \n";
            out += token + " , LEFTBRACKET \n";
        }
        else if(token==")"){
            ofile << token << " , RIGHTBRACKET \n";
            out += token + " , RIGHTBRACKET \n";
        }
        else if(token=="*"){
            ofile << token << " , MULTIPLY \n";
            out += token + " , MULTIPLY \n";
        }
        else if(token=="/"){
            ofile << token << " , DIVID \n";
            out += token + " , DIVID \n";
        }
        else if(token=="="){
            ofile << token << " , EQUAL \n";
            out += token + " , EQUAL \n";
        }
        else if(token=="<"){
            ofile << token << " , SMALLER \n";
            out += token + " , SMALLER \n";
        }
    }
    else if (state == reserved)
    {
        if (token=="if"){
            ofile << token << " , IF \n";
            out += token + " , IF \n";
        }
        else if(token=="then"){
            ofile << token << " , THEN \n";
            out += token + " , THEN \n";
        }
        else if(token=="repeat"){
            ofile << token << " , REPEAT \n";
            out += token + " , REPEAT \n";
        }
        else if(token=="until"){
            ofile << token << " , UNTIL \n";
            out += token + " , UNTIL \n";
        }
        else if(token=="read"){
            ofile << token << " , READ \n";
            out += token + " , READ \n";
        }
        else if(token=="write"){
            ofile << token << " , WRITE \n";
            out += token + " , WRITE \n";
        }
        else if(token=="end"){
            ofile << token << " , END \n";
            out += token + " , END \n";
        }
        else if(token=="else"){
            ofile << token << " , ELSE \n";
            out += token + " , ELSE \n";
        }
        else {
            ofile << token << " , Reserved Word \n";
        out += token + " , Reserved Word \n";
        }
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

