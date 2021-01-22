
FIND_PATH(redishead testhelp.h PATHS ./include/)
IF(redishead)
INCLUDE_DIRECTORIES(${redishead})
ENDIF(redishead)

link_libraries(pthread)

add_executable(sdstest src/sds.c src/zmalloc.c)

set_target_properties(sdstest PROPERTIES COMPILE_DEFINITIONS "SDS_TEST_MAIN")
