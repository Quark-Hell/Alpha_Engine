SET (Tests_Source "${CMAKE_CURRENT_LIST_DIR}")
include_directories("${Tests_Source}")

SET(Core_Tests_Dir "${Tests_Dir}/CoreTests")

add_executable(CoreTests 
	"${Tests_Dir}/TestMain.cpp"
	"${Core_Tests_Dir}/TestCore.cpp"
	"${Core_Tests_Dir}/Modules.cpp")

add_dependencies(CoreTests ALPHA_Engine)

if(WIN32)
	include(CMakeCloneDependencies.txt)

	if(MSVC)
		target_link_libraries(CoreTests
				PRIVATE ALPHA_Engine
				PRIVATE GTest::gtest_main
				PRIVATE "${Examples_Build_Dir}/external/assimp.lib"
		)

		copy_file("${Examples_Build_Dir}/external/assimp-vc143-mt.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assimp-vc143-mt.dll")
	elseif(MINGW)
		target_link_libraries(CoreTests
				PRIVATE ALPHA_Engine
				PRIVATE GTest::gtest_main
				PRIVATE "${Examples_Build_Dir}/external/assimp.dll.a"
		)

		copy_file("${Examples_Build_Dir}/external/libassimp-5.dll" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libassimp-5.dll")
	endif()

else()
	find_package(assimp REQUIRED)

	target_link_libraries(CoreTests
			PUBLIC ALPHA_Engine
			PRIVATE GTest::gtest_main
			PRIVATE assimp
	)
endif()


include(GoogleTest)
gtest_discover_tests(CoreTests)