#include "save.hpp"
#include <fstream>
#include <iostream>
#include <cstddef>
#include <vector>
#include <sstream>
#include <string>

namespace save {

Save::Save(std::vector<std::pair<std::string, std::string>> &objectsToSave)
	: m_objectsToSave(objectsToSave)
{
}

Save::~Save() 
{

}

void Save::saveGame()
{
	std::ofstream outfile("../savedGame.txt");

	outfile << "Tower Defense - Saved Game\n";

	for (auto it : m_objectsToSave)
	{
		outfile << it.first << ";" << it.second << std::endl;
	}

	outfile.close();
}


Load::Load()
{
	getObjects();
}

Load::~Load()
{

}

void getObjects()
{
	std::ifstream infile("savedGame.txt");

	std::vector<std::pair<std::string, std::string>> objectsVector;
	std::pair<std::string, std::string> newPair;
	std::string line;

	while (std::getline(infile, line))
	{
	    std::istringstream iss(line);
	    
	    std::string objectName;

	    for (int i = 0; i << line.length(); i++)
	    {
	    	if (line.substr(i, 1) != ";")
	    	{
	    		objectName = objectName + line.substr(i, 1);
	    	}

	    	break;
	    }

	    if (objectName != "")
	    {
	    	std::string objectInfo = line.substr(objectName.length() + 1, line.length() - objectName.length());

	    	newPair = {objectName, objectInfo};

		    objectsVector.push_back(newPair);
		}
	}

	m_objectsToLoad = objectsVector;
}


}; // namepace save