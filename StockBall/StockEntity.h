#include "QString"
#include <map>

const QString dataXml = "data.xml";			//�Զ���xml


class CEntity
{

public:
	std::string name;
	std::string code;
	int		index;
};

class CStock
	: public CEntity
{
public:
	CStock();
	~CStock();
};

class CIndex
	: public CEntity
{
public:
	CIndex();
	~CIndex();
};

class CStockManager
{
public:

	static CStockManager* instance();

	//��������
	void loadData();

public:
	CStockManager() : _mapEntity(), _mapMainEntity(), _mapFavirateEntity()
	{}
	~CStockManager(){}

private:
	std::map<std::string, CEntity*> _mapEntity;	//code:Entity �ܵ�map
	std::map<std::string, CEntity*>_mapMainEntity;	//�������
	std::map<std::string, CEntity*>_mapFavirateEntity;	//����ϵ�
};


