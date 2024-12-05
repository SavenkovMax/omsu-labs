#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>


struct FunctionalDependency {
	std::set<std::string> lhs{};
	std::set<std::string> rhs{};
};

template <typename T>
void PrintSet(const std::set<T>& set) {
	for (auto& item : set) {
		std::cout << item << ' ';
	}
}

void PrintDependencies(const std::vector<FunctionalDependency>& fds) {
	for (auto& fd : fds) {
		PrintSet(fd.lhs);
		std::cout << " -> ";
		PrintSet(fd.rhs);
		std::cout << '\n';
	}
}

std::set<std::string> Closure(const std::set<std::string>& attributes,
	const std::vector<FunctionalDependency>& fds) {

	std::set<std::string> closure(attributes);
	bool updated;

	do {
		updated = false;
		for (auto& fd : fds) {
			if (std::includes(closure.begin(), closure.end(), fd.lhs.begin(), fd.lhs.end())) {
				size_t sz_before = closure.size();
				closure.insert(fd.rhs.begin(), fd.rhs.end());
				if (sz_before > closure.size()) {
					updated = true;
				}
			}
		}

	} while (updated);

	return closure;
}

std::vector<FunctionalDependency> NormalizeDependencies(const std::vector<FunctionalDependency>& fds) {
	std::vector<FunctionalDependency> normalize;

	for (auto& fd : fds) {
		for (auto& attribute : fd.rhs) {
			FunctionalDependency dependency = { {fd.lhs.begin(), fd.lhs.end()}, {attribute} };
			normalize.push_back(dependency);
		}
	}

	return normalize;
}

std::vector<FunctionalDependency> RemoveRedurantDependencies(const std::vector<FunctionalDependency>& fds) {
	std::vector<FunctionalDependency> minimized = fds;

	for (size_t i = 0; i < minimized.size(); ++i) {
		std::vector<FunctionalDependency> tmp = minimized;
		tmp.erase(tmp.begin() + i);

		auto closure = Closure(minimized[i].lhs, tmp);
		if (std::includes(closure.begin(), closure.end(), minimized[i].rhs.begin(), minimized[i].rhs.end())) {
			minimized.erase(minimized.begin() + i);
			--i;
		}
	}

	return minimized;
}

std::vector<FunctionalDependency> MinimizeLHS(const std::vector<FunctionalDependency>& fds) {
	std::vector<FunctionalDependency> minimized;

	for (auto& fd : fds) {
		auto lhs = fd.lhs;
		auto rhs = fd.rhs;
		std::vector<std::string> redurant_attributes;

		if (lhs.size() > 1) {
			for (auto& attribute : lhs) {
				std::set<std::string> temp_lhs = lhs;
				temp_lhs.erase(attribute);

				auto closure = Closure(temp_lhs, fds);
				if (std::includes(closure.begin(), closure.end(), rhs.begin(), rhs.end())) {
					redurant_attributes.push_back(attribute);
				}
			}
			for (auto& attribute : redurant_attributes) {
				lhs.erase(attribute);
			}
		}
		minimized.push_back({ lhs, rhs });
	}

	return minimized;
}

std::vector<FunctionalDependency> MinimalCover(const std::vector<FunctionalDependency>& fds) {
	auto normalized = NormalizeDependencies(fds);
	std::cout << "After normalization: \n";
	PrintDependencies(normalized);
	auto without_redundancy = RemoveRedurantDependencies(normalized);
	std::cout << "After removing: \n";
	PrintDependencies(without_redundancy);
	auto minimized = MinimizeLHS(without_redundancy);
	std::cout << "After minimization: \n";
	PrintDependencies(minimized);

	return minimized;
}

int main() {
	std::vector<FunctionalDependency> fds = {
		{{"A1"}, {"A2", "A3", "A4", "A5", "A6", "A7", "A8"}},
		{{"A9"}, {"A10", "A11", "A12"}},
		{{"A14"}, {"A21", "A22", "A23"}},
		{{"A13"}, {"A9", "A14", "A15"}},
		{{"A16"}, {"A13", "A17", "A18"}},
		{{"A16", "A1"}, {"A19", "A20"}},
		{{"A17"}, {"A24", "A25", "A26"}}
	};
	auto res = MinimalCover(fds);
}
