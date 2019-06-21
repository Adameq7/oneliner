# Oneliner

A programming language based on movie quotes and one-liners, with programs fitting into a single line. 

## Overview

The main idea behind the language was to produce (code) one-liners composed of (movie) one-liners.
It is inspired by the ArnoldC language, and shares some of its syntax, due to the supreme quality of Arnold Schwarzenegger's one-liners.
The Oneliner interpreter is written in C.


## Quick Start

Acquire a copy of the repo and build the interpreter:

	git clone https://github.com/Adameq7/oneliner.git
	cd oneliner
	make
  
You can now either run it and input the programs directly, or use input redirection (shown with one of the included examples below):

	./oneliner

OR

	./oneliner < examples/fizzbuzz.oneliner

There is a `-t` option available which additionally prints out the structure of the program.


# Details of the language

## Structure

Oneliner programs have to start with `GO AHEAD, MAKE MY DAY` and end with `TERMINATED`, and a `main` function must be present; the `main` function is executed when the program is run.


## Functions

Functions have between 0 - 20 arguments and can either return the value of a specified variable or be void (in which case they return 0).
Function declaration structure:

	ALLOW ME TO BREAK THE ICE `function name` `arg1` `arg2` ... `argx` LET'S ROCK `function body` I'LL BE BACK `return variable` COURT'S ADJOURNED

	[Example]
	ALLOW ME TO BREAK THE ICE multiplicate x y LET'S ROCK SWALLOW THIS x KNOCK KNOCK x y I'LL BE BACK x COURT'S ADJOURNED

The only way to call a funtion is by assigning the return value of the call to a variable. Since void functions have to be called this way too, a `dummy_return` global variable is available for this purpose.


## Variables

All variables are of type double (64-bit floating point).
Variables have to be declared prior to being used:

	HERE IS MY INVITATION `var`

	[Example]
	HERE IS MY INVITATION x

Variables can be assigned value in four ways (fifth way is described under the `Memory` section):

Assign value of var2 to var1:

	SWALLOW THIS `var1` `var2`

	[Example]
	SWALLOW THIS x y

Assign given value to var1:

	SWALLOW THIS `var1` `number`

	[Example]
	SWALLOW THIS x 3

Assign the result of an operation (arg1 operator arg2) to var1 (all but one operators are binary, `not` takes only one argument):

	SWALLOW THIS `var1` `operator` `arg1 = (var2 | number)` `arg2 = (var3 | number)`

	[Example]
	SWALLOW THIS x KNOCK KNOCK y 5

Assign the return value of a calling function <func> with given values of arguments:

	SWALLOW THIS `var1` `func` `arg1 = (var2 | number)` `arg2 = (var3 | number)` ... `argx = (vary | number)`

	[Example]
	SWALLOW THIS x log 10 y


## Operators

These are the operators that may be used when computing a value to assign to a variable:
Arithmetic operators:

	Addition        GIVE YOU A LIFT?
	Subtraction     LET OFF SOME STEAM, BENNETT
	Multiplication  KNOCK KNOCK
	Division        HE HAD TO SPLIT
	Modulo          KEEP THE CHANGE, YA FILTHY ANIMAL

Logical operators:

	And             THIS TOWN AIN'T BIG ENOUGH FOR THE BOTH OF US
	Or              ONE OF US IS IN DEEP TROUBLE
	Not             IT'S NOT A TUMOR
	Equal           YOU ARE NOT YOU, YOU ARE ME
	Less            YOU'RE A FUCKING CHOIRBOY COMPARED TO ME


## Memory

A 100000-element array of doubles is provided as a substitute for memory, with elements indexed from 0 to 99999.
Read from memory at index (may be a variable or a number) into var1:

	COME GET SOME `index = (var2 | number)` `var1`

	[Example]
	COME GET SOME 3 x

Write value of var1 to memory at index (may be a variable or a number):

	STICK AROUND `index = (var2 | number)` `var1`

	[Example]
	STICK AROUND y x


## Conditional statements

An if statement is available (if the variable `condition` evaluates to zero, `body-false` is executed, otherwise `body-true` is executed):

	GRANT ME REVENGE `condition` `body-true` AND IF YOU DO NOT LISTEN `body-false` THEN TO HELL WITH YOU

	[Example]
	GRANT ME REVENGE cond TALK TO THE HAND "true" AND IF YOU DO NOT LISTEN TALK TO THE HAND "false" THEN TO HELL WITH YOU


## Loops

A while loop is available (the loop repeats as long as variable `condition` evaluates to non-zero):

	I HAVE COME HERE `condition` TO CHEW BUBBLEGUM AND KICK ASS `body` AND I'M ALL OUT OF BUBBLEGUM

	[Example]
	I HAVE COME HERE x TO CHEW BUBBLEGUM AND KICK ASS SWALLOW THIS x LET OFF SOME STEAM BENNETT x 1 AND I'M ALL OUT OF BUBBLEGUM


## Printing

It is possible to print strings (contained in double quotations), values of variables or numbers:

	TALK TO THE HAND `string | var | number`

	[Example]
	TALK TO THE HAND "this is a string"

To print a newline:

	TALK TO THE HAND `message` ENOUGH TALK 

	[Example]
	TALK TO THE HAND x ENOUGH TALK


# Examples

Two simple programs are provided below. Four additional examples are included in the examples/ folder.

## Simplest valid program that does nothing:

	GO AHEAD, MAKE MY DAY ALLOW ME TO BREAK THE ICE main LET'S ROCK I'LL BE BACK COURT'S ADJOURNED TERMINATED


## Hello World!

	GO AHEAD, MAKE MY DAY ALLOW ME TO BREAK THE ICE main LET'S ROCK TALK TO THE HAND "Hello World!" ENOUGH TALK I'LL BE BACK COURT'S ADJOURNED TERMINATED
