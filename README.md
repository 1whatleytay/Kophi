# Kophi - A Java Class Loader

## Features
 - A comfy, Object-Oriented C++ Library
 - Cross Platform with CMake
 - Aims to stay up to date with new Java versions

## Building and Linking

### CMake Project
First, add the project as a CMake subdirectory.
```cmake
add_subdirectory(path/to/Kophi)
```

Next, link the "Kophi" library to your project:
```cmake
target_link_library(MyProject Kophi)
```

And you're done!

### Building Kophi
If you aren't using CMake and you need to generate a binary, CMake makes your life easy.
Ensure you have CMake installed, you can download it [here](https://cmake.org/download).

In your command prompt, you need to make a build directory and have CMake generate a project.
If you open up a terminal in Kophi's root directory, it can be done with these commands:
```bash
mkdir build
cd build
cmake ..
```

If you're on Windows, you can usually follow this up by opening Kophi.sln and building the project.
If you're on macOS or Linux, give `make .` a shot.

## Using Kophi
Start using Kophi by including the "Kophi/JavaClass.h" header file.
```cpp
#include <Kophi/JavaClass.h>

using namespace Kophi;
```

### Loading Classes
Once you've included the header, loading a class can be done by constructing a `JavaClass` object.
```cpp
// Load from a class file on disk...
JavaClass myClass = JavaClass("path/to/File.class");

// Load from a vector filled with the bytes from a file.
std::vector<unsigned char> data = { ... };
JavaClass myClass = JavaClass(data);
```

### Getting Class Information
Once you've made your class, you can grab its name by accessing the "Constant Pool".
You can use some of the `get` methods to navigate the information.
```cpp
// JavaClass myClass;

// JavaConstantClass represents a class used by this Class file.
JavaConstantClass *thisClass = myClass.getThisClass();
JavaConstantClass *superClass = myClass.getSuperClass();
// Fetch its name by using the getName() method.
std::string thisClassName = thisClass->getName();
```

You can also get its access through the `accessFlags` property.
The `describeAccessFlags` returns a description of all the flags, like you would see in Java.
```cpp
// JavaClass myClass;

std::string access = describeAccessFlags(myClass.accessFlags);
```

### Class Properties
You can also get information on class methods, fields and more through `JavaClass`'s properties.

The `pool` property stores plenty of information on constants the class uses.
These can be method references, integers that don't change, or names.
```cpp
// JavaClass myClass;

for (JavaConstant constant : myClass.pool) {
    // JavaConstant is a pointer, so use -> to get properties.
    JavaConstantTag tag = constant->tag;
    if (tag == JavaConstantTag::Integer) {
        std::cout << "Integer found!" << std::endl;
    }
}
```
See "Casting" to access subvalues for constants.

The `methods` and `fields` properties store information about the class' methods and fields.
Methods take use of `JavaAttribute` objects to store code and other information about the method.
Both methods and fields have names, types and accessFlags that you can describe.
Go wild!
```cpp
// JavaClass myClass;

for (JavaMethod method : myClass.methods) {
    std::string access = describeAccessFlags(method.accessFlags);
    std::string methodName = method.getName();
    // Java uses a weird format for their types, see spec.
    std::string methodType = method.getDescriptor();
    
    ...
}
```

Finally, you can see the `attributes` property elsewhere as well, where it stores information about its owner.
You can get what the attribute is used for with the `name` property, which you can use to cast the `JavaAttribute` into something more useful.
```cpp
// JavaClass myClass;

for (JavaAttribute attribute : myClass.attributes) {
    std::cout << "Attribute Named: " << attribute.name << std::endl;
}
```

### Casting
Casting lets you turn `JavaConstant`s and `JavaAttribute`s into something useful.
For example, if you have a `JavaConstant` with a tag of `Integer`, you can get the value of the integer it represents with a cast.
Or if you have a `JavaAttribute` with a name of `"Code"`, you can get the java code it contains with a cast.

One obvious way you can do this is with C-style or C++ Casts, like the following.
```cpp
// For attributes
JavaAttribute myAttribute = ...;

if (myAttribute->name == "LineNumberTable") {
    // Casting starts here! Note the type is "JavaAttribute" with "LineNumberTable" appended to the end.
    JavaAttributeLineNumberTable *table = (JavaAttributeLineNumberTable *)myAttribute.get();

    // Now you can access the hidden "lineNumbers" property!
    int firstLineNumber = table->lineNumbers[0].lineNumber;
    int firstPC = table->lineNumbers[0].startPC;
}

// For constants
JavaConstant myConstant = ...;

if (myConstant->tag == JavaConstantTag::Integer) {
    // Casting starts here again! Note the type is "JavaConstant" with "Integer" appended to the end.
    JavaConstantInteger *integer = dynamic_cast<JavaConstantIntger *>(constant.get());
    
    // Now you can access the "value" parameter.
    int value = integer->value;
}
```

A better way is to use the static `cast` method on the type you want to cast to.
This will check your `tag` or `name` to make sure it matches the cast you are trying to cast to, and throws an exception if not.
It also saves you a few characters to type.
```cpp
JavaConstant myConstant = ...;

try {
    // Casting here! Try/catch is optional incase you're sure.
    JavaConstantClass *myClass = JavaConstantClass::cast(myConstant);
    
    std::string className = myClass->getName();
} catch (ConstantCastException e) { }
```

## Reporting Issues and Contributing
If something explodes while you're using it, feel free to [file an issue](https://github.com/1whatleytay/Kophi/issues) on github.
If you know C++ and are willing to help, any pull requests you can make will be greatly appreciated.

### Style
We use `lowerCamelCase` for all variables, fields, properties, methods and functions.
We use `UpperCamelCase` for all classes and namespaces.
Try to stay consistent with the rest of the code and you should be good.
