#pragma once
#include <functional>
#include <list>

	// Args를 이용해 가변 인수 목록을 나타낼 수 있음 
	// 동작원리는 컴파일 단계에서 타입추론을 통해 실행됨
	template<typename... Args>
	class MyAction
	{
	public:
		using Func = std::function<void(Args...)>;

		// 구독해둔 함수를 리무브 하기위해서는 함수가 존재하는 위치를 아는 반복자를 저장해둬야함
		// 그걸 Handle 구조체에 담아서 반환해준다.
		struct Handle
		{
			typename std::list<Func>::iterator it;
		};

	public:
		MyAction() = default;
		~MyAction() = default;

		// 구독 함수 목록 맨뒤에 추가 함 그리고 핸들을 반환
		Handle AddListener(const Func& fn)
		{
			functions.push_back(fn);
			auto it = --functions.end();
			return Handle{ it };
		}

		Handle operator +=(const Func& fn)
		{
			return AddListener(fn);
		}

		// 구독 해제함
		void RemoveListener(Handle handle)
		{
			functions.erase(handle.it);
		}

		

		// 모든 구독 목록 해제
		void Clear()
		{
			functions.clear();
		}

		void Invoke(Args... args)
		{
			for (auto& fn : functions)
				fn(args...);
		}

		bool HasListener()
		{
			return !functions.empty();
		}

	private:
		// list로 해야함 이걸 벡터는 연속된 메모리 블록이므로 앞쪽에 요소를 리무브 하면 
		// 뒤에 요소들이 모두 앞으로 당겨짐 그래서 반복자들이 가리키고 있던 functions에  주소들이 바뀜
		std::list<Func> functions;
	};

	template<>
	class MyAction<void>
	{
	public:
		using Func = std::function<void()>;

		struct Handle
		{
			std::list<Func>::iterator it;
		};

	public:
		Handle AddListener(const Func& fn)
		{
			functions.push_back(fn);
			return Handle{ std::prev(functions.end()) };
		}

		Handle operator+=(const Func& fn)
		{
			return AddListener(fn);
		}

		void RemoveListener(Handle handle)
		{
			functions.erase(handle.it);
		}

		void Clear()
		{
			functions.clear();
		}

		void Invoke()
		{
			for (auto& fn : functions)
				if (fn) fn();
		}

		bool HasListener()
		{
			return !functions.empty();
		}

	private:
		std::list<Func> functions;
	};
