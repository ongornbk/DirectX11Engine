#pragma once
#include "Unit.h"
#include "VariablesManager.h"
#include "Doodads.h"
#include "gdef.h"
#include "modern/modern_handle.h"
#include "modern/modern_pack2.h"
#include "modern/modern_pack4.h"
#include <stack>
#include <unordered_set>
#include <set>
//#include <boost/bimap/bimap.hpp>

class Global : public modern_class
{
	
public:
	Global(void);
	~Global(void);
	modern_handle                      m_lastPickedUnit;
	modern_handle                      m_dyingUnit;
	modern_handle                      m_killingUnit;
	modern_handle                      m_triggeringUnit;
	modern_handle                      m_lastSelectedUnit;
	modern_handle                      m_castingUnit;
	modern_handle                      m_levelingUnit;
	modern_handle                      m_lastCreatedRenderContainer;
	modern_handle                      m_pickedObject;
	modern_handle                      m_triggeringRegion;
	modern_handle                      m_leavingObject;
	modern_handle                      m_enteringObject;
	modern_handle                      m_matchingObject;
	modern_handle                      m_pickedPlayer;
	MSVC_VOLATILE ObjectFlags          m_lastFlags{};
	MSVC_VOLATILE Task*                m_lastTask;
	static Global*       GetInstance();
	struct DirectX::XMFLOAT3             m_lastPoint;
	std::stack<Unit*>    m_stack;
	VariablesManager     m_variables;
	uint32               m_size;

	XMVECTOR camera_up;
	XMVECTOR camera_lookat;

	//std::map<class modern_handle*, std::set<modern_handle*, modern_handle_less>, modern_handle_less> m_binaryMapPack2;
	//std::map<class modern_weak_handle,std::set<modern_weak_handle, modern_weak_handle_less>,modern_weak_handle_less> m_bmap2weak;
	//std::map<struct modern_pack4, int64> m_bmap4;
	//boost::bimap<class modern_handle*, class modern_handle*, modern_handle_less> m_bimap2;
	//boost::bimaps::bimap<class modern_handle*, class modern_handle*> m_bimap2;
	std::map<class modern_handle*, std::set<class modern_handle*, modern_handle_less>*,modern_handle_less> m_mp2;




	void getS(std::string name) const;
	void release();

	
};

