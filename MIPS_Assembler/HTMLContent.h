#pragma once
#include <QtWidgets/QMainWindow>
class HTMLLine
{
public:
	HTMLLine();
	~HTMLLine();
	void addKeyword(QString keyWord);
	void addVariable(QString vaiable);
	void addComment(QString comment);
	void addOperator(QString oneOperator);
	QString fetchHTML() {
		return this->htmlContent;
	}
	void hilightRawText(std::string rawText);
private:
	QString htmlContent;
	void guessAName(QString oneToken);
};

