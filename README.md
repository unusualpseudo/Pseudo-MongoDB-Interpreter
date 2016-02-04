# Pseudo-MongoDB-Interpreter
- A small MongoDB Interpreter created with C .

- The interpreter don't parse all the grammair given in the file : MongbBNF .

- It's can specialy execute the CRUD  queries with a multiple key : value .

- The BNF is taken from :
<a href="https://github.com/mongodb-js/mongodb-language-model/blob/master/docs/bnf.md">BNF Source </a>
, i mad some changes to that BNF in order to make Non-recursive Predective parser .

- The  use the libson libary  <a href="https://github.com/mongodb/libbson">Libbson</a>

- For each data base created a new directory will be created in the db directory , and for each one of this directories will containt files matches with the collections exit in that data base .
