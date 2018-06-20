//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Table.cpp
//

#include "Table.hpp"

Table::Table(irr::gui::IGUITable *tab, int id)	
{
	table = tab;
	_col = 0;
	_row = 1;
	_id = id;
	addCol(L"");
	table->setResizableColumns(false);
}

Table::Table()
{
}

Table::~Table()
{
}

void Table::addCol(const wchar_t* name)
{	
	table->addColumn(name, _col);
	table->setColumnWidth(_col, 75);
	_colName.push_back(name);
	_col += 1;
}

void Table::addRow(const wchar_t* name)
{
	table->addRow(_row);
	_rowName.push_back(name);
	setValue(0, _row, this->wcToString(name));
	_row += 1;
}

bool Table::setValue(int col, int row, const std::string &data)
{

	if (col < 0 || col > _col || row < 0 || row > _row) {	
		std::cerr << "Can't access cell at (" << col  << ", " << row <<
			")\n";
		return false;
	} else {
		const wchar_t *text = this->getWC(data.c_str());
		table->setCellText(row - 1, col, text);
		delete text;
		return true;
	}
}

bool Table::setValue(const std::string &colName, const std::string &rowName,
		     const std::string &data)
{
	int col = getIdFromCol(this->getWC(colName.c_str()));
	int row = getIdFromRow(this->getWC(rowName.c_str()));

	std::cout << col << " " << row << "\n";
	if (col < 0 || col > _col || row < 0 || row > _row) {	
	std::cerr << "Can't access cell at (" << col  << ", " << row <<
			")\n";
		return false;
	} else {
		const wchar_t *text = this->getWC(data.c_str());
		table->setCellText(row - 1, col, text);
		delete text;
		return true;
	}
	
}

int Table::getIdFromCol(const wchar_t *colName)
{
	int count = -1;
	int counter = -1;	
	bool okay;

	for (std::vector<const wchar_t *>::iterator it = _colName.begin();
	     it != _colName.end(); ++it) {
		okay = true;
		count += 1;
		counter = -1;		
		while ((*it)[++counter] && okay) {
			if ((*it)[counter] != colName[counter]) {
				okay = false;
			}				
		}
		if (counter != 0 && okay) {
			return count;
		}
	}
	return -1;
}

int Table::getIdFromRow(const wchar_t *rowName)
{
	int count = 0;
	int counter = -1;
	bool okay;
		
	for (std::vector<const wchar_t *>::iterator it = _rowName.begin();
	     it != _rowName.end(); ++it) {
		okay = true;
		count += 1;
		counter = -1;		
		while ((*it)[++counter] && okay) {
			if ((*it)[counter] != rowName[counter])
				okay = false;	
		}
		if (counter != 0 && okay) {
			return count;
		}
	}
	return -1;
}

void Table::setVisible(bool visible)
{
	table->setVisible(visible);	
}

int Table::getId() const
{
	return _id;
}

void Table::initTable()
{
	addCol(L"Level 1");
	addCol(L"Level 2");
	addCol(L"Level 3");
	addCol(L"Level 4");
	addCol(L"Level 5");
	addCol(L"Level 6");
	addCol(L"Level 7");	
	addCol(L"Level 8");
}

void Table::addTeamName(std::vector<std::string> list)
{
	for (auto it = list.begin(); it != list.end(); ++it) {
		const wchar_t *text = this->getWC(it->c_str());
		addRow(text);
		delete text;
	}
}

const wchar_t *Table::getWC(const char *str)
{
    const size_t cSize = strlen(str) + 1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs(wc, str, cSize);
    return (wc);
}

std::string	Table::wcToString(const wchar_t *arr)
{
	int	size = wcslen(arr);
	char *str = (char *)malloc(size + 1);
	memset(str, 0, size);
	wcstombs(str, arr, size);
	return (std::string(str));
}