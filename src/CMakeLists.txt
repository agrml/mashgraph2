set(SOURCE_FILES
        task2.cpp
        )
add_executable(project2 ${SOURCE_FILES})
target_link_libraries(project2
        easybmp
        argvparser
        linear
        ${GLOG_LIBRARIES}
        )

