#pragma once

#include <exception>
#include "events.h"
#include "nameddocument.h"

namespace wano {
	namespace services {
		template<typename T>
		class Singleton {
		public:
			static T& get() {
				static T _singleton = T();
				return _singleton;
			}
		};

		class ServiceNotFoundException : public std::exception {};

		template<typename T>
		class Locator {
		public:
			static T& get() {
				if (_service == nullptr)
					throw ServiceNotFoundException();
				return *_service;
			}

			static void set(T& service) {
				_service = &service;
			}

		private:
			static T* _service;
		};
		template<typename T> T* Locator<T>::_service;

		using events = Singleton<EventQueue>;
		using currentNamedDocument = Locator<NamedDocument>;
	}
}