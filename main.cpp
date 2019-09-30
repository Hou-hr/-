//
//  main.cpp
//  C++ Test
//
//  Created by apple on 2019/4/18.
//  Copyright © 2019年 Tentcoo. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

vector<string> words;

void getsym(string line, int index);
int identifier(string line, int index);
int number(string line, int index, bool isLose);
void insertReservedWords();
bool isReservedWords(string word);

int main(int argc, const char * argv[]) {
    
    insertReservedWords();
    
    ifstream file("/Users/apple/Desktop/C++ Test/content.txt");
    string line;
    
    while (getline(file, line)) {
        getsym(line, 0);
        cout<<endl;
    }
    
    return 0;
}

void getsym(string line, int index) {
    long len = line.size();
    while (index < len)
    {
        if ((line[index] == ' ' || line[index] == 10 || line[index] == 13 || line[index] == 9))
        {
            index++;
        }
        else
        {
            break;
        }
    }
    if (index >= len)
    {
        return;
    }
    else
    {
        if ((line[index] >= 'a' && line[index] <= 'z') || (line[index] >= 'A' && line[index] <= 'Z') || line[index] == '_')
        {
            index = identifier(line, index);
        }
        else
        {
            if (line[index] >= '0' && line[index] <= '9')
            {
                index = number(line, index, false);
            }
            else
            {
                if (line[index] == '=')
                {
                    index++;
                    if (index < len && line[index] == '=')
                    {
                        index++;
                        cout<<"<"<<line.substr(index-2, index)<<",判断符号> ";
                    }
                    else
                    {
                        cout<<"<"<<line[index-1]<<",赋值符号> ";
                    }
                }
                else
                {
                    if (line[index] == '+')
                    {
                        index++;
                        if (index < len && line[index] >= '0' && line[index] <= '9')
                        {
                            index = number(line, index, false);
                        }
                        else
                        {
                            cout<<"<"<<line[index-1]<<",加符号> ";
                        }
                    }
                    else
                    {
                        if (line[index] == '-')
                        {
                            index++;
                            if (index < len && line[index] >= '0' && line[index] <= '9')
                            {
                                index = number(line, index, true);
                            }
                            else
                            {
                                cout<<"<"<<line[index-1]<<",减符号> ";
                            }
                        }
                        else
                        {
                            if (line[index] == '>')
                            {
                                index++;
                                if (index < len && line[index] == '=')
                                {
                                    index++;
                                    cout<<"<"<<line.substr(index-2, index)<<",大于等于符号> ";
                                }
                                else
                                {
                                    cout<<"<"<<line[index-1]<<",大于符号> ";
                                }
                            }
                            else
                            {
                                if (line[index] == '<')
                                {
                                    index++;
                                    if (index < len && line[index] == '=')
                                    {
                                        index++;
                                        cout<<"<"<<line.substr(index-2, index)<<",小于等于符号> ";
                                    }
                                    else
                                    {
                                        cout<<"<"<<line[index-1]<<",小于符号> ";
                                    }
                                }
                                else
                                {
                                    if (line[index] == '(')
                                    {
                                        index++;
                                        cout<<" <"<<line[index-1]<<",左括号符号> ";
                                    }
                                    else
                                    {
                                        if (line[index] == ')')
                                        {
                                            index++;
                                            cout<<"<"<<line[index-1]<<",右括号符号> ";
                                        }
                                        else
                                        {
                                            if (line[index] == '{')
                                            {
                                                index++;
                                                cout<<"<"<<line[index-1]<<",左大括号符号> ";
                                            }
                                            else
                                            {
                                                if (line[index] == '}')
                                                {
                                                    index++;
                                                    cout<<"<"<<line[index-1]<<",右大括号符号> ";
                                                }
                                                else
                                                {
                                                    if (line[index] == ';') {
                                                        index++;
                                                        cout<<"<"<<line[index-1]<<",分号符号> ";
                                                    }
                                                    else
                                                    {
                                                        if (line[index] == '"') {
                                                            index++;
                                                            cout<<"<"<<line[index-1]<<",冒号符号> ";
                                                        }
                                                        else
                                                        {
                                                            if (line[index] == ',') {
                                                                index++;
                                                                cout<<"<"<<line[index-1]<<",逗号符号> ";
                                                            }
                                                            else
                                                            {
                                                                if (line[index] == 47) // '/'
                                                                {
                                                                    index++;
                                                                    cout<<"<"<<line[index-1]<<",斜杠或除号符号> ";
                                                                }
                                                                else
                                                                {
                                                                    if (line[index] == 92) // '\'
                                                                    {
                                                                        index++;
                                                                        cout<<"<"<<line[index-1]<<",反斜杠符号> ";
                                                                    }
                                                                    else
                                                                    {
                                                                        if (line[index] == '*')
                                                                        {
                                                                            index++;
                                                                            cout<<"<"<<line[index-1]<<",乘/星号符号> ";
                                                                        }
                                                                        else
                                                                        {
                                                                            if (line[index] == '#')
                                                                            {
                                                                                index++;
                                                                                cout<<"<"<<line[index-1]<<",头文件声明符号> ";
                                                                            }
                                                                            else
                                                                            {
                                                                                if (line[index] == '%')
                                                                                {
                                                                                    index++;
                                                                                    cout<<" <"<<line[index-1]<<",求余符号> ";
                                                                                }
                                                                                else
                                                                                {
                                                                                    if (line[index] == '.')
                                                                                    {
                                                                                        index++;
                                                                                        cout<<" <"<<line[index-1]<<",点符号> ";
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        if (line[index] == '[')
                                                                                        {
                                                                                            index++;
                                                                                            cout<<" <"<<line[index-1]<<",左中括号符号> ";
                                                                                        }
                                                                                        else
                                                                                        {
                                                                                            if (line[index] == ']')
                                                                                            {
                                                                                                index++;
                                                                                                cout<<" <"<<line[index-1]<<",右中括号符号> ";
                                                                                            }
                                                                                            else
                                                                                            {
                                                                                                index++;
                                                                                                cout<<endl<<"ERROR: 无法识别的标识符 "<<line[index-1]<<endl;
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (index < len)
    {
        getsym(line, index);
    }
    
}

int identifier(string line, int index) {
    int place = index;
    while ((line[place] >= 'a' && line[place] <= 'z') || (line[place] >= 'A' && line[place] <= 'Z') || (line[place] >= '0' && line[place] <= '9') || line[place] == '_') {
        place++;
        if (place >= line.size()) {
            break;
        }
    }
    string word = line.substr(index, place-index);
    if (isReservedWords(word)) {
        cout<<"<"<<word<<",保留字> ";
    } else {
        cout<<"<"<<word<<",标识符> ";
    }
    
    return place;
}

int number(string line, int index, bool isLose) {
    int place = index;
    bool flag = 0;
    while (line[place] >= '0' && line[place] <= '9') {
        place++;
    }
    if (line[place] == '.') {
        flag = 1;
        place++;
        while (line[place] >= '0' && line[place] <= '9') {
            place++;
        }
    }
    string s = "<";
    if (isLose) {
        s = "<-";
    }
    if (flag) {
        cout<<s<<line.substr(index, place-index)<<",浮点数> ";
    } else {
        cout<<s<<line.substr(index, place-index)<<",整数> ";
    }
    return place;
}

void insertReservedWords() {
    words.push_back("while");
    words.push_back("for");
    words.push_back("if");
    words.push_back("else");
    words.push_back("int");
    words.push_back("float");
    words.push_back("double");
    words.push_back("string");
    words.push_back("char");
    words.push_back("void");
    words.push_back("bool");
    words.push_back("print");
    words.push_back("long");
    words.push_back("break");
    words.push_back("define");
}

bool isReservedWords(string word) {
    for (int i = 0; i < words.size(); i++) {
        if (words[i] == word) {
            return true;
        }
    }
    return false;
}
