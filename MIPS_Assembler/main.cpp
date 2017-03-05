#include "MIPS_Assembler.h"
#include <QtWidgets/QMainWindow>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MIPS_Assembler w;
	w.show();
	return a.exec();
}
