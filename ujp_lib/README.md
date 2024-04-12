# UJP_LIB

### Description

This README contains information about how to use this library and what 
is the purpouse of each component.

All of the components are under the `ujp` namespace.

### Index
-   [ujp_json](#item_one)
-   [ujp_scanner](#item_two)
-   [ujp_exception](#item_three)

<a id="item_one"></a>
## ujp_json

### enum types
An enum type of data that determines the type of an attribute in a json.

### enum parserStates
An enum type of data that determines the different results returned by the parser method.

### JSON()
Constructor of class `ujp::JSON` that creates an empty `ujp::JSON` object.

### JSON(std::istream &)
JSON's class constructor that creates a `ujp::JSON` object and initializes it depending on the `std::istream` content.

### void flush()
Empties a `ujp::JSON` object.

### std::string to_string()
Returns a `std::string` representing the JSON object.

### double getNumber(std::string) const
Returns the `double` value associated to the key passed as an argument. If the key does not exist or has another value type the method
will throw a `Key_Error` exception.

### std::string getString(std::string) const
Returns the `std::string` value associated to the key passed as an argument. If the key does not exist or has another value type the method
will throw a `Key_Error` exception.

### JSON& getJSON(std::string)
Returns the `ujp::JSON` value associated to the key passed as an argument. If the key does not exist or has another value type the method
will throw a `Key_Error` exception.

### bool setNumber(std::string, double)
Modifys/Adds the `double` value to the key specified in the first argument, then it returns `true`. If the key already exists and corresponds to a different type
then the method will do nothing and returns `false`.

### bool setString(std::string, std::string)
Modifys/Adds the `std::string` value to the key specified in the first argument, then it returns `true`. If the key already exists and corresponds 
to a different type then the method will do nothing and returns `false`.

### bool setJSON(std::string, ujp::JSON&)
Modifys/Adds the `ujp::JSON` value to the key specified in the first argument, then it returns `true`. If the key already exists and corresponds to a different type
then the method will do nothing and returns `false`.

<a id="item_two"></a>
## ujp_scanner

### parserStates parse(JSON &json, std::istream &input)
Parses the `std::istream` given as an argument into the JSON object passed by reference.
Returns an enum `parserStates` that provides information about the result of the parsing method.

<a id="item_three"></a>
## ujp_exception

### Key_Error
`Key_Error` exception is thrown if the user attempts to access a key in a dictionary that either does not exist or has a different type.