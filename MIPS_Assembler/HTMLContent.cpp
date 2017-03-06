#include "HTMLContent.h"
#define KEYWORD_COLOR "#e74c3c"
#define VARIABLE_COLOR "#16a085"
#define COMMENT_COLOR "#bdc3c7"
#define OPERATOR_COLOR "#9b59b6"
#define START_COLOR "#3498db"


HTMLLine::HTMLLine()
{
	this->htmlContent = "";
}


HTMLLine::~HTMLLine()
{
}

void HTMLLine::addKeyword(QString keyWord) {
	this->htmlContent.append(QString("<span style='color: %2'>%1</span>").arg(keyWord, KEYWORD_COLOR));
}



void HTMLLine::addVariable(QString variable) {
	this->htmlContent.append(QString("<span style='color: %2'>%1</span>").arg(variable, VARIABLE_COLOR));
}
void HTMLLine::addStart(QString start)
{
	this->htmlContent.append(QString("<span style='color: %2'>%1</span>").arg(start, START_COLOR));
}
void HTMLLine::addComment(QString comment) {
	this->htmlContent.append(QString("<span style='color: %2'>%1</span>").arg(comment, COMMENT_COLOR));
}
void HTMLLine::addOperator(QString oneOperator) {
	this->htmlContent.append(QString("<span style='color: %2'>%1</span>").arg(oneOperator, OPERATOR_COLOR));
}

void HTMLLine::hilightRawText(std::string rawText) {
	QString qLine;
	qLine = QString::fromStdString(rawText);
	QRegExp instrucReg("(\\s*)?(\\w+)(\\s+)(\\$\\w+)(\\s*)?(,)(\\s*)?(\\$\\w+)(\\s*)?(,)(\\s*)?(\\$\\w+)(\\s*)?(;)(\\s*)(\\/\\/.*)?");
	// Pattern: add $zero, $zero, $zero;
	QRegExp startReg("(\\s*)(\\w+)(\\s*)(:)(\\s*)(\\/\\/.*)?");
	// Pattern: start:\n
	QRegExp labelReg("(\\s*)(\\.\\w+)(\\s+)(\\w+)(\\s*)(\\/\\/.*)?");
	// Pattern: .text 0x00000000
	QRegExp commentReg("(\\s*)(\\/\\/.*)");
	// Pattern: //comment here
	QRegExp blockReg("(\\s*)([\\w]+)(\\s+)(\\w+)(\\s*)(;)(\\s*)(\\/\\/.*)?");

	int instructPos = instrucReg.indexIn(qLine);
	int startPos = startReg.indexIn(qLine);
	int labelPos = labelReg.indexIn(qLine);
	int commentPos = commentReg.indexIn(qLine);
	int blockPos = blockReg.indexIn(qLine);
	QStringList instructTokens = instrucReg.capturedTexts();
	QStringList startTokens = startReg.capturedTexts();
	QStringList labelTokens = labelReg.capturedTexts();
	QStringList commentTokens = commentReg.capturedTexts();
	QStringList blockTokens = blockReg.capturedTexts();
	if (instructPos > -1) {
		for (int i = 1; i < instructTokens.count(); i++) {
			this->guessAName(instructTokens.at(i));
		}
	}
	else if (startPos > -1) {
		for (int i = 1; i < startTokens.count(); i++) {
			this->guessAName(startTokens.at(i));
		}
	}
	else if (labelPos > -1) {
		for (int i = 1; i < labelTokens.count(); i++) {
			this->guessAName(labelTokens.at(i));
		}
	}
	else if (commentPos > -1) {
		for (int i = 1; i < commentTokens.count(); i++) {
			this->guessAName(commentTokens.at(i));
		}
	}
	else if (blockPos > -1) {
		for (int i = 1; i < blockTokens.count(); i++) {
			this->guessAName(blockTokens.at(i));
		}
	}
	else {
		this->addVariable(QString::fromStdString(rawText));
	}
}

void HTMLLine::guessAName(QString oneToken)
{
	QString htmlResult;
	if (oneToken.contains('$')) {
		this->addVariable(oneToken);
	}
	else if (oneToken.contains(',') || oneToken.contains(';')){
		this->addOperator(oneToken);
	}
	else if (oneToken.contains("//")) {
		this->addComment(oneToken);
	}
	else if (oneToken.contains("st")) {
		this->addStart(oneToken);
	}
	else if (oneToken.contains(':')) {
		this->addOperator(oneToken);
	}
	else if (oneToken.contains('.')) {
		this->addKeyword(oneToken);
	}
	else if (oneToken.contains('x')) {
		this->addVariable(oneToken);
	}
	else {
		this->addKeyword(oneToken);
	}
}
