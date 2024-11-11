#include "EntityWrapper.h"
#include "AdminWorld.h"

void IEntityWrapper::EntityCreate(UWorld* pWorld)
{
	if (nullptr == pWorld || !pWorld->IsGameWorld())
		return; //编辑器下
	m_idEntity = UAdminWorld::Get(pWorld)->CreateEntity();
 	m_bCreate = true;
}

void IEntityWrapper::EntityDestroy(UWorld* pWorld)
{
	if (m_bCreate)
	{
		m_bCreate = false;
		UAdminWorld::Get(pWorld)->DestroyEntity(m_idEntity);
	}
}
