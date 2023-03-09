# Code generation from generics
Math members are defined in generics like c++ template.  
Generic definitions are converted by `sed`, `make` and std-C macro definitions
in `SLC`.  
Common naming conventions are listed below.

Table 1. Common naming conventions  
Identifier | Category | Description
-----------|----------|-----------------
`__NUMT`     | Macro | Base number type
`__IDXT`   | Macro | Base indexer-size type
`_PP_NT_IT`   | Identifier postfix | It is replaced with `_<name1><name2>`, <br/>where `name1` is a string representing a base number type, and <br/>`name2` is a base indexer-size type.
<br/>