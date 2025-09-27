option(Build_Tests "Build tests" ON)

#Examples
set(Tests_Dir "${ALPHA_Engine}/Tests")
message(${Tests_Dir})

if(Tests_Dir)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0 
    )

    enable_testing()

    set(INSTALL_GTEST OFF CACHE BOOL "Disable installation of googletest" FORCE)
    FetchContent_MakeAvailable(googletest)

    if(EXISTS ${Tests_Dir})
        include("${Tests_Dir}/CoreTests/CMakeLists.txt")
        include("${Tests_Dir}/ModulesTests/CMakeLists.txt")
    endif()
endif()