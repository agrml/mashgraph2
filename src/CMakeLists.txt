set(SOURCE_FILES
        task2.cpp
        Usable.cpp
        ../include
)


add_executable(project2 ${SOURCE_FILES})
target_link_libraries(project2
        easybmp
        argvparser
        linear
        ${GLOG_LIBRARIES}
)
set_target_properties(project2 PROPERTIES COMPILE_DEFINITIONS DEBUG)
