/*
 * CornerGrocer.cpp
 *
 *  Date: 12/11/2022
 *  Author: John Margaronis
 *  Class: CS-210 Programming Languages
 */

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int userSel;
string thread;
string lineFile;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void displayMenu() // function to display the main menu
{
	cout << "************************* User Menu *************************" << endl;
	cout << "*                                                           *" << endl;
	cout << "* 1 - Generate a list of the products and quantities        *" << endl;
	cout << "* 2 - Display the frequency of items                        *" << endl;
	cout << "* 3 - Generate a histogram of sales data                    *" << endl;
	cout << "* 4 - Exit Application                                      *" << endl;
	cout << "*                                                           *" << endl;
	cout << "*************************************************************" << endl;
	cout << "* Please make a selection ...                               *" << endl << endl;
}
void generateList() {
	cout << "--> Now generating a list of items and quantities sold for today ..." << endl << endl;
	CallProcedure("generateList");  // calling to python method generateList
	cout << endl;
}
void displayFrequency() {
	cout << "Please enter the item name:" << endl << endl;;
	cin >> thread;
	cout << endl << endl;
	cout << "--> Outputting sales for " << thread << " ..." << endl << endl;
	cout << "  --> " << thread << ": " << callIntFunc("displayFrequency", thread) << endl << endl;  // calling to python method displayFrequency
}
void writeItems() {
	cout << "--> Writing items and quantities sold today to a file ..." << endl << endl;;
	CallProcedure("writeItems");  // calling to python method writeItems

	ifstream frequencyFile("frequency.dat");
	string item;
	int count;

	while (getline(frequencyFile, lineFile)) {
		istringstream iss(lineFile);
		if (!(iss >> item >> count)) break;
		cout << "  --> " << item << " " << string(count, '*') << endl; // output the histogram
	}
	cout << endl;
}
int main() {
	int userSel = 0;

	while (userSel != 4) {
		displayMenu();
		cin >> userSel;
		cout << endl;
		switch (userSel) {
		case 1: // generate list of products and quantities
			generateList();
			break;
		case 2: // display the frequency of items
			displayFrequency();
			break;
		case 3: // generate the histogram
			writeItems();
			break;
		case 4: // exit the program
			cout << "Corner Grocer now exiting ..." << endl;
			break;
		default:
			cout << "Invalid entry - please select a valid option from the menu above ..." << endl;
			exit(EXIT_SUCCESS);
		}
	}
}