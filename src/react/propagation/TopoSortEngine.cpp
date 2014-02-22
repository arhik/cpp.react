#include "react/propagation/TopoSortEngine.h"

////////////////////////////////////////////////////////////////////////////////////////
namespace react {
namespace topo_sort_impl {

////////////////////////////////////////////////////////////////////////////////////////
/// Node
////////////////////////////////////////////////////////////////////////////////////////
Node::Node() :
	Level(0),
	NewLevel(0),
	Collected(false)
{
}

////////////////////////////////////////////////////////////////////////////////////////
/// Turn
////////////////////////////////////////////////////////////////////////////////////////
Turn::Turn(TransactionData<Turn>& transactionData) :
TurnBase(transactionData),
	ExclusiveSequentialTransaction(transactionData.Input())
{
}

////////////////////////////////////////////////////////////////////////////////////////
/// TopoSortEngine
////////////////////////////////////////////////////////////////////////////////////////
TopoSortEngine::TopoSortEngine()
{
}

void TopoSortEngine::OnNodeAttach(Node& node, Node& parent)
{
	parent.Successors.Add(node);

	if (node.Level <= parent.Level)
		node.Level = parent.Level + 1;
}

void TopoSortEngine::OnNodeDetach(Node& node, Node& parent)
{
	parent.Successors.Remove(node);
}

void TopoSortEngine::OnTransactionCommit(TransactionData<Turn>& transaction)
{
	Turn turn(transaction);

	if (! BeginTransaction(turn))
		return;

	transaction.Input().RunAdmission(turn);
	transaction.Input().RunPropagation(turn);	

	while (!collectBuffer_.empty() || !scheduledNodes_.Empty())
	{
		// Merge thread-safe buffer of nodes that pulsed during last turn into queue
		for (auto node : collectBuffer_)
			scheduledNodes_.Push(node);
		collectBuffer_.clear();

		auto curNode = scheduledNodes_.Top();
		auto currentLevel = curNode->Level;

		// Pop all nodes of current level and start processing them in parallel
		do
		{
			scheduledNodes_.Pop();

			if (curNode->Level < curNode->NewLevel)
			{
				curNode->Level = curNode->NewLevel;
				invalidateSuccessors(*curNode);
				scheduledNodes_.Push(curNode);
				break;
			}

			curNode->Collected = false;

			// Tick -> if changed: OnNodePulse -> adds child nodes to the queue
			tasks_.run(std::bind(&Node::Tick, curNode, &turn));

			if (scheduledNodes_.Empty())
				break;

			curNode = scheduledNodes_.Top();
		}
		while (curNode->Level == currentLevel);

		// Wait for tasks of current level
		tasks_.wait();

		if (shiftRequests_.size() > 0)
		{
			for (auto req : shiftRequests_)
				applyShift(*req.ShiftingNode, *req.OldParent, *req.NewParent, turn);
			shiftRequests_.clear();
		}
	}

	EndTransaction(turn);
}

void TopoSortEngine::OnNodePulse(Node& node, Turn& turn)
{
	processChildren(node, turn);
}

void TopoSortEngine::OnNodeShift(Node& node, Node& oldParent, Node& newParent, Turn& turn)
{
	// Invalidate may have to wait for other transactions to leave the target interval.
	// Waiting in this task would block the worker thread, so we defer the request to the main
	// transaction loop (see applyInvalidate).
	ShiftRequestData d = {&node, &oldParent, &newParent};
	shiftRequests_.push_back(d);
}

//tbb::parallel_for(tbb::blocked_range<NodeVectorT::iterator>(curNodes.begin(), curNodes.end(), 1),
//	[&] (const tbb::blocked_range<NodeVectorT::iterator>& range)
//	{
//		for (const auto& succ : range)
//		{
//			succ->Counter++;

//			if (succ->SetMark(mark))
//				nextNodes.push_back(succ);
//		}
//	}
//);

void TopoSortEngine::applyShift(Node& node, Node& oldParent, Node& newParent, Turn& turn)
{
	OnNodeDetach(node, oldParent);
	OnNodeAttach(node, newParent);

	invalidateSuccessors(node);
	//recalculateLevels(node);

	//scheduledNodes_.Invalidate();

	// Re-schedule this node
	node.Collected = true;
	collectBuffer_.push_back(&node);
}

void TopoSortEngine::processChildren(Node& node, Turn& turn)
{
	// Add children to queue
	for (auto* succ : node.Successors)
	{
		if (!succ->Collected.exchange(true))
			collectBuffer_.push_back(succ);
	}
}

void TopoSortEngine::invalidateSuccessors(Node& node)
{
	for (auto* succ : node.Successors)
	{
		if (succ->NewLevel <= node.Level)
			succ->NewLevel = node.Level + 1;
	}
}

} // ~namespace react::topo_sort_impl
} // ~namespace react