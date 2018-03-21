//------------------------------------------------------------------------------
// main.cc
// (C) 2015-2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#ifndef MAIN2_CC
#define MAIN2_CC
#include "config.h"
#include "exampleapp.h"
#include <GL/glut.h>


int
main(int argc, char** argv)
{
	glutInit(&argc, argv);

	Example::ExampleApp app;
	if (app.Open())
	{

		app.Run();
		app.Close();
	}
	app.Exit();
	
}
#endif