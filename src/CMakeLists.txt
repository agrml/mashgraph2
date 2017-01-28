set(SOURCE_FILES
        matrix.hpp
        task2.cpp
        Usable.cpp
)


add_executable(project2 ${SOURCE_FILES})
target_link_libraries(project2
        easybmp
        argvparser
        linear
        ${GLOG_LIBRARIES}
)
set_target_properties(project2 PROPERTIES COMPILE_DEFINITIONS DEBUG)


set(GOOGLE_TESTS_SOURCE_FILES
        ${SOURCE_FILES}
        GoogleTests.cpp
)

add_executable(GoogleTests ${GOOGLE_TESTS_SOURCE_FILES})

target_link_libraries(GoogleTests
        easybmp
        argvparser
        linear
        ${GLOG_LIBRARIES}
        ${GTEST_LIBRARIES}
        pthread
)

set_target_properties(GoogleTests PROPERTIES COMPILE_DEFINITIONS DEBUG)
