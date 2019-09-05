In C++ we have a **get pointer** and a **put pointer** for getting (i.e. reading) data from a file and putting(i.e. writing) data on the file respectively.

seekg() is used to move the get pointer to a desired location. `fin.seekg(10,ios::beg);`


tellg() is used to know where the get pointer is in a file. `int posn = fin.tellg();`

seekp() is used to move the put pointer to a desired location. `fout.seekp(10,ios::beg);`  

tellp() is used to know where the put pointer is in a file.  `int posn=fout.tellp();`

The reference points are: ios::beg, ios::end, ios::cur

p.s. A stream is a sequence of characters. So **those positions and offsets are in the unit of character**

p.s. `f.seekg(pos) ` is equivalent to `f.seekg(offset, f.beg)` or `f.seekg(offset, std::ios::beg)`

p.s. `int pos = f.tellg(); xxx; f.seekg(pos);` will return to the original position.

--------------

When any stream object reaches the end of stream, must clear its state before doing any other operations.

```
while(std::getline(f, ss)) ++number_of_lines;
f.clear();
f.seekg(pos);
```
