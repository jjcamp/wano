/*
* events.h
* Contains the EventQueue class and EventType enum
* Header-only file to prevent linker errors
*/
#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <typeinfo>

namespace wano {
	// Enumeration of allowable event types
	enum EventType {
		MOVE_CURSOR,
		DOC_MOVE
	};

	// Alias this long type that is used several times
	template<typename T>
	using vecfuncvoid = std::vector<std::function<void(T)>>;

	class EventQueue {
	public:
		EventQueue() :
			events() {}

		// Adds an event handler (usually a lambda) which listens for the EventType and 
		// has an input parameter of type T.
		template<typename T> void addHandler(EventType type, std::function<void(T)> handler);
		// Fires an event of the specified EventType, passing along the parameter info
		// of type T.
		template<typename T> void fire(EventType type, T info);

	private:
		// Similar to boost::any
		struct LazyType {
			struct basetype {
				const type_info* typeinfo;
			};
			template<typename T> struct supertype : public basetype {
				T value;
			};
			template<typename T> static LazyType create(T value);
			template<typename T> static T cast(LazyType &c);
			std::unique_ptr<basetype> ptr;
		};

		std::unordered_map<EventType, LazyType> events;
	};
	
	template<typename T>
	void EventQueue::addHandler(EventType type, std::function<void(T)> handler) {
		if (events.count(type) == 0) {
			events[type] = LazyType::create(std::make_shared<vecfuncvoid<T>>(0));
		}
		LazyType::cast<shared_ptr<vecfuncvoid<T>>>(events[type])->push_back(handler);
	}

	template<typename T>
	void EventQueue::fire(EventType type, T info) {
		if (events.count(type) == 1) {
			for (auto h : *LazyType::cast<shared_ptr<vecfuncvoid<T>>>(events[type]).get()) {
				h(info);
			}
		}
	}

	template<typename T>
	static EventQueue::LazyType EventQueue::LazyType::create(T value) {
		auto lt = LazyType();
		auto tinfo = supertype<T>();
		tinfo.value = value;
		tinfo.typeinfo = &typeid(value);
		lt.ptr = make_unique<supertype<T>>(tinfo);
		return lt;
	}

	template<typename T>
	static T EventQueue::LazyType::cast(LazyType &c) {
		if (typeid(T) != *c.ptr->typeinfo) {
			throw bad_cast();
		}
		return ((supertype<T>*)c.ptr.get())->value;
	}
}

