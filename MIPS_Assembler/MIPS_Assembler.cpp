#include "MIPS_Assembler.h"
#include "HTMLContent.h"


MIPS_Assembler::MIPS_Assembler(QWidget *parent)
	: QMainWindow(parent)
{
	this->filePath = "";
	ui.setupUi(this);
	createActions();
}

void MIPS_Assembler::createActions() {
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
	connect(ui.textEdit, SIGNAL(textChanged()), this, SLOT(textChanged()));
	connect(ui.actionTest, SIGNAL(triggered()), this, SLOT(testHTML()));
	connect(ui.actionCopy, SIGNAL(triggered()), this, SLOT(copyFile()));
	connect(ui.actionPaste, SIGNAL(triggered()), this, SLOT(pasteFile()));
	connect(ui.actionCut, SIGNAL(triggered()), this, SLOT(cutFile()));
	connect(ui.actionRedo, SIGNAL(triggered()), this, SLOT(redoFile()));
	connect(ui.actionUndo, SIGNAL(triggered()), this, SLOT(undoFile()));
}

void MIPS_Assembler::openFile() {
	QString fileName = QFileDialog::getOpenFileName(
		this, tr("Open File"), "/", tr("Text File (*.txt)")
	);
	this->filePath = fileName.toStdString();

	std::fstream targetFile;
	targetFile.open(this->filePath, std::ios::in);
	std::string fileLine;
	ui.textEdit->clear();
	if (targetFile.is_open()) {
		while (std::getline(targetFile, fileLine)) {
			//ui.textEdit->append(parseLine(fileLine));
			this->targetFile.append(QString::fromStdString(fileLine));
		}
		ui.textEdit->append(this->targetFile.getLines());
	}
	targetFile.close();
	//qDebug() << ui.textEdit->toHtml();
}

void MIPS_Assembler::saveFile() {
	QString plainText = ui.textEdit->toPlainText();
	if (this->filePath != "") {
		std::ofstream targetFile;
		targetFile.open(this->filePath, std::ios::trunc);
		targetFile << plainText.toStdString();
		targetFile.close();
	}
	fileSaved = true;
	changeWindowTitle();
}

void MIPS_Assembler::changeWindowTitle() {
	QString windowPreText("MIPS Assembler");
	QString newWindowTitle = windowPreText + [&saved=this->fileSaved]()->QString{
		return saved ? "" : "*";
	}()+"  " + QString::fromStdString(this->filePath);
	setWindowTitle(newWindowTitle);
}
void MIPS_Assembler::textChanged() {
	fileSaved = false;
	changeWindowTitle();
	qDebug() << ui.textEdit->toPlainText();
}

QString MIPS_Assembler::parseLine(std::string eachLine) {
	HTMLLine htmlResult;
	htmlResult.hilightRawText(eachLine);
	return htmlResult.fetchHTML();
}
void MIPS_Assembler::testHTML() {
	ui.textEdit->append("<h2>asdf</h2>");
}
