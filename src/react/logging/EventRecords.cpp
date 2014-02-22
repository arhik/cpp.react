#include "react/logging/EventRecords.h"

namespace react {

////////////////////////////////////////////////////////////////////////////////////////
/// NodeCreateEvent
////////////////////////////////////////////////////////////////////////////////////////
NodeCreateEvent::NodeCreateEvent(ObjectId nodeId, const char* type) :
	nodeId_{ nodeId },
	type_{ type }
{
}

void NodeCreateEvent::Serialize(std::ostream& out) const
{
	out << "> Node = " << nodeId_ << std::endl;
	out << "> Type = " << type_ << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////
/// NodeDestroyEvent
////////////////////////////////////////////////////////////////////////////////////////
NodeDestroyEvent::NodeDestroyEvent(ObjectId nodeId) :
	nodeId_{ nodeId }
{
}

void NodeDestroyEvent::Serialize(std::ostream& out) const
{
	out << "> Node = " << nodeId_ << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////
/// NodeAttachEvent
////////////////////////////////////////////////////////////////////////////////////////
NodeAttachEvent::NodeAttachEvent(ObjectId nodeId, ObjectId parentId) :
	nodeId_{ nodeId },
	parentId_{ parentId }
{
}

void NodeAttachEvent::Serialize(std::ostream& out) const
{
	out << "> Node = " << nodeId_ << std::endl;
	out << "> Parent = " << parentId_ << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////
/// NodeDetachEvent
////////////////////////////////////////////////////////////////////////////////////////
NodeDetachEvent::NodeDetachEvent(ObjectId nodeId, ObjectId parentId) :
	nodeId_{ nodeId },
	parentId_{ parentId }
{
}

void NodeDetachEvent::Serialize(std::ostream& out) const
{
	out << "> Node = " << nodeId_ << std::endl;
	out << "> Parent = " << parentId_ << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////
/// InputNodeAdmissionEvent
////////////////////////////////////////////////////////////////////////////////////////
InputNodeAdmissionEvent::InputNodeAdmissionEvent(ObjectId nodeId, int transactionId) :
	nodeId_{ nodeId },
	transactionId_{ transactionId }
{
}

void InputNodeAdmissionEvent::Serialize(std::ostream& out) const
{
	out << "> Node = " << nodeId_ << std::endl;
	out << "> Transaction = " << transactionId_ << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////
/// NodePulseEvent
////////////////////////////////////////////////////////////////////////////////////////
NodePulseEvent::NodePulseEvent(ObjectId nodeId, int transactionId) :
	nodeId_{ nodeId },
	transactionId_{ transactionId }
{
}

void NodePulseEvent::Serialize(std::ostream& out) const
{
	out << "> Node = " << nodeId_ << std::endl;
	out << "> Transaction = " << transactionId_ << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////
/// NodeIdlePulseEvent
////////////////////////////////////////////////////////////////////////////////////////
NodeIdlePulseEvent::NodeIdlePulseEvent(ObjectId nodeId, int transactionId) :
	nodeId_{ nodeId },
	transactionId_{ transactionId }
{
}

void NodeIdlePulseEvent::Serialize(std::ostream& out) const
{
	out << "> Node = " << nodeId_ << std::endl;
	out << "> Transaction = " << transactionId_ << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////
/// NodeInvalidateEvent
////////////////////////////////////////////////////////////////////////////////////////
NodeInvalidateEvent::NodeInvalidateEvent(ObjectId nodeId, ObjectId oldParentId, ObjectId newParentId, int transactionId) :
	nodeId_{ nodeId },
	oldParentId_ {oldParentId },
	newParentId_{ newParentId },
	transactionId_{ transactionId }
{
}

void NodeInvalidateEvent::Serialize(std::ostream& out) const
{
	out << "> Node = " << nodeId_ << std::endl;
	out << "> Transaction = " << transactionId_ << std::endl;
	out << "> OldParent = " << oldParentId_ << std::endl;
	out << "> NewParent = " << newParentId_ << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////
/// NodeEvaluateBeginEvent
////////////////////////////////////////////////////////////////////////////////////////
NodeEvaluateBeginEvent::NodeEvaluateBeginEvent(ObjectId nodeId, int transactionId, size_t threadId) :
	nodeId_{ nodeId },
	transactionId_{ transactionId },
	threadId_{ threadId }
{
}

void NodeEvaluateBeginEvent::Serialize(std::ostream& out) const
{
	out << "> Node = " << nodeId_ << std::endl;
	out << "> Transaction = " << transactionId_ << std::endl;
	out << "> Thread = " << threadId_ << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////
/// NodeEvaluateEndEvent
////////////////////////////////////////////////////////////////////////////////////////
NodeEvaluateEndEvent::NodeEvaluateEndEvent(ObjectId nodeId, int transactionId, size_t threadId) :
	nodeId_{ nodeId },
	transactionId_{ transactionId },
	threadId_{ threadId }
{
}

void NodeEvaluateEndEvent::Serialize(std::ostream& out) const
{
	out << "> Node = " << nodeId_ << std::endl;
	out << "> Transaction = " << transactionId_ << std::endl;
	out << "> Thread = " << threadId_ << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////
/// TransactionBeginEvent
////////////////////////////////////////////////////////////////////////////////////////
TransactionBeginEvent::TransactionBeginEvent(int transactionId) :
	transactionId_{ transactionId }
{
}

void TransactionBeginEvent::Serialize(std::ostream& out) const
{
	out << "> Transaction = " << transactionId_ << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////
/// TransactionEndEvent
////////////////////////////////////////////////////////////////////////////////////////
TransactionEndEvent::TransactionEndEvent(int transactionId) :
	transactionId_{ transactionId }
{
}

void TransactionEndEvent::Serialize(std::ostream& out) const
{
	out << "> Transaction = " << transactionId_ << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////
/// UserBreakpointEvent
////////////////////////////////////////////////////////////////////////////////////////
UserBreakpointEvent::UserBreakpointEvent(const char* name) :
	name_{ name }
{
}

void UserBreakpointEvent::Serialize(std::ostream& out) const
{
	out << "> Name = " << name_ << std::endl;
}

// ---
}