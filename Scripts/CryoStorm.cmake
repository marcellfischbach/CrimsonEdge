


function(CS_MOC trgt)

	set(MOC_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/__cmake__build__moc__")

	message("MOC: ${CMAKE_CURRENT_SOURCE_DIR}")
	message("MOC: ${CMAKE_SOURCE_DIR}")

	set (EXEC_PATH "")
	if (CryoStorm_BINARY_DIR)
		set(EXEC_PATH "${CryoStorm_BINARY_DIR}/bin/")
	endif()
	
	#string(REGEX REPLACE ".*/" "" ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

	string(MAKE_C_IDENTIFIER ${trgt} TARGET_IDENTIFIER)


	set(TARGET_NAME "${trgt}-MOC")
	add_custom_target(${TARGET_NAME}
                            COMMAND ${EXEC_PATH}csMOC  --path ${MOC_DIRECTORY} --sourcepath ${CMAKE_CURRENT_SOURCE_DIR}
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			BYPRODUCTS "${MOC_DIRECTORY}/.csCache"
	)
	if (CryoStorm_BINARY_DIR)
		# this is an in-engine build
		add_dependencies(${TARGET_NAME} csMOC)
	endif()
	add_dependencies(${trgt} ${TARGET_NAME})


    target_include_directories(${trgt} BEFORE PUBLIC ${MOC_DIRECTORY})

	
endfunction(CS_MOC)
