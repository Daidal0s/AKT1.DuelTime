add_executable(coreTest test.cpp)
configure_target(coreTest)
target_link_libraries(coreTest 
    PRIVATE Core
)
configure_test(coreTest)
