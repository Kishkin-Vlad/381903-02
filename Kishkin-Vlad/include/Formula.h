#include<string>
#include<map>

#include "Collection.h"

#define MAX_SIZE 1000

using namespace std;


enum TypeElem 
{
	VALUE,           // number
	VAR,             // variable
	BIN_OPERATOR,    // binary operator
	UNARY_OPERATOR,  // unary operator
	L_BRACKET,       // left bracket
	R_BRACKET        // right bracket
};

enum State
{
	q0,  // unknow or operator-(unary)
	q1,  // number
	q2,  // variable or right bracket
	q3   // operators+, -, *, /, ^
};


class Lexem
{
private:
	string str;
	TypeElem te;
	int value;
	int prior;

public:
	Lexem(const string& _str, const TypeElem _te, int _value = -1, int _prior = -1) :
		str(_str), te(_te), value(_value), prior(_prior) {};
	Lexem(const Lexem& lex)
	{
		str = lex.str;
		te = lex.te;
		value = lex.value;
		prior = lex.prior;
	}
	string getStr() { return str; };
	TypeElem getTypeElem() { return te; };
	int getValue() { return value; };
	int getPrior() { return prior; };

	bool operator==(const Lexem& lex)
	{
		return (str == lex.str && te == lex.te && value == lex.value && prior == lex.prior);
	}

	bool operator==(Lexem* lex)
	{
		return (str == lex->str && te == lex->te && value == lex->value && prior == lex->prior);
	}

	friend ostream& operator<<(ostream& out, const Lexem& lex)
	{
		out << lex.str;

		return out;
	}
	friend ostream& operator<<(ostream& out, Lexem* lex)
	{
		out << lex->str;

		return out;
	}
};


class Formula
{
private:
	string inputFormula;
	string outputFormula;
	map<string, double>* vars;
	bool readyOutFor = false;

	ICollection<Lexem*>* listRPN;                                               // list ready for reverse polish notation

	void LexicalAnalysis(ICollection<Lexem*>* list);                            // string to lexem
	void SyntacticAnalysis(ICollection<Lexem*>& in, ICollection<Lexem*>* out);  // revers polish natation
public:
	Formula();
	Formula(const string& str);
	Formula(const char* str);
	~Formula();

	void init(const string& str);

	const string getInputFormula() { return inputFormula; };
	const string getOutputFormula() { return outputFormula; }; 

	bool anyVar() { return !vars->empty(); };                  // are there any values
	bool addVar();

	void conversToRevPolNot();                                 // convers to reverse polish notation
	double calculateExpression();                              // calculate our expression
};