#pragma once


#include <map>
#include <functional>
#include <typeinfo>

namespace Aether {
	struct Event
	{
		virtual ~Event() {}
	};

	using EventMap = std::multimap<const std::type_info*, const std::function<void(const Event&)>>;

	class EventManager
	{
	public:
		template<typename T>
		static void On(const std::function<void(const Event&)>& fn)
		{
			eventMap.emplace(&typeid(T), fn);
		}

		static void Emit(const Event& event) {
			auto range = eventMap.equal_range(&typeid(event));
			for (auto& it = range.first; it != range.second; ++it)
				it->second(event);
		}
	private:
		static EventMap eventMap;
	};
}