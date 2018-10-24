//------------------------------------------------------------------------------
// main.cc
// (C) 2015 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "assignmentapp.h"

int
main(int argc, const char** argv)
{
	Example::AssignmentApp & app = Example::AssignmentApp::GetInstance();
	if (app.Open())
	{
		app.Run();
		app.Close();
	}
	app.Exit();
	
}