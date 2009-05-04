#-----------------------------------------------------------------
# kmp
# ===
#
# Top-level CMake file for kmp
#
# Author:			Evrard, Moulard
# Copyright:		Evrard, Moulard 2009
#-----------------------------------------------------------------

cmake_minimum_required(VERSION 2.6)

project(kmp_lib)
project(kmp_tests)

# --- Project variables ------------------------------------------

# --- Modules ----------------------------------------------------

include(FindBoost)

# --- Subdirectories ---------------------------------------------

add_subdirectory(include)
add_subdirectory(tests)