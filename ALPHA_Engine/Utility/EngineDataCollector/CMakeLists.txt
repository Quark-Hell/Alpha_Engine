option(EngineDataCollector "Build Engine data collector. That collect all info about name's classes, derived from Component" ON)

if(EngineDataCollector)
	set(EngineDataCollector_Dir "${ALPHA_Engine}/Utility/EngineDataCollector")
	set(Output_Dir "${CMAKE_BINARY_DIR}/Meta")

	message(${EngineDataCollector_Dir})
	
	add_executable(EngineDataCollector 
		"${EngineDataCollector_Dir}/Collector.cpp"
		"${EngineDataCollector_Dir}/Parser.cpp"
	)

	file(MAKE_DIRECTORY ${Output_Dir})

	add_custom_command(
		OUTPUT ${CMAKE_BINARY_DIR}/components_list.txt
		COMMAND EngineDataCollector ${Output_Dir}/Components_List.txt ${SCAN_DIRS}
		DEPENDS EngineDataCollector
		COMMENT "Scanning all components before building engine..."
	)
	
	add_custom_target(ScanComponents ALL
		DEPENDS ${CMAKE_BINARY_DIR}/components_list.txt
	)

	add_dependencies(ALPHA_Engine ScanComponents)
endif()