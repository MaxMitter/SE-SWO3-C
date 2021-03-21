#include <ml5/ml5.h>
#include "./lib/ast_application.h"


int main(int argc, char* argv[]) {
	wxImage::AddHandler(new wxPNGHandler);
	ast_application{}.run(argc, argv);
	wxImage::CleanUpHandlers();
}