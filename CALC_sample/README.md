Renesas RX65N/RX72N Envision Kit Calculator Sample
=========

<img src="../docs/calc_sample.jpg" width="50%">

[Japanese](READMEja.md)
   
## Overview

 - Generic Calculator Applications
 - GUI operation when used with the RX65N/RX72N Envision Kit
 - Operable from the console in microcontrollers that do not have graphics
 - Multiply floating point number using the gmp mpfr library
 - 250 digits of internal processing (could be more, but sufficient for the time being)

## Project list

 - main.cpp
 - calc_gui.hpp
 - calc_symbol.hpp
 - calc_func.hpp
 - calc_cmd.hpp
 - RX64M/Makefile
 - RX71M/Makefile
 - RX66T/Makefile
 - RX65N/Makefile (for LCD)
 - RX72N/Makefile (for LCD)

### Use Library

 - libgmp.a
 - libmpfr.a

### Main support classes

 - common/basic_arith.hpp
 - common/mpfr.hpp
   
## Build Method

 - Go to the target directory
 - Make.
 - Write the calc_sample.mot file to the microcontroller.

## Corresponding function

|function name|function|
|---|-------|
|sin|sin(x)|
|cos|cos(x)|
|tan|tan(x)|
|asin|asin(x)|
|acos|acos(x)|
|atan|atan(x)|
|log|log10(x)|
|ln|log(x)|
|x^y|X ^ Y|
|x^-1|X ^ -1|
|x^2|X ^ 2|
|sqrt|sqrt(x)|
|exp|exp10(x)|
|π|pi|
|Deg|Angle Method, 360|
|Rad|Angle Method, 2pi|
|Grad|Angle Method, 400|

## Future Plans

- Wifi-enabled, allowing you to view and type in the browser
- A dedicated programming language, allowing you to perform your own operations
- Graphing
- Flexible and unrestricted hexadecimal display and conversion, etc.
- Arithmetic Processing

-----
   
License
----
   
MIT open source license   

libgmp:  GNU LGPL v3 and GNU GPL v2   
libfrmp: GNU LGPL v3   
