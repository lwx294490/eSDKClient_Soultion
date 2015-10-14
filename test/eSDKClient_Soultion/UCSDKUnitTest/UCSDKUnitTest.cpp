// UCSrvUnitTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include "cppunit/extensions/TestFactoryRegistry.h"
#include "cppunit/ui/text/TestRunner.h"
#include "cppunit/XmlOutputter.h"
//#include "UTLoadConfFile.h"
//#include "UTLoadDll.h"

int main()
{
	//UTLoadConfFile::Instance()->LoadConfFile();

	CppUnit::TextUi::TestRunner runner;

	std::ofstream outputFile("UnitTest_Results.xml");

	CppUnit::Outputter *myoutputter;
	myoutputter = new CppUnit::XmlOutputter(&runner.result(), outputFile, "UTF-8");
	runner.setOutputter(myoutputter);

	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry("UCSDKUnitTest");
	runner.addTest( registry.makeTest() );

	runner.run();

	//UTLoadDll::Instance()->FreeDll();

//#ifdef _DEBUG
//	system("pause");
//#endif

	return 0;
}

