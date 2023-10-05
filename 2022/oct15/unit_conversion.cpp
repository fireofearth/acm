#include <bits/stdc++.h>
using namespace std;

/// 1 m = 3.28084 ft
/// 1 ft = 12 in
/// 1 hr = 60 min
/// 1 min = 60 s
///
/// ("m", "ft", 3.28084)

// to, from, unit value
typedef std::tuple<std::string, std::string, double> Definition;
typedef std::vector<Definition> DefinitionList;
// to, from, value to convert
typedef std::tuple<std::string, std::string, double> Query;
typedef std::vector<Query> QueryList;

typedef std::vector<std::string> UnitList;

std::unordered_map<std::string, UnitList> gdef;
std::unordered_map<std::string, std::unordered_map<std::string, double>> convs;
std::unordered_set<std::string> visited;

template <template<typename ...> class Container,  typename T>
std::string toString(const Container<T>& v) {
    bool beg = true;
    std::stringstream ss;
    for (const T& t : v) {
        if (!beg) ss << ", ";
        beg = false;
        ss << t;
    }
    return ss.str();
}

std::vector<double> conversion(const DefinitionList& defs, const QueryList& queries) {
    gdef.clear();
    convs.clear();
    double value;
    std::string to, from, start, end, curr;
    std::optional<std::string> prev;

    for (const auto& def : defs) {
        from = get<0>(def);
        to = get<1>(def);
        value = get<2>(def);
        gdef[from].push_back(to);
        gdef[to].push_back(from);
        convs[from][to] = value;
        convs[to][from] = 1.0 / value;
    }
    
    std::vector<double> out;
    out.reserve(queries.size());
    for (const auto& query : queries) {
        visited.clear();
        std::stack<std::string> d;
        std::deque<std::string> path;
        start = get<0>(query);
        end = get<1>(query);
        // std::cout << start << " " << end << std::endl;
        d.push(start);
        prev = std::nullopt;
        while(!d.empty()) {
            curr = d.top();
            // std::cout << "    prev " << prev << " curr " << curr << " path " << toString(path) << std::endl;

            if (!gdef.count(curr)) {
                // only happens if curr == start;
                d.pop();
                continue;
            }

            if (visited.count(curr)) {
                // go to next node
                d.pop();
                if (!d.empty() && prev.has_value() && d.top() == prev.value()) {
                    // we are back tracking
                    path.pop_back();
                    if (!path.empty()) {
                        prev = path.back();
                    } else {
                        prev = std::nullopt;
                    }
                }
                continue;
            }

            path.push_back(curr);
            if (curr == end) {
                break;
            }

            visited.insert(curr);
            for (const std::string& unit : gdef[curr]) {
                d.push(unit);
            }
            prev = curr;
        }
        
        if (path.empty()) {
            out.push_back(std::numeric_limits<double>::infinity());
        } else if (path.back() != end) {
            out.push_back(std::numeric_limits<double>::infinity());
        } else {
            value = get<2>(query);
            // std::cout << start << " " << end << " " << value << std::endl;
            for (int i = 0; i < path.size() - 1; i++) {
                // std::cout << "    convs[" << path[i] << "][" << path[i+1] << "] " << convs[path[i]][path[i + 1]] << std::endl;
                value *= convs[path[i]][path[i + 1]];
            }
            out.push_back(value);
        }
    }

    return out;
}

void __trial_2() {
    const DefinitionList defs = {
        {"a", "b", 2},
        {"b", "c", 1.5},
        {"a", "c", 3},
        {"c", "d", 5},
        {"d", "e", 1.4},
        {"c", "f", 11},
        {"c", "g", 13},
        {"f", "g", 1.18181818181818}
    };
    const QueryList queries = {
        {"a", "d", 1.0}, // 15
        {"b", "f", 1.0}  // 16.5
    };
    const std::vector<double> out = conversion(defs, queries);
    std::string to, from;
    double vfrom, vto;
    std::cout << "solutions:" << std::endl;
    for (int i = 0; i < queries.size(); i++) {
        std::tie(from, to, vfrom) = queries[i];
        vto = out[i];
        std::cout << from << " " << to << " " << vfrom << " " << vto << std::endl;
    }
}

/*
g++ -std=c++17 unit_conversion.cpp -o k
*/
void __trial_1() {
    const DefinitionList defs = {
        {"a", "b", 2.0},
        {"b", "c", 3.0},
        {"c", "d", 5.0}
    };
    const QueryList queries = {
        {"a", "c", 1.1}, // 6.6
        {"a", "a", 1.1}, // 1.1
        {"a", "d", 1.1}, // 33.0
        {"a", "e", 1.1}, // infty
        {"e", "a", 1.1}, // infty
        {"c", "a", 1.0}, // 0.183333
        {"d", "a", 1.0}  // 0.036666
    };
    const std::vector<double> out = conversion(defs, queries);
    std::string to, from;
    double vfrom, vto;
    std::cout << "solutions:" << std::endl;
    for (int i = 0; i < queries.size(); i++) {
        std::tie(from, to, vfrom) = queries[i];
        vto = out[i];
        std::cout << from << " " << to << " " << vfrom << " " << vto << std::endl;
    }
}

int main() {
    __trial_1();
    __trial_2();
    return 0;
}

