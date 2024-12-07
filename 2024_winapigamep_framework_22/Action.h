#pragma once
#include <functional>
#include <algorithm>

class Action
{
public:
	using ActionFunc = std::function<void()>;

	Action& operator+=(ActionFunc func) {
		actions.push_back(func);
		return *this;
	}

	Action& operator-=(ActionFunc func) {
		actions.erase(std::remove_if(actions.begin(), actions.end(),
			[&func](const auto& f) {
				return f.target_type() == func.target_type();
			}),
			actions.end());
		return *this;
	}

	void Invoke() const {
		for (const auto& action : actions) {
			if (action) {
				action();
			}
		}
	}
	void Clear() {
		actions.clear();
	}
private:
	vector<ActionFunc> actions;
};
