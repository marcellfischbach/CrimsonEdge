#include <ceCore/entity/csEntityState.hh>
#include "csEntity.hh"
#include <ceCore/entity/csWorld.hh>
#include <entity/entitystate.refl.hh>

namespace cryo
{

csEntityState::csEntityState(const std::string &name)
  : iObject()
  , m_name(name)
  , m_needUpdate(false)
  , m_entity(nullptr)
{
  CS_CLASS_GEN_CONSTR;
}

csEntityState::~csEntityState()
{

}

void csEntityState::SetName(const std::string &name)
{
  m_name = name;
}

const std::string &csEntityState::GetName() const
{
  return m_name;
}

void csEntityState::SetEntity(csEntity *entity)
{
  if (m_entity != entity)
  {
    csEntity * oldEntity = m_entity;
    m_entity = entity;
    
    UpdateEntity(oldEntity, m_entity);
    
    CS_ADDREF(m_entity);
    CS_RELEASE(oldEntity);
  }
}

csEntity* csEntityState::GetEntity()
{
  return m_entity;
}


csEntityState* csEntityState::GetState(const Class* cls)
{
  return m_entity ? m_entity->GetState(cls) : nullptr;
}

const csEntityState* csEntityState::GetState(const Class* cls) const
{
  return m_entity ? static_cast<const csEntity*>(m_entity)->GetState(cls) : nullptr;
}


std::vector<csEntityState*> csEntityState::GetStates(const Class* cls)
{
  return m_entity ? m_entity->GetStates(cls) : std::vector<csEntityState*>();
}

std::vector<const csEntityState*> csEntityState::GetStates(const Class* cls) const
{
  return m_entity ? static_cast<const csEntity*>(m_entity)->GetStates(cls) : std::vector<const csEntityState*>();
}


const csEntity* csEntityState::GetEntity() const
{
  return m_entity;
}

csSpatialState* csEntityState::GetRoot()
{
  return m_entity ? m_entity->GetRoot() : nullptr;
}


const csSpatialState* csEntityState::GetRoot() const
{
  return m_entity ? m_entity->GetRoot() : nullptr;
}

csWorld* csEntityState::GetWorld()
{
  return m_entity ? m_entity->GetWorld() : nullptr;
}

const csWorld* csEntityState::GetWorld() const
{
  return m_entity ? m_entity->GetWorld() : nullptr;
}

void csEntityState::SetNeedUpdate(bool needUpdate)
{
  if (m_needUpdate != needUpdate)
  {
    csWorld * world = GetWorld();
    if (world && m_needUpdate)
    {
      world->DetachUpdateState(this);
    }
    m_needUpdate = needUpdate;
    if (world && m_needUpdate)
    {
      world->AttachUpdateState(this);
    }
  }
}

bool csEntityState::IsNeedUpdate() const
{
  return m_needUpdate;
}

void csEntityState::UpdateEntity(csEntity *oldEntity, csEntity *newEntity)
{
  if (oldEntity)
  {
    oldEntity->DeregisterEntityState(this);
  }
  if (newEntity)
  {
    newEntity->RegisterEntityState(this);
  }
}

void csEntityState::AttachToWorld(csWorld *world)
{
  if (m_needUpdate)
  {
    world->AttachUpdateState(this);
  }
  OnAttachedToWorld(world);
}

void csEntityState::DetachFromWorld(csWorld *world)
{
  if (m_needUpdate)
  {
    world->DetachUpdateState(this);
  }
  OnDetachedFromWorld(world);
}


void csEntityState::OnAttachedToWorld(csWorld* world)
{
}

void csEntityState::OnDetachedFromWorld(csWorld* world)
{

}

void csEntityState::Update(float tpf)
{
  // nothing to be done
}

}
