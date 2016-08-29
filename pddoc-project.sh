#!/bin/bash
# coding: utf-8

name=""
title=""
version=""
mversion=`pddoc --version`
sourced=""

function newProject() {
	mkdir "$name"
	mkdir "$name/htdocs"
	mkdir "$name/htdocs/html"
	mkdir "$name/htdocs/html/styles"
	mkdir "$name/htdocs/html/js"
	mkdir "$name/htdocs/html/resources"
	touch "$name/project.pro"
	touch "$name/config.pdc"
	touch "$name/Makefile"
	pddoc --css > "$name/htdocs/html/styles/general_style.css"
	pddoc --head1 > "$name/htdocs/classes/general_header_h.html"
	pddoc --head2 > "$name/htdocs/classes/general_header_b.html"
	pddoc --foot > "$name/htdocs/classes/general_footer.html"
	echo "dirname: $name" >> "$name/project.pro"
	echo "name: $title" >> "$name/project.pro"
	echo "version: $version" >> "$name/project.pro"
	echo "pddoc-v: $mversion" >> "$name/project.pro"
	echo "sourcedir: $sourced" >> "$name/project.pro"
	echo "" >> "$name/config.pdc"
	echo "" >> "$name/Makefile"
}

function build() {
	make
}

function addFile() {
	
}
