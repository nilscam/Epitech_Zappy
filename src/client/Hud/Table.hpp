//
// EPITECH PROJECT, 2018
// zappy
// File description:
// Table.cpp
//

#ifndef TABLE_HPP
#define TABLE_HPP

#include "include.hpp"
#include <string>
#include <vector>
#include <iostream>
#include "Rectangle.hpp"

class Table
{
public:
	Table(irr::gui::IGUITable *tab, int id);
	Table();
	~Table();
	void addCol(const wchar_t *name);
	void addRow(const wchar_t *name);
	
	bool setValue(int col, int row, const wchar_t *value);
	/* setValue in a cell from row and col nb */
	
	bool setValue(const wchar_t *colName, const wchar_t *rowName,
		      const wchar_t *data);
	/* setValue in a cell from row and col name */

	int getIdFromRow(const wchar_t * rowName);
	int getIdFromCol(const wchar_t * colName);
	void setVisible(bool visible);
	int getId() const;
	
	void initTable();
	/* init the column */
	
	void addTeamName(std::vector<const wchar_t *> list);
	/* init the row from a list of name */
private:
	int _col;
	int _row;
	int _id;
	irr::gui::IGUITable *table;
	std::vector<const wchar_t *> _colName;
	std::vector<const wchar_t *> _rowName;
};

#endif
