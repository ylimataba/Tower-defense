#ifndef TOWER_DEFENCE_SRC_SAVE_HPP
#define	TOWER_DEFENCE_SRC_SAVE_HPP

#include <cstddef>
#include <vector>

namespace save {

class Save
{
public:
	Save(std::vector<std::pair<std::string, std::string>> &objectsToSave);

	~Save();

	void loadPreviousGame();
	void saveGame();

private:
	bool m_previousSaveExists;

	std::vector<std::pair<std::string, std::string>> m_objectsToSave;
	
};

}; // namespace save

#endif //TOWER_DEFENCE_SRC_SAVE_HPP