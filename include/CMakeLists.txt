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

add_library(kmp SHARED ${KMP_HEADERS} empty.cc)

install(FILES ${KMP_HEADERS}
	DESTINATION ${CMAKE_INSTALL_PREFIX}/include/kmp
	PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE WORLD_READ WORLD_WRITE
)