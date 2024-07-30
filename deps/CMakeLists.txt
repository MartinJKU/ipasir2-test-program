add_subdirectory(ipasir2-cpp)

if (USE_MINISAT)
    add_subdirectory(ipasir2_solver_minisat)
elseif (USE_LINGELING)
    add_subdirectory(ipasir2_solver_lingeling)
elseif (USE_CRYPTOMINISAT)
    add_subdirectory(ipasir2_solver_cryptominisat)
endif()