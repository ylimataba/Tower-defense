#include "save.hpp"
#include <fstream>
#include <iostream>
#include <cstddef>
#include <vector>
#include <sstream>
#include <string>
#include <utility>

namespace save {

Save::Save(std::vector<std::pair<std::string, std::string>> &objectsToSave) :
	m_objectsToSave(objectsToSave)
{
}

Save::~Save() 
{

}

void Save::saveGame()
{
	std::ofstream outfile("../savedGame.txt");

	for (auto it : m_objectsToSave)
	{
		outfile << it.first << ";" << it.second << std::endl;
	}

	outfile.close();
}


Load::Load(std::vector<std::pair<std::string, std::string>> &objectsToLoad) :
	m_objectsToLoad(objectsToLoad),
	m_savedGameExists(false)
{
	emptyPreviousObjects();
	getObjects();
}

Load::~Load()
{

}

void Load::emptyPreviousObjects()
{
	while (!m_objectsToLoad.empty())
	{
		m_objectsToLoad.pop_back();
	}
}

void Load::getObjects()
{
	std::ifstream infile("../savedGame.txt");

	if (!infile.is_open())
	{
		m_savedGameExists = false;
		return;
	}

	m_savedGameExists = true;

	std::pair<std::string, std::string> newPair;
	std::string line;

	while (std::getline(infile, line))
	{
	    std::istringstream iss(line);
	    
	    std::string objectName;

	    for (auto i = 0; i < line.length(); i++)
	    {
	    	if (line.substr(i, 1) == ";")
	    	{
	    		break;
	    	}

    		objectName = objectName + line.substr(i, 1);	    	
	    }

	    if (objectName != "")
	    {
	    	std::string objectInfo = line.substr(objectName.length() + 1, line.length() - objectName.length());

	    	newPair = {objectName, objectInfo};

		    m_objectsToLoad.push_back(newPair);
		}
	}
}

bool Load::gameSaveExists()
{
	return m_savedGameExists;
}

} // namepace save