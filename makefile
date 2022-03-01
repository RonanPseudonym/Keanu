# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -std=c++14
 
main.o: main.cpp parse.h
	$(CC) $(CFLAGS) main.cpp