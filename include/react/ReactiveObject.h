#pragma once

#include "Signal.h"
#include "EventStream.h"
#include "Observer.h"
#include "Conversion.h"

////////////////////////////////////////////////////////////////////////////////////////
namespace react {

////////////////////////////////////////////////////////////////////////////////////////
/// DynamicSignal_
////////////////////////////////////////////////////////////////////////////////////////
//template
//<
//	typename TDomain,
//	typename S
//>
//class DynamicSignal_ : public Signal_<TDomain,S>
//{
//public:
//	DynamicSignal_() :
//		Signal_(),
//		owner_{ nullptr }
//	{
//	}
//
//	DynamicSignal_(Signal_&& other, void* owner) :
//		Signal_(std::move(other)),
//		owner_{ owner }
//	{
//	}
//
//	void*	Owner() const		{ return owner_; }
//
//protected:
//	void*	owner_;
//};

////////////////////////////////////////////////////////////////////////////////////////
/// ReactiveObject
////////////////////////////////////////////////////////////////////////////////////////
template <typename TDomain>
class ReactiveObject
{
public:
	////////////////////////////////////////////////////////////////////////////////////////
	/// Aliases
	////////////////////////////////////////////////////////////////////////////////////////
	template <typename S>
	using Signal = Signal_<TDomain,S>;

	template <typename S>
	using VarSignal = VarSignal_<TDomain,S>;

	//template <typename S>
	//using DynamicSignal = DynamicSignal_<TDomain,S>;

	template <typename E>
	using Events = Events_<TDomain,E>;

	template <typename E>
	using EventSource = EventSource_<TDomain,E>;

	using Observer = Observer_<TDomain>;

	////////////////////////////////////////////////////////////////////////////////////////
	/// MakeVar (higher order signal)
	////////////////////////////////////////////////////////////////////////////////////////
	template
	<
		template <typename Domain_, typename Val_> class TOuter,
		typename TInner
	>
	inline auto MakeVar(const TOuter<TDomain,TInner>& value)
		-> VarSignal<Signal<TInner>>
	{
		return react::MakeVar<TDomain>(value);
	}

	////////////////////////////////////////////////////////////////////////////////////////
	/// MakeVar
	////////////////////////////////////////////////////////////////////////////////////////
	template <typename S>
	inline auto MakeVar(const S& value)
		-> VarSignal<S>
	{
		return react::MakeVar<TDomain>(value);
	}

	////////////////////////////////////////////////////////////////////////////////////////
	/// MakeSignal
	////////////////////////////////////////////////////////////////////////////////////////
	template
	<
		typename TFunc,
		typename ... TArgs
	>
	inline auto MakeSignal(TFunc func, const Signal<TArgs>& ... args)
		-> Signal<decltype(func(args() ...))>
	{
		typedef decltype(func(args() ...)) S;

		return react::MakeSignal<TDomain>(func, args ...);
	}

	////////////////////////////////////////////////////////////////////////////////////////
	/// MakeEventSource
	////////////////////////////////////////////////////////////////////////////////////////
	template <typename E>
	inline auto MakeEventSource()
		-> EventSource<E>
	{
		return react::MakeEventSource<TDomain,E>();
	}

	////////////////////////////////////////////////////////////////////////////////////////
	/// DYNAMIC_REF
	////////////////////////////////////////////////////////////////////////////////////////
	#define DYNAMIC_REF(obj, name)	\
	Flatten(						\
		MakeSignal([] (				\
			Identity<decltype(obj)>::Type::ValueT r) { return r->name; }, obj))
};

} //~namespace react