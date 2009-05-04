#-----------------------------------------------------------------
# Boost.Kamoulox
# ==============
#
# The library
#
# Author:			Evrard, Moulard
# Copyright:		Evrard, Moulard 2009
#-----------------------------------------------------------------

include(SourcesLib.cmake)

add_executable(Kamoutests ${KMPTESTS_SRC})

include_directories(${kmp_tests_SOURCE_DIR}/include)

install(TARGETS Kamoutests
	RUNTIME DESTINATION bin
)