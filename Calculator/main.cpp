#include <map>
#include <stack>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

enum Attribute { OPERATOR, OPERAND };

class Node
{
public:
    double value;
    Attribute attr;
    Node() {};
    Node(double v, Attribute a) : value(v), attr(a) {}
    bool operator<(const Node&);
};




class Calculator
{
public:
    Calculator() {};
    ~Calculator() {};

    bool isOperator(char);
    int buildSufix(string, stack<Node>&);
    double calcSufix(stack<Node>);
    void printStack(stack<Node>&);
    
};


int main(int, char**) 
{
    string exp;
    stack<Node> sufix;
    Calculator cal;

    while (true)
    {
        cout << "Please input expression:" << endl;
        cin >> exp;
        
        cout << "\n return " << cal.buildSufix(exp, sufix);
        cal.printStack(sufix);
        // cal.printStack(sufix);

    }

    return 0;
}

bool Calculator::isOperator(char a)
{
    return a == '(' || a == ')' || a == '+' || a == '-' || a == '*' || a == '/' || a == '^';
}

int Calculator::buildSufix(string exp, stack<Node>& sufix)
{
    char ch;
    double num;
    Node node;
    stack<Node> op;
    istringstream iss(exp);

    sufix.push(Node('#', OPERATOR));

    for (int i = 0; i < exp.size() ; i = iss.tellg())
    {
        if (i == EOF) return EOF;

        if (isOperator(exp[i]))  // if operator
        {
            iss >> ch;
            node = Node(ch, OPERATOR);

            if (ch == '(')
                op.push(node);
            else if (ch == ')')
            {
                while (!op.empty() && op.top().value != '(')
                {
                    sufix.push(op.top());
                    op.pop();
                }
                if (op.empty()) return EOF;
                else op.pop();
            }
            else 
            {
                while (!op.empty() && node < op.top())
                {
                    sufix.push(op.top());
                    op.pop();
                }
                op.push(node);
            }
        }
        else
        {
            iss >> num;
            sufix.push(Node(num, OPERAND));
        }
    }

    while (!op.empty() && op.top().value != '(')
    {
        sufix.push(op.top());
        op.pop();
    }

    if (!op.empty())
        return EOF;
    
    return 1;
}

void Calculator::printStack(stack<Node>& s)
{
    stack<Node> rs;

    while (!s.empty())
    {
        rs.push(s.top());
        s.pop();
    }

    cout << endl;
    while (!rs.empty())
    {
        Node n = rs.top();
        if (n.attr == OPERAND)
        {
            cout << ' ' << n.value << " ";
        }
        else
        {
            char c = n.value;
            cout << ' ' << c << " ";
        }
        rs.pop();
    }
    cout << endl;
}

bool Node::operator<(const Node& n)
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

    return PRIORITY[c1] < PRIORITY[c2];
}