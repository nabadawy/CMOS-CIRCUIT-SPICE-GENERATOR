// C++ program to generate CMOS circuit simulation 
#include <iostream>
#include <string>
#include <vector>
#include <stack>


using namespace std;
void  CMOS_Circuit_SPICE_Generator(vector <string> str);
void NOT(string input, string & out_put);
void AND(string in_1, string in_2, string & out_put);
void OR(string in_1, string in_2, string & out_put);
void OR_2(string in_1, string in_2, string & out_put);
void AND_2(string in_1, string in_2, string & out_put);
void handle_bracket(string n);
bool validity(string v);

int main()
{
	vector <string > exp;    //vector to copy the string in it 
	vector <int> count;      // to put the index of ; in it "for the multiple expressions"
	string str;
	string substring;
	int ans;
	
	cout << " -----------------------------------\n ";
	cout << "please choose the mode of operation: \n";
	cout << " (1) one expression \n" << " (2) multiple expressions \n";
	cout << "---------------------------------------\n";
	cin >> ans;

	switch (ans)
	{
	case 1:   // only one expression 
		cout << " please enter one expression without any spaces: \n";
		cin >> str;
		if (!validity(str))
		{
			cout << "Invalid format\n";
			system("pause");
			return 0;
		}
		else 
		
		for (int i = 0; i < str.size(); i++)
		{
			if (str.at(i) == '(')    
			{
				handle_bracket(str);     // function to solve expressions with brackets 
				system("pause");
				return 0; 
			}
			
			else {
				char k = str.at(i);   // copping the elements of the string into the vector with string type 
				string s(1, k);
				exp.push_back(s);
			}

		}
		CMOS_Circuit_SPICE_Generator(exp);    // the function that display the data section of the COMS Circuit 

		break;
	case 2:   // case 2 which deals with multiple expressions 
		cout << " please enter the expressions you want  \n one expression then followed by ; and then the second one \n Note: no ; at the last one and no spaces at all \n";
		
	
		cin >> str;
		cout << str<< endl; 
		if (!validity(str))
		{
			cout << "Invalid format\n";
			system("pause");
			return 0;
		}
		
		// traverse the string and make substrings to be able to evaluate each one alone
		for (int i = 0; i < str.size(); i++)
		{
			if (str.at(i) == ';')
				count.push_back(i); // putting the index of the ; in a victor 
		
		}
		
		
		substring = str.substr(0, count[0]);
		

		for (int j = 0; j < substring.size(); j++)   // each substring is coppied to a vector of type string 
		{
			char k = substring.at(j);
			string s(1, k);
			exp.push_back(s);
		}
		
		CMOS_Circuit_SPICE_Generator(exp);   // to generate the data section 
		exp.clear();
		cout << "---------------------------------------------\n";
		 
		if (count.size() > 1) {
			
			for (int i = 1; i < count.size(); i++)   // cutting to substrings 
			{
				
				substring = str.substr(count[i - 1], count[i]- count[i-1]);
				for (int j = 1; j < substring.size(); j++)
				{
					char k = substring.at(j);
					string s(1, k);
					exp.push_back(s);
				}
				CMOS_Circuit_SPICE_Generator(exp);
				exp.clear();
				cout << "----------------------------------------------\n";
			}
		}
		substring = "";
		substring = str.substr(count[count.size() - 1], str.size()-2);
		
		
		
		for (int j = 1; j < substring.size(); j++)
		{
			char k = substring.at(j);
			string s(1, k);
			exp.push_back(s);
		}
	
		CMOS_Circuit_SPICE_Generator(exp);
		exp.clear(); 
		cout << "-------------------------------------------\n";

		
		break;
	}



	
	system("pause");

	return 0;
}
void  CMOS_Circuit_SPICE_Generator(vector <string> str)   
{

	while (str.size() >= 4)  // if the size of the vector is less than 4 then, stop the loop 
	{
		if (str.size() == 4) // for sure if size is 4 it is a negtiation 
		{
			NOT(str[2], str[0]);   // NOT
			str.pop_back();
		}
		if (str.size() == 5)   // if size = 5 it can be only OR or AND
		{
			if (str[3] == "|")      // if OR 
			{

				string k = "or" + str[0];
				OR_2(str[2], str[4], k);
				NOT(k, str[0]);
				// DECREASING THE SIZE 
				str.pop_back();   
				str.pop_back();
			}
			else
			{
				string k = "and" + str[0];  // IF AND 
				AND_2(str[2], str[4], k);
				NOT(k, str[0]);

				str.pop_back();
				str.pop_back();
			}
		}

		for (int i = 0; i < str.size(); i++)  // loop for NOT 
		{

			if (str[i] == "'")
			{
				std::string s = to_string(i);
				string out = "not" + s;
				NOT(str[i - 1], out);
				str[i - 1] = out;
				str.erase(str.begin() + i, str.begin() + i + 1);


			}

		}
		if (str.size() >= 6)
		{
			
			for (int i = 0; i < str.size(); i++) // loop for AND
			{

				if (str[i] == "&")
				{
					std::string s = to_string(i);
					string out = "and" + s;
					
					AND(str[i - 1], str[i + 1], out);
					str[i - 1] = out;
					str.erase(str.begin() + i, str.begin() + i + 2);



					
					
				}
				

			}

		}
		// adding this part to solve the skipping index which results in errors 
		if (str.size() >= 6)
		{
			
			for (int i = 0; i < str.size(); i++)
			{

				if (str[i] == "&")
				{
					std::string s = to_string(i);
					string out = "and" + s;
					
					AND(str[i - 1], str[i + 1], out);
					str[i - 1] = out;
					str.erase(str.begin() + i, str.begin() + i + 2);



					
				}
				

			}

		}
		if (str.size() >= 6)
		{

			for (int i = 0; i < str.size(); i++)
			{
				if (str[i] == "|")
				{
					std::string s = to_string(i);
					string out = "or" + s;
					OR(str[i - 1], str[i + 1], out);
					str[i - 1] = out;
					str.erase(str.begin() + i, str.begin() + i + 2);


					

				}

			}
		}


	}
}
void NOT(string  input, string & out_put)   // skelton for NOT
{
	cout << "M" << input << "1  " << out_put << "  " << input << "   VDD   VDD    PMOS" << endl;
	cout << "M" << input << "2  " << out_put << "  " << input << "   0   0    NMOS" << endl << endl;

}
void AND(string  in_1, string in_2, string & out_put) //skelton for AND
{
	cout << "M" << in_1 << "1  " << out_put << "  " << in_1 << "   VDD   VDD    PMOS" << endl;
	cout << "M" << in_1 << "2  " << out_put << "  " << in_1 << "  DM" << in_2 << "4" << "   "  "DM" << in_2 << "4" << "   NMOS" << endl;
	cout << "M" << in_2 << "1  " << out_put << "  " << in_2 << "   VDD   VDD    PMOS" << endl;
	cout << "M" << in_2 << "2  " << "DM" << in_2 << "4" << "   " << in_2 << "   0   0    NMOS" << endl;
	cout << "M" << out_put << "1  " << "not" << out_put << "  " << out_put << "   VDD   VDD    PMOS" << endl;
	cout << "M" << out_put << "2  " << "not" << out_put << "  " << out_put << "   0   0    NMOS" << endl << endl;
	out_put = "not" + out_put;

}
void OR(string  in_1, string in_2, string & out_put) // skelton for OR 
{
	cout << "M" << in_1 << "1  " << "DM" << in_1 << "1" << "   " << in_1 << "   VDD   VDD    PMOS" << endl;
	cout << "M" << in_1 << "2  " << out_put << "  " << "  " << in_1 << "   0   0    NMOS" << endl;
	cout << "M" << in_2 << "1  " << out_put << "  " << in_2 << "  " << "DM" << in_1 << "1" << "   "  "DM" << in_1 << "1" << "  PMOS" << endl;
	cout << "M" << in_2 << "2  " << out_put << "  " << in_2 << "   0   0    NMOS" << endl;
	cout << "M" << out_put << "1  " << "not" << out_put << "  " << out_put << "   VDD   VDD    PMOS" << endl;
	cout << "M" << out_put << "2  " << "not" << out_put << "  " << out_put << "   0   0    NMOS" << endl << endl;
	out_put = "not" + out_put;
}

void OR_2(string in_1, string in_2, string & out_put)  // OR_2 FOR THE FINAL OR EVALUATING 
{
	cout << "M" << in_1 << "1  " << "DM" << in_1 << "1" << "   " << in_1 << "   VDD   VDD    PMOS" << endl;
	cout << "M" << in_1 << "2  " << out_put << "  " << "  " << in_1 << "   0   0    NMOS" << endl;
	cout << "M" << in_2 << "1  " << out_put << "  " << in_2 << "  " << "DM" << in_1 << "1" << "   "  "DM" << in_1 << "1" << "  PMOS" << endl;
	cout << "M" << in_2 << "2  " << out_put << "  " << in_2 << "   0   0    NMOS" << endl;

}
void AND_2(string in_1, string in_2, string & out_put)  // AND_2 FOR THE FINAL AND EVALUATION 
{
	cout << "M" << in_1 << "1  " << out_put << "  " << in_1 << "   VDD   VDD    PMOS" << endl;
	cout << "M" << in_1 << "2  " << out_put << "  " << in_1 << "  DM" << in_2 << "4" << "   "  "DM" << in_2 << "4" << "   NMOS" << endl;
	cout << "M" << in_2 << "1  " << out_put << "  " << in_2 << "   VDD   VDD    PMOS" << endl;
	cout << "M" << in_2 << "2  " << "DM" << in_2 << "4" << "   " << in_2 << "   0   0    NMOS" << endl;

}

void handle_bracket(string n)   
{
	string str;
	char top = 0;
	stack <char> buffer;
	stack <string> buffer2;
	vector <string> exp2;

	for (int i = 0; i < n.length(); i++) // CHANFGING TO POSTFIX 
	{
		if (n[i] == '(')
			buffer.push(n[i]);
		else if (n[i] == ')' && !buffer.empty())
		{
			top = buffer.top();
			buffer.pop();
			while (top != '(' && !buffer.empty())
			{
				str += top;
				top = buffer.top();
				buffer.pop();
			}
		}
		else if (n[i] == '\'' || n[i] == '&' || n[i] == '|')
		{
			if (!buffer.empty())
				top = buffer.top();
			while (!buffer.empty() && top == '\'' &&  n[i] == '&' ||
				top == '\'' &&  n[i] == '|' ||
				top == '&' &&  n[i] == '|')


			{
				top = buffer.top();
				buffer.pop();
				str += top;
				if (!buffer.empty())
					top = buffer.top();
			}
			buffer.push(n[i]);
		}
		else
			str += n[i];
	}

	while (!buffer.empty())
	{
		top = buffer.top();
		buffer.pop();
		str += top;   // STRING WILL BE IN THE FORM OF Y=AB|CD&| 
	}

	for (int i = 0; i < str.size(); i++)
	{   
		char k = str.at(i);
		string s(1, k);
		exp2.push_back(s);

	}

	while (exp2.size() >= 4)
	{
		if (exp2.size() == 4 || exp2.size() == 5)
		{

			if (exp2.size() == 4)
			{
				NOT(exp2[2], exp2[0]);
				str.pop_back();
				break; 
			}
			if (exp2.size() == 5)
			{
				if (exp2[4] == "|")
				{

					string k = "or" + exp2[0];
					OR_2(exp2[2], exp2[3], k);
					NOT(k, exp2[0]);

					exp2.pop_back();
					exp2.pop_back();
					break;
				}
				else
				{
					string k = "and" + exp2[0];
					AND_2(exp2[2], exp2[3], k);
					NOT(k, exp2[0]);

					exp2.pop_back();
					exp2.pop_back();
					break; 
				}
			}
		}
		if (exp2.size() >= 6)
		{
			for (int i = 0; i < exp2.size(); i++)
			{
				if (exp2.size() > 4) {
					if (exp2[i] == "'")
					{
						std::string s = to_string(i);
						string out = "not" + s;
						NOT(exp2[i - 1], out);
						exp2[i - 1] = out;
						exp2.erase(exp2.begin() + (i), exp2.begin() + (i + 1));
						i = 0;

						/*for (int i = 0; i < exp2.size(); i++)
						{
							cout << exp2[i];
						}
						cout << endl;
						*/
					}
					else if (exp2[i] == "&")
					{
						std::string s = to_string(i);
						string out = "and" + s;

						AND(exp2[i - 1], exp2[i - 2], out);
						exp2[i - 2] = out;
						exp2.erase(exp2.begin() + (i - 1), exp2.begin() + (i + 1));
						i = 0;
					}

					else if (exp2[i] == "|")
					{
						std::string s = to_string(i);
						string out = "or" + s;
						OR(exp2[i - 1], exp2[i - 2], out);
						exp2[i - 2] = out;
						exp2.erase(exp2.begin() + (i - 1), exp2.begin() + i + 1);
						i = 0;
					}
				}
			
			}
		}
	}
}
bool validity (string v)
{
	for (int i = 1; i < v.size() - 1; i++)
	{
		if (v[i] == v[0]) {
			return false;



			if (v[i] == ';' && (v[i + 1] == ' '))
				return false;
			if (v[i] == ';' && (v[i - 1] == ' '))
				return false;

		}

		if (v[v.size() - 1] == '&' || v[v.size() - 1] == '|')
			return false;

		else return true;
	}

}



