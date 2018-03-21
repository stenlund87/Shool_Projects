//------------------------------------------------------------------------------
/**
	Application class used for example application.
	
	(C) 2015 Individual contributors, see AUTHORS file
*/
//------------------------------------------------------------------------------

#ifndef ASSIGNMENTAPP_H
#define ASSIGNMENTAPP_H

#include "core/app.h"
#include "render/window.h"
#include "2d/2dapp.h"

class Shape;


namespace Example
{
class AssignmentApp : public App2D::BaseApp
{

public:
	static AssignmentApp& GetInstance()
	{
		static AssignmentApp instance;
		return instance;
	}

	/// destructor
	~AssignmentApp();

	/// initialize, create shapes etc
	void Setup();

	/// update app, draw lines etc
	void Update();

	/// line drawing function
	static void DrawLine(const LineData & line);

private:
	/// constructor hidden because it is a singleton
	AssignmentApp();
	/// also hidden because of the singleton
	AssignmentApp(AssignmentApp const &);
	/// also hidden because of the singleton
	void operator=(AssignmentApp const &);

	std::vector<Shape*>saved_shapes;
	float f;
};

//------------------------------------------------------------------------------
/**
*/
inline void 
AssignmentApp::DrawLine( const LineData & line )
{
	AssignmentApp::GetInstance().AddLine(line);
}
} // namespace Example


#endif // !ASSIGNMENTAPP_H