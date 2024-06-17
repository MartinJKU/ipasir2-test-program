#include <ipasir2cpp.h>
#include <iostream>
#include <memory>


namespace ip2 = ipasir2;
using namespace std::literals;

int main() {
    try {
        ip2::ipasir2 api = ip2::create_api();
        //ip2::ipasir2 api = ip2::create_api("./solver.so");

        std::unique_ptr<ip2::solver> solver = api.create_solver();
        solver->add(1, 2, 3); // Add clause (1 OR 2 OR 3)
        solver->add(-1);      // Add clause (-1)
        solver->add(-2);      // Add clause (-2)

        auto result = solver->solve();
        std::cout << "Result: " << result.map("sat"sv, "unsat"sv, "unknown"sv) << std::endl;
    }
    catch (const ip2::ipasir2_error& error) {
        std::cerr << "Could not solve the formula: " << error.what() << std::endl;
    }
    return 0;
}
