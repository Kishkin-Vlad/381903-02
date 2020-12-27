#include "Formula.h"


Formula::Formula() :
	inputFormula(), outputFormula()
{
	listRPN = new List<Lexem*>;
	vars = new map<string, double>;
}

Formula::Formula(const string& str) :
	inputFormula(str), outputFormula()
{
	listRPN = new List<Lexem*>;
	vars = new map<string, double>;
}

Formula::Formula(const char* str) :
	inputFormula(str), outputFormula()
{
	listRPN = new List<Lexem*>;
	vars = new map<string, double>;
}

Formula::~Formula()
{
	delete listRPN;
	delete vars;
}

void Formula::init(const string& str)
{
	if (str.length() == 0)
		throw logic_error("Formula: string lenght is zero");

	inputFormula = str;
	outputFormula = "";
	if (!listRPN->isEmpty())
		listRPN->clear();
	vars->clear();
}

void Formula::LexicalAnalysis(ICollection<Lexem*>* list)
{
	// del all " "
	string new_formula("");
	for (int i = 0; i < inputFormula.length(); i++)
	{
		char temp = inputFormula[i];
		if (temp != ' ')
			new_formula += temp;
	}
	inputFormula = new_formula;
	inputFormula += " ";

	string lex = "Begin";
	State state = q0;
	int count_brackets = 0;
	char ch;
	int len = inputFormula.length();

	char temp_n = 'n';
	for (int i = 0; i < len; i++)
	{
		ch = inputFormula[i];
		switch (state)
		{
		case q0:
			lex = ch;

			if (ch >= '0' && ch <= '9')
				state = q1;
			else if (ch >= 'a' && ch <= 'z')
				state = q2;
			else if (ch == '-')
			{
				state = q3;
				list->add(new Lexem(lex, UNARY_OPERATOR));
			}
			else if (ch == '(' || ch == '[' || ch == '{')
			{
				count_brackets++;
				list->add(new Lexem(lex, L_BRACKET));
			}
			else if (ch == ')' || ch == ']' || ch == '}')
			{
				state = q2;

				count_brackets--;
				if (count_brackets < 0)
					throw logic_error("Formula: count left and right brackets not the same");

				// comprassion left and right brackets
				/*int index1 = list->rfind(new Lexem("(", L_BRACKET));
				int index2 = list->rfind(new Lexem("[", L_BRACKET));
				int index3 = list->rfind(new Lexem("{", L_BRACKET));
				if (!(ch == ')' && index1 > index2 && index1 > index3))
					throw logic_error("Formula: different brackets");
				else if (!(ch == ']' && index2 > index1 && index2 > index3))
					throw logic_error("Formula: different brackets");
				else if (!(ch == '}' && index3 > index1 && index3 > index2))
					throw logic_error("Formula: different brackets");*/

				list->add(new Lexem(lex, R_BRACKET));
			}
			else if (ch == ' ') {}
			else if (ch == '+' || ch == '^' || ch == '*' || ch == '/')
				throw logic_error("Formula: expression is invalid - binary operation is in the wrong place");
			else
			{
				cout << '1';
				throw logic_error("Formula: expression is invalid - incorrect character");
			}

			break;
		case q1:
			if (ch >= '0' && ch <= '9')
				lex += ch;
			else
			{
				double temp = atoi(lex.c_str());
				list->add(new Lexem(lex, VALUE, temp));
				state = q3;

				lex = ch;
				if (ch == '+' || ch == '-')
					list->add(new Lexem(lex, BIN_OPERATOR, -1, 1));
				else if (ch == '*' || ch == '/')
					list->add(new Lexem(lex, BIN_OPERATOR, -1, 2));
				else if (ch == '^')
					list->add(new Lexem(lex, BIN_OPERATOR, -1, 3));
				else if (ch >= 'a' && ch <= 'z')
				{
					state = q2;
					list->add(new Lexem("*", BIN_OPERATOR, -1, 2));
				}
				else if (ch == '(' || ch == '[' || ch == '{')
				{
					state = q0;
					count_brackets++;
					list->add(new Lexem(lex, L_BRACKET));
				}
				else if (ch == ')' || ch == ']' || ch == '}')
				{
					state = q2;

					count_brackets--;
					if (count_brackets < 0)
						throw logic_error("Formula: count left and right brackets not the same");

					// comprassion left and right brackets
					/*Lexem* temp = new Lexem("(", L_BRACKET);
					int index1 = list->rfind(temp);
					int n = 1;*/
					/*temp("[", L_BRACKET);
					int index2 = list->rfind(temp);
					
					temp = new Lexem("{", L_BRACKET);
					int index3 = list->rfind(temp);*/

					/*if (ch == ')' && !(index1 > index2 && index1 > index3))
						throw logic_error("Formula: different brackets");
					else if (ch == ']' && !(index2 > index1 && index2 > index3))
						throw logic_error("Formula: different brackets");
					else if (ch == '}' && !(index3 > index1 && index3 > index2))
						throw logic_error("Formula: different brackets");*/

					list->add(new Lexem(lex, R_BRACKET));
				}
				else if (ch == ' ') {}
				else
				{
					cout << '2';
					throw logic_error("Formula: expression is invalid - incorrect character");
				}
			}

			break;
		case q2:
			if (!list->isEmpty() && list->getLast()->getTypeElem() == R_BRACKET) // if last lexem == right bracket
			{
				lex = ch;

				if (ch >= '0' && ch <= '9')
				{
					state = q1;
					list->add(new Lexem("*", BIN_OPERATOR, -1, 2));
				}
				else if (ch >= 'a' && ch <= 'z')
					list->add(new Lexem("*", BIN_OPERATOR, -1, 2));
				else if (ch == '+' || ch == '-')
				{
					state = q3;
					list->add(new Lexem(lex, BIN_OPERATOR, -1, 1));
				}
				else if (ch == '*' || ch == '/')
				{
					state = q3;
					list->add(new Lexem(lex, BIN_OPERATOR, -1, 2));
				}
				else if (ch == '^')
				{
					state = q3;
					list->add(new Lexem(lex, BIN_OPERATOR, -1, 3));
				}
				else if (ch == '(' || ch == '[' || ch == '{')
				{
					state = q0;
					count_brackets++;
					list->add(new Lexem("*", BIN_OPERATOR, -1, 2));
					list->add(new Lexem(lex, L_BRACKET));
				}
				else if (ch == ')' || ch == ']' || ch == '}')
				{
					state = q2;

					count_brackets--;
					if (count_brackets < 0)
						throw logic_error("Formula: count left and right brackets not the same");

					// comprassion left and right brackets
					/*int index1 = list->rfind(new Lexem("(", L_BRACKET));
					int index2 = list->rfind(new Lexem("[", L_BRACKET));
					int index3 = list->rfind(new Lexem("{", L_BRACKET));
					if (!(ch == ')' && index1 > index2 && index1 > index3))
						throw logic_error("Formula: different brackets");
					else if (!(ch == ']' && index2 > index1 && index2 > index3))
						throw logic_error("Formula: different brackets");
					else if (!(ch == '}' && index3 > index1 && index3 > index2))
						throw logic_error("Formula: different brackets");*/

					list->add(new Lexem(lex, R_BRACKET));
				}
				else if (ch == ' ') {}
				else
				{
					cout << '3';
					throw logic_error("Formula: expression is invalid - incorrect character");
				}
			}
			else  // if value or variable
			{
				if (ch >= '0' && ch <= '9')
				{
					temp_n = ch;
					lex += ch;
				}
				else if (ch >= 'a' && ch <= 'z')
				{
					if (temp_n >= '0' && temp_n <= '9')
						throw logic_error("Formula: how should it look var: <letters><number> (the number can be omitted)");
					lex += ch;
				}
				else if (ch == '+' || ch == '-')
				{
					state = q3;

					(*vars)[lex] = 0;
					list->add(new Lexem(lex, VAR));

					lex = ch;
					list->add(new Lexem(lex, BIN_OPERATOR, -1, 1));
				}
				else if (ch == '*' || ch == '/')
				{
					state = q3;

					(*vars)[lex] = 0;
					list->add(new Lexem(lex, VAR));

					lex = ch;
					list->add(new Lexem(lex, BIN_OPERATOR, -1, 2));
				}
				else if (ch == '^')
				{
					state = q3;

					(*vars)[lex] = 0;
					list->add(new Lexem(lex, VAR));

					lex = ch;

					list->add(new Lexem(lex, BIN_OPERATOR, -1, 3));
				}
				else if (ch == '(' || ch == '[' || ch == '{')
				{
					state = q0;
					count_brackets++;

					(*vars)[lex] = 0;
					list->add(new Lexem(lex, VAR));

					lex = ch;
					list->add(new Lexem(lex, L_BRACKET));
				}
				else if (ch == ')' || ch == ']' || ch == '}')
				{
					state = q2;

					count_brackets--;
					if (count_brackets < 0)
						throw logic_error("Formula: count left and right brackets not the same");

					// comprassion left and right brackets
					/*int index1 = list->rfind(new Lexem("(", L_BRACKET));
					int index2 = list->rfind(new Lexem("[", L_BRACKET));
					int index3 = list->rfind(new Lexem("{", L_BRACKET));
					if (!(ch == ')' && index1 > index2 && index1 > index3))
						throw logic_error("Formula: different brackets");
					else if (!(ch == ']' && index2 > index1 && index2 > index3))
						throw logic_error("Formula: different brackets");
					else if (!(ch == '}' && index3 > index1 && index3 > index2))
						throw logic_error("Formula: different brackets");*/

					(*vars)[lex] = 0;
					list->add(new Lexem(lex, VAR));

					lex = ch;
					list->add(new Lexem(lex, R_BRACKET));
				}
				else if (ch == ' ')
				{
					state = q3;
					(*vars)[lex] = 0;
					list->add(new Lexem(lex, VAR));
				}
				else
				{
					cout << '4';
					throw logic_error("Formula: expression is invalid - incorrect character");
				}
				}

			break;
		case q3:
			lex = ch;

			if (ch >= '0' && ch <= '9')
				state = q1;
			else if (ch >= 'a' && ch <= 'z')
				state = q2;
			else if (ch == '-')
				list->add(new Lexem(lex, UNARY_OPERATOR));
			else if (ch == '(' || ch == '[' || ch == '{')
			{
				count_brackets++;
				list->add(new Lexem(lex, L_BRACKET));
			}
			else if (ch == ')' || ch == ']' || ch == '}')
			{
				state = q2;

				count_brackets--;
				if (count_brackets < 0)
					throw logic_error("Formula: count left and right brackets not the same");

				// comprassion left and right brackets
				/*int index1 = list->rfind(new Lexem("(", L_BRACKET));
				int index2 = list->rfind(new Lexem("[", L_BRACKET));
				int index3 = list->rfind(new Lexem("{", L_BRACKET));
				if (!(ch == ')' && index1 > index2 && index1 > index3))
					throw logic_error("Formula: different brackets");
				else if (!(ch == ']' && index2 > index1 && index2 > index3))
					throw logic_error("Formula: different brackets");
				else if (!(ch == '}' && index3 > index1 && index3 > index2))
					throw logic_error("Formula: different brackets");*/

				list->add(new Lexem(lex, R_BRACKET));
			}
			else if (ch == ' ') {}
			else if (ch == '+' || ch == '^' || ch == '*' || ch == '/')
				throw logic_error("Formula: expression is invalid - binary operation is in the wrong place");
			else
			{
				cout << '5';
				throw logic_error("Formula: expression is invalid - incorrect character");
			}

			break;
		}
	}
}

void Formula::SyntacticAnalysis(ICollection<Lexem*>& in, ICollection<Lexem*>* out)
{
	ICollection<Lexem*>* st = new Stack<Lexem*>(MAX_SIZE);

	for (int i = 0; i < in.getSize(); i++)
	{
		TypeElem te = in[i]->getTypeElem();

		if (te == VALUE || te == VAR)
			out->add(in[i]);
		else if (te == BIN_OPERATOR)
		{
			int pr = in[i]->getPrior();
			if (st->isEmpty())
				st->add(in[i]);
			else
			{
				int pr_top = st->getLast()->getPrior();
				if (pr > pr_top)
					st->add(in[i]);
				else
				{
					for (int j = 0; j < st->getSize(); j++)
						out->add(st->pop());
					st->add(in[i]);
				}
			}
			
		}
		else if (te == L_BRACKET)
			st->add(in[i]);
		else if (te == R_BRACKET)
		{
			TypeElem temp = st->getLast()->getTypeElem();
			while (temp != L_BRACKET)
			{
				out->add(st->pop());
				temp = st->getLast()->getTypeElem();
			}
			st->pop();
		}
		else if (te == UNARY_OPERATOR)
			st->add(in[i]);
	}
	while (st->getSize() > 0)
		out->add(st->pop());
}

bool Formula::addVar()
{
	if (!(anyVar()))
		return true;

	cout << "Enter variable (type double):" << endl;
	for (auto& var : *vars)
	{
		cout << var.first << " = ";
		cin >> var.second;
	}
	return true;
}

void Formula::conversToRevPolNot()
{
	if (inputFormula.length() == 0)
		throw logic_error("Formula: expression is not initialized");

	inputFormula += " ";
	ICollection<Lexem*>* li = new List<Lexem*>;  // list input
	LexicalAnalysis(li);
	
	cout << "After lexical analysis:" << endl;
	li->print();
	cout << endl << endl;

	ICollection<Lexem*>* lo = new List<Lexem*>;  // list output
	SyntacticAnalysis(*li, lo);

	cout << "After syntactic analysis:" << endl;
	lo->print();
	cout << endl << endl;

	listRPN = lo;

	// lo << putputFormula
	for (int i = 0; i < listRPN->getSize(); i++)
	{
		outputFormula += listRPN->operator[](i)->getStr();
	}

	cout << "OutputFormula:" << endl;
	cout << outputFormula << endl << endl;

	addVar();
	readyOutFor = true;
}

double Formula::calculateExpression()
{
	if (readyOutFor == false)
		throw logic_error("Formula: output formula is not ready");

	ICollection<Lexem*>* st = new Stack<Lexem*>(MAX_SIZE);

	for (int i = 0; i < listRPN->getSize(); i++)
	{
		Lexem* element_now = listRPN->operator[](i);
		TypeElem temp = listRPN->operator[](i)->getTypeElem();
		if (temp == BIN_OPERATOR)
		{
			Lexem* elem2 = st->pop();
			Lexem* elem1 = st->pop();
			double val;

			if (element_now->getStr() == "+")
			{
				val = elem1->getValue() + elem2->getValue();
				st->add(new Lexem(to_string(val), VALUE, val));
			}
			else if (element_now->getStr() == "-")
			{
				val = elem1->getValue() - elem2->getValue();
				st->add(new Lexem(to_string(val), VALUE, val));
			}
			else if (element_now->getStr() == "*")
			{
				val = elem1->getValue() * elem2->getValue();
				st->add(new Lexem(to_string(val), VALUE, val));
			}
			else if (element_now->getStr() == "/")
			{
				if (elem2->getValue() == (double)0)
					throw logic_error("Formula: in calculations, it turns out to be 0");
				val = elem1->getValue() / elem2->getValue();
				st->add(new Lexem(to_string(val), VALUE, val));
			}
			else if (element_now->getStr() == "^")
			{
				val = pow(elem1->getValue(), elem2->getValue());
				st->add(new Lexem(to_string(val), VALUE, val));
			}
		}
		else if (temp == UNARY_OPERATOR)
		{
			Lexem* elem1 = st->pop();
			double val = -(elem1->getValue());

			st->add(new Lexem(to_string(val), VALUE, val));
		}
		else if (temp == VALUE)
			st->add(element_now);
		else if (temp == VAR)
			st->add(new Lexem(element_now->getStr(), VALUE, (*vars)[element_now->getStr()]));
	}
	cout << endl << "Remaining number in stack:" << endl;
	st->print();
	cout << endl;

	return st->pop()->getValue();
}
