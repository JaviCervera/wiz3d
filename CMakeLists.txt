#Minimum version
cmake_minimum_required(VERSION 2.6)

#Define project
project(tau)

#Define file groups
file(GLOB TAU_FILES "src/*.c" "lib/lua/*.c" "lib/base64/base64.c")

#Add header and lib directories
include_directories(${INCLUDE_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR}/lib/lua ${CMAKE_CURRENT_SOURCE_DIR}/lib)
link_directories(${LINK_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR}/lib/sdl2/_CMAKE)

#Add executable targets
add_executable(tau ${TAU_FILES})

#Add platform specific options
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	add_definitions(-DWIN32)
	if (MSVC)
		message("Platform is Windows (MSVC)")
		#add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	else (MSVC)
		message("Platform is Windows (MinGW)")
		#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-std=c90 -pedantic-errors -Wall")
		set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++98 -fno-exceptions -fno-rtti")
		set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-s -static -mwindows")
	endif (MSVC)
	target_link_libraries(tau SDL2 opengl32 winmm imm32 version ${TARGET_LINK_LIBRARIES})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	message("Platform is macOS")
	#add_definitions(-std=c++11 -stdlib=libc++)
	#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-std=c90 -pedantic-errors -Wall")
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++98 -fno-exceptions -fno-rtti")
	target_link_libraries(tau SDL2 iconv "-framework AppKit" "-framework AudioToolbox" "-framework Carbon" "-framework CoreAudio" "-framework CoreVideo" "-framework ForceFeedback" "-framework IOKit" "-framework OpenGL" ${TARGET_LINK_LIBRARIES})
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	message("Platform is Linux")
	#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-std=c90 -pedantic-errors -Wall")
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fno-exceptions -fno-rtti")
	#set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-s -static")
	target_link_libraries(tau SDL2 asound dl GL m pthread pulse X11 Xcursor Xext Xi Xinerama Xrandr Xxf86vm ${TARGET_LINK_LIBRARIES})
else (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message("Unrecognized platform " ${CMAKE_SYSTEM_NAME})
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
