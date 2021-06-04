#include <thread>
#include <vector>
#include <iostream>
#include <mutex>
#include <memory>


static std::mutex iomut { };


struct scope {
    scope(const char *name) : s(name) {
        std::lock_guard<std::mutex> lock(iomut);
        std::cerr << "enter: " << s << std::endl;
    }

    ~scope() {
        std::lock_guard<std::mutex> lock(iomut);
        std::cerr << "leave: " << s << std::endl;
    }

    std::string s;
};



int main() {
    scope("main");

    {
        scope("main::values before");

        std::vector<int> vec;

        scope("main::values after");

        {
            scope("main::thread before");
            std::thread th([&vec]() {
                std::vector<int> tmp;

                tmp.emplace_back(10);
                tmp.emplace_back(20);
                tmp.emplace_back(30);
                tmp.emplace_back(40);

                vec = tmp;
            });

            scope("main::thread after");

#ifdef EXAMPLE_WITH_JOIN
            th.join();
#endif

#ifdef EXAMPLE_WITH_DETACH
            th.detach();
#endif
        }
    }

    return 0;
}
