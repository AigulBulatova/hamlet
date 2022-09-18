# Hamlet

Program for sorting text files

## Description

The program sorts the lines of a text file in lexicographic order (alphabetically), ignoring spaces and punctuation. Can also sort strings by comparing them from the end.

## Installation

You must have installed ```g++``` and ```make```
* Download files or clone this repository:
  * ```git clone https://github.com/AigulBulatova/hamlet.git```
* Build the program:
  * ```cd hamlet/```
  * ```make```

## Usage

This program has 2 types of sorting - in lexicographic order and comparing strings from the end. Results of this sortings will be printed to files ```txt/direct_sorted.txt``` and ```reverse_sorted.txt```. 

### Configs

If you want to use standart C function qsort(), go to the file [configs.h](https://github.com/AigulBulatova/hamlet/blob/master/configs.h) and comment ```#define USE_MY_SORT``` with ```//``` at the beginning. Otherwise, the comparison function written by me will be used.

Defined LOGS in the file [configs.h](https://github.com/AigulBulatova/hamlet/blob/master/configs.h) will create log file and print additional information into it. If you want to turn it off, comment ```#define LOGS``` with ```//```.


