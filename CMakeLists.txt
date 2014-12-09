cmake_minimum_required(VERSION 2.6)
project(libRacv)

file(
	GLOB_RECURSE
	source_files
	src/*
)

file(
	GLOB_RECURSE
	header_files
	include/libRacv/*
)

list(
	REMOVE_ITEM
	header_files
	"include/libRacv/opencv/*"
)

include_directories(include)

add_library(
	Racv
	STATIC
	${source_files}
	${header_files}
)
