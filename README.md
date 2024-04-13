# UncomplicatedJsonParser (UJP)

## About

This is a C++ library intended to parse a string/file into a C++ object and vice versa. 
It is not currently completed and it does not allow the parse of json files that contains arrays or booleans, however all other kind of json files are supported.

## Getting started

To use it on your proyect you need to include the `ujp_lib/` directory and link the library with the executable where you need to use it.

To do so, in the `ujp_lib/` directory, a CMakeLists.txt file is stored to define the library and allow other CMakeLists.txt files to call it and in order to use the library.

To get used to the library, I have included a file `main.cpp` where there are explained some of the methods and uses of the library. In order to
successfully run it, you need to compile it using the CMakeLists.txt file.

I recommed doing the following command to execute it:

    ./main < json_files/file1.json

The main executable should be executed at the same level as the `main.cpp` file, so it can find the path to `json_files/file1.json`.

## Examples

Inside the `examples/` folder you can find more uses and scenarios to help you understanding and learning how to use UJP.

## License

The code is released under the MIT license. See the LICENSE file for more details. If you use this code, please include a link to this repository and mention the author/s.