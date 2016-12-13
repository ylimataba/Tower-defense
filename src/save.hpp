#ifndef TOWER_DEFENCE_SRC_SAVE_HPP
#define	TOWER_DEFENCE_SRC_SAVE_HPP

#include <cstddef>
#include <vector>
#include <utility>

namespace save {

class Save
{
public:
	Save(std::vector<std::pair<std::string, std::string>> &objectsToSave);

	~Save();

	void saveGame();

private:
	Save(const Save&);
	Save& operator=(const Save&);
	
	std::vector<std::pair<std::string, std::string>> m_objectsToSave;	
};


class Load
{
public:
	Load(std::vector<std::pair<std::string, std::string>> &objectsToLoad);

	~Load();

	void emptyPreviousObjects();
	void getObjects();
	bool gameSaveExists();

private:
	Load(const Load&);
	Load& operator=(const Load&);

	bool m_savedGameExists;

	std::vector<std::pair<std::string, std::string>> &m_objectsToLoad;

};

}; // namespace save

#endif //TOWER_DEFENCE_SRC_SAVE_HPP