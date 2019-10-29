#include <map>
#include <stack>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>

using namespace std;

enum Attribute { OPERATOR, OPERAND };



class divideZeroErr:public exception
{
public:
   const char* what()const throw()//#1 
   {
        return "ERROR! Don't divide a number by zero.\n";
   }    
};

class bracketsErr:public exception
{
public:
   const char* what()const throw()//#1 
   {
        return "ERROR! Brackets do not match.\n";
   }    
};

class operatorErr:public exception
{
public:
   const char* what()const throw()//#1 
   {
        return "ERROR! Invalid operands or operator.\n";
   }    
};


class Node
{
public:
    double value;
    Attribute attr;
    Node() {};
    Node(double v, Attribute a) : value(v), attr(a) {}
    bool operator<=(const Node&);
};


class Calculator
{
public:
    Calculator() {};
    ~Calculator() {};

    bool isOperator(char);
    void buildSufix(string, stack<Node>&);
    void printStack(stack<Node>);
    double calcSufix(stack<Node>);
    void calc2nums(stack<double>&, char);
    
};


int main(int, char**) 
{
    string exp;
    stack<Node> sufix;
    Calculator cal;

    while (true)
    {
        cout << "\nPlease input expression:" << endl;
        cin >> exp;

        try
        {
            cal.buildSufix(exp, sufix);  // build sufix polish
            // cal.printStack(sufix);
            double res = cal.calcSufix(sufix);
            cout << "= " << res << endl;
        }
        catch(const exception& e)
        {
            cerr << e.what() << '\n';
        }

        while (!sufix.empty()) sufix.pop();
    }

    return 1;
}

bool Calculator::isOperator(char a)
{
    return a == '(' || a == ')' || a == '+' || a == '-' || a == '*' || a == '/' || a == '^';
}

void Calculator::buildSufix(string exp, stack<Node>& sufix)
{
    char ch;
    double num;
    Node node;
    stack<Node> s;  // operator stack
    stack<Node> polish;
    istringstream iss(exp);

    polish.push(Node('#', OPERATOR));

    for (int i = 0; i < iss.str().size() ; i = iss.tellg())
    {
        if (i == EOF) throw operatorErr();

        if (isOperator(iss.str()[i]))  // if operator
        {
            iss >> ch;
            node = Node(ch, OPERATOR);

            if (ch == '(')  s.push(node);
            else if (ch == ')')     
            {
                while (!s.empty() && s.top().value != '(')
                {
                    polish.push(s.top());
                    s.pop();
                }
                if (s.empty()) throw bracketsErr();
                else s.pop();
            }
            else 
            {
                while (!s.empty() && node <= s.top())
                {
                    polish.push(s.top());
                    s.pop();
                }
                s.push(node);
            }
        }
        else  // operand
        {
            iss >> num;
            polish.push(Node(num, OPERAND));
        }
    }

    while (!s.empty() && s.top().value != '(')
    {
        polish.push(s.top());
        s.pop();
    }

    if (!s.empty()) throw bracketsErr();
    else  // reverse polisih
    {
        while(polish.top().value != '#')
        {
            sufix.push(polish.top());
            polish.pop();
        }
    }
}

void Calculator::printStack(stack<Node> s)
{
    cout << endl;
    while (!s.empty())
    {
        Node n = s.top();
        if (n.attr == OPERAND)
        {
            cout << ' ' << n.value << " ";
        }
        else
        {
            char c = n.value;
            cout << ' ' << c << " ";
        }
        s.pop();
    }
    cout << endl;
}

double Calculator::calcSufix(stack<Node> sufix)
{
    stack<double> num;
    while (!sufix.empty()) 
    {
        if (sufix.top().attr == OPERAND)
        {
            num.push(sufix.top().value);
            sufix.pop();
        }
        else
        {
            calc2nums(num, char(sufix.top().value));
            sufix.pop();
        }
    }
    if (!num.empty())
    {
        double res = num.top();
        num.pop();
        if (num.empty()) return res;
        else throw operatorErr();
    }
    else throw operatorErr();
}

void Calculator::calc2nums(stack<double>& num, char c)
{
    double n;

    if (num.empty()) throw operatorErr();
    else
    {
        n = num.top();
        num.pop();
    }
    if (num.empty()) throw operatorErr();
    else
    {
        switch (c)
        {
        case '+':
            num.top() += n;
            break;
        case '-':
            num.top() -= n;
            break;
        case '*':
            num.top() *= n;
            break;
        case '/':
            if (n == 0) throw divideZeroErr();
            else num.top() /= n;
            break;
        case '^':
            num.top() = pow(num.top(), n);
            break;
        default:
            return throw operatorErr();
        }
    }

}

bool Node::operator<=(const Node& n)
{
    map<char, short> PRIORITY;
    PRIORITY['('] = 0;
    PRIORITY[')'] = 0;
    PRIORITY['+'] = 1;
    PRIORITY['-'] = 1;
    PRIORITY['*'] = 2;
    PRIORITY['/'] = 2;
    PRIORITY['^'] = 3;

    char c1 = this->value;
    char c2 = n.value;

    return PRIORITY[c1] <= PRIORITY[c2];
}