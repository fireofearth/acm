#include <bits/stdc++.h>
using namespace std;

/*
in:
4
1
buy 10 shares at 90
1
sell 10 share at 110
2
buy 10 shares at 90
sell 10 share at 110
2
buy 10 shares at 110
sell 10 shares at 90

out:
- 90 -
110 - -
- 90 -
110 90 -
- 110 -
- - 90

in:
2
2
sell 10 share at 110
buy 10 shares at 90
2
sell 10 shares at 90
buy 10 shares at 110

out:
110 - -
110 90 -
90 - -
- - 90

in:
1
4
buy 10 shares at 100
sell 1 shares at 120
sell 20 shares at 110
buy 30 shares at 110

out:
- 100 -
120 100 -
110 100 -
120 110 110

https://open.kattis.com/problems/stockprices
g++ -O2 -std=gnu++23 stockprices.cpp -o k
./k < tests/stockprices-1.in
*/
typedef std::pair<int,int> pii;

struct CompBuyer {
    // buyers ranked by largest price (bid)
    bool operator()(pii a, pii b) {
        return a.first < b.first;
    }
};

struct CompSeller {
    // sellers ranked by smallest price (ask)
    bool operator()(pii a, pii b) {
        return a.first > b.first;
    }
};

void body (std::vector<std::tuple<int,int,int>>& results) {
    // run one test case
    int n_ops;
    std::cin >> n_ops;

    std::vector<std::tuple<std::string, int, int>> ops;
    ops.reserve(n_ops);
    std::string op_type;
    int op_n_shares, op_price;
    std::string nop;
    for (int i = 0; i < n_ops; i++) {
        // get operation
        std::cin >> op_type >> op_n_shares >> nop >> nop >> op_price;
        ops.push_back({op_type, op_n_shares, op_price});
    }

    int stock_price = -1;
    std::priority_queue<pii, std::vector<pii>, CompBuyer> buyers;
    std::priority_queue<pii, std::vector<pii>, CompSeller> sellers;
    for (int i = 0; i < n_ops; i++) {
        std::tie(op_type, op_n_shares, op_price) = ops[i];

        // add to priority queue
        if (op_type == "buy") {
            // is buyer
            buyers.push({op_price, op_n_shares});
        } else {
            // is seller
            sellers.push({op_price, op_n_shares});
        }

        // printf("operation %s %d %d \n", op_type.c_str(), op_n_shares, op_price);

        // do transactions until no more can be done
        while (true) {
            if (buyers.empty() || sellers.empty()) {
                // no transactions if no buyers or sellers
                break;
            }

            auto [bid_price, n_buy] = buyers.top();
            auto [ask_price, n_sell] = sellers.top();

            // printf("transaction? bid: %d, ask: %d \n", bid_price, ask_price);

            // transactions only happen if the ask price is lower or equal to bid price
            if (bid_price < ask_price) {
                break;
            }

            // a transaction can happen, so update bid and ask
            buyers.pop();
            sellers.pop();
            int n_buy_remain = std::max(0, n_buy - n_sell);
            int n_sell_remain = std::max(0, n_sell - n_buy);
            if (n_buy_remain > 0) {
                buyers.push({bid_price, n_buy_remain});
            }
            if (n_sell_remain > 0) {
                sellers.push({ask_price, n_sell_remain});
            }

            stock_price = ask_price;
        }

        // get ask, bid and stock prices
        int ask_price = -1;
        int bid_price = -1;
        if (!sellers.empty()) {
            std::tie(ask_price, op_price) = sellers.top();
        }
        if (!buyers.empty()) {
            std::tie(bid_price, op_price) = buyers.top();
        }
        results.push_back({ask_price, bid_price, stock_price});
    }
}

int main () {
    int N;
    std::cin >> N;
    std::vector<std::tuple<int,int,int>> results;
    results.reserve(200 * 1000);
    for (int i = 0; i < N; i++) {
        body(results);
    }
    for (auto [ask_price, bid_price, stock_price] : results) {
        if (ask_price < 0) {
            std::cout << "- ";
        } else {
            std::cout << ask_price << " ";
        }

        if (bid_price < 0) {
            std::cout << "- ";
        } else {
            std::cout << bid_price << " ";
        }

        if (stock_price < 0) {
            std::cout << "-\n";
        } else {
            std::cout << stock_price << "\n";
        }
    }
    return 0;
}

