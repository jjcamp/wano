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

using namespace std;

namespace wano {
	// Enumeration of allowable event types
	enum EventType {
		MOVE_CURSOR,
		DOC_MOVE
	};

	class EventQueue {
	public:
		EventQueue() :
			events() {}

		// Adds an event handler (usually a lambda) which listens for the EventType and 
		// has an input parameter of type T.
		template<typename T> void addHandler(EventType type, function<void(T)> handler);
		// Fires an event of the specified EventType, passing along the parameter info
		// of type T.
		template<typename T> void fire(EventType type, T info);

	private:
		struct LazyType {
			struct basetype {
				const type_info* typeinfo;
			};
			template<typename T> struct supertype : public basetype {
				T value;
			};
			template<typename T> static LazyType create(T t);
			template<typename T> static T cast(LazyType &c);
			unique_ptr<basetype> ptr;
		};

		unordered_map<EventType, LazyType> events;
	};
	
	template<typename T>
	void EventQueue::addHandler(EventType type, function<void(T)> handler) {
		if (events.count(type) == 0) {
			events[type] = LazyType::create<shared_ptr<vector<function<void(T)>>>>(make_shared<vector<function<void(T)>>>(vector<function<void(T)>>(0)));
		}
		LazyType::cast<shared_ptr<vector<function<void(T)>>>>(events[type])->push_back(handler);
	}

	template<typename T>
	void EventQueue::fire(EventType type, T info) {
		if (events.count(type) == 1) {
			auto v = LazyType::cast<shared_ptr<vector<function<void(T)>>>>(events[type]);
			auto vp = v.get();
			for (auto h : *vp) {
				h(info);
			}
		}
	}

	template<typename T>
	static EventQueue::LazyType EventQueue::LazyType::create(T t) {
		auto lt = LazyType();
		auto tinfo = supertype<T>();
		tinfo.value = t;
		tinfo.typeinfo = &typeid(t);
		lt.ptr = make_unique<supertype<T>>(tinfo);
		return lt;
	}

	template<typename T>
	static T EventQueue::LazyType::cast(LazyType &c) {
		if (typeid(T) != *c.ptr->typeinfo) {
			throw bad_cast();
		}
		auto ret = ((supertype<T>*)c.ptr.get())->value;
		return ret;
	}
}

