#include "save.hpp"
#include <fstream>
#include <iostream>
#include <cstddef>
#include <vector>

namespace save {

Save::Save(std::vector<std::pair<std::string, std::string>> &objectsToSave)
	: m_previousSaveExists(false),
	  m_objectsToSave(objectsToSave)
{
}

Save::~Save() 
{

}

void Save::loadPreviousGame()
{

}

void Save::saveGame()
{
	std::ofstream outfile("../savedGame.txt");

	outfile << "Tower Defense - Game Save\n";

	for (auto it : m_objectsToSave)
	{
		outfile << it.first << ";" << it.second << std::endl;
	}

	outfile.close();
}

}; // namepace save