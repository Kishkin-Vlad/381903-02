#include <stdlib.h>
#include <conio.h>    // for getch
#include <exception>  // for catch (logic_error)

#include "Formula.h"

using namespace std;


int main()
{
	Formula form;
	string str;

	while (true)
	{
		system("cls");
		cout << "# support for variables of the form <letters><number> (example: 'line1', 'vec21', 'dfgrkvgmfr2341234')" << endl
			<< "# support for multiplication <experession><number> or <expression><variable> etc (example: '23(1 + a)', '(12 + 4) (2 + 2)')" << endl
			<< "# support for many spaces (example: '   2  +    -12  ^2   ')" << endl
			<< "# support for unary minus (example: '2 + -1', '2 - ---1')" << endl
			<< "# operators: +, -, *, /, ^" << endl;
		cout << "Enter 'exit' for finish";
		try
		{
			cout << "Enter string: ";
			getline(cin, str);
			if (str == "exit")
				break;

			form.init(str);
			form.conversToRevPolNot();
			double res = form.calculateExpression();

			cout << "Your answer: " << res << endl;
			getch();
			continue;
		}
		catch (exception& e)
		{
			system("cls");
			cout << "Type error: " << typeid(e).name() << endl;
			cout << "Error: " << e.what() << endl << endl;
			cout << endl << "Your string: " << form.getInputFormula() << endl << endl;

			cout << "Try again (press enter)";
			
			getch();
		}
	}

	system("cls");

	return 0;
}