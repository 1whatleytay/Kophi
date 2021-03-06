#include <Kophi/Private.h>
#include <Kophi/JavaClass.h>

#include <sstream>
#include <iostream>

namespace Kophi {
    std::string describeClass(const JavaClass &java) {
        std::stringstream stream;
        stream << "Java Class File " << std::to_string(java.majorVersion) << "."
            << std::to_string(java.minorVersion) << "\n";
        stream << "This Class: " << describeAccessFlags(java.accessFlags) << " " << java.getThisClass()->getName()
            << ", Super Class: " << java.getSuperClass()->getName() << "\n";
        stream << "Access Flags: " << describeAccessFlags(java.accessFlags) << "\n";

        stream << "Constants (" << std::to_string(java.constantCount) << "):" << "\n";
        for (int a = 0; a < java.pool.size(); a++) {
            const JavaConstant info = java.pool[a];
            if (!info) continue;
            stream << "\t{" << std::to_string(a) << "} ";
            switch (info->tag) {
                case JavaConstantTag::Utf8:
                    stream << "Utf8 [" << std::to_string((JavaConstantUtf8::cast(info)->length))
                                << "]: " << JavaConstantUtf8::cast(info)->text;
                    break;
                case JavaConstantTag::Class:
                    stream << "Class " << JavaConstantClass::cast(info)->getName();
                    break;
                case JavaConstantTag::String:
                    stream << "String [" << std::to_string(JavaConstantString::cast(info)->stringIndex)
                               << "]: " << JavaConstantString::cast(info)->getText();
                    break;
                case JavaConstantTag::FieldRef:
                    stream << "Field Ref: " << JavaConstantRef::cast(info)->getNameAndType()->getDescriptor()
                               << " " << JavaConstantRef::cast(info)->getClass()->getName()
                               << "#" << JavaConstantRef::cast(info)->getNameAndType()->getName();
                    break;
                case JavaConstantTag::MethodRef:
                    stream << "Method Ref: " << JavaConstantRef::cast(info)->getNameAndType()->getDescriptor()
                               << " " << JavaConstantRef::cast(info)->getClass()->getName()
                               << "#" << JavaConstantRef::cast(info)->getNameAndType()->getName();
                    break;
                case JavaConstantTag::NameAndType:
                    stream << "Name And Type: " << JavaConstantNameAndType::cast(info)->getDescriptor()
                               << " " << JavaConstantNameAndType::cast(info)->getName();
                    break;
                default:
                    stream << "Unknown Constant";
                    break;
            }
            stream << "\n";
        }

        stream << "Interfaces (" << std::to_string(java.interfaceCount) << ")\n";
        if (java.interfaceCount > 0) {
            stream << "\t[ ";
            for (uint16_t interface : java.interfaces) {
                stream << interface << ", ";
            }
            stream << "]";
        }

        stream << "Fields (" << java.fieldCount << ")" << "\n";
        for (const JavaField &field : java.fields) {
            stream << "\t" << describeAccessFlags(field->accessFlags)
                       << " " << field->getDescriptor() << " " << field->getName() << "\n";
            for (const JavaAttribute &attr : field->attributes) {
                stream << "\t\t" << attr->toString() << "\n";
            }
        }

        stream << "Methods (" << std::to_string(java.methodCount) << ")\n";
        for (const JavaMethod &method : java.methods) {
            stream << "\t" << describeAccessFlags(method->accessFlags)
                       << " " << method->getDescriptor() << " " << method->getName() << "\n";
            for (const JavaAttribute &attr : method->attributes) {
                stream << "\t\t" << attr->toString() << "\n";
            }
        }

        stream << "Attributes (" << std::to_string(java.attributeCount) << ")\n";
        for (const JavaAttribute &attr : java.attributes) {
            stream << "\t\t" << attr->toString() << "\n";
        }

        return stream.str();
    }

    unsigned JavaPool::size() const {
        return pool.size();
    }

    JavaConstant JavaPool::operator[](unsigned index) const {
        return pool[index];
    }

    JavaPool::JavaPool(const JavaClass &java, unsigned size, const Kophi::Byte *data, unsigned &index) {
        unsigned m = 0;

        pool.reserve(size);
        pool.emplace_back(); // Add empty object.
        for (int a = 0; a < size - 1; a++) {
            bool isDouble;
            pool.push_back(JavaConstantType::build(java, &data[m], m, isDouble));
            if (isDouble) pool.emplace_back();
        }

        index += m;
    }

    JavaPool::JavaPool(const Kophi::JavaPool &old) {
        pool = std::vector<JavaConstant>(old.pool);
    }

    const JavaConstantClass *JavaClass::getThisClass() const { return JavaConstantClass::cast(pool[thisClass]); }
    const JavaConstantClass *JavaClass::getSuperClass() const { return JavaConstantClass::cast(pool[superClass]); }

    const JavaAttribute JavaClass::searchAttributes(const std::string& name) const {
        for (const JavaAttribute &attribute : attributes) {
            if (attribute->name == name) {
                return attribute;
            }
        }

        return JavaAttribute(nullptr);
    }

    const std::vector<JavaConstant> JavaClass::searchConstants(JavaConstantTag tag) const {
        std::vector<JavaConstant> constants;

        for (int a = 0; a < pool.size(); a++) {
            if (pool[a]->tag == tag) {
                constants.push_back(pool[a]);
            }
        }

        return constants;
    }

    const std::vector<std::string> JavaClass::getDependancies() const {
        std::vector<JavaConstant> constants = searchConstants(JavaConstantTag::Class);
        std::vector<std::string> names;
        names.reserve(constants.size());

        for (const JavaConstant &constant : constants) {
            names.push_back(JavaConstantClass::cast(constant)->getName());
        }

        return names;
    }

    const std::string JavaClass::getSourceFileName() const {
        return JavaAttributeSourceFile::cast(searchAttributes("SourceFile"))->getSourceFileName();
    }

    JavaClass::JavaClass(const std::vector<Byte> &data) {
        unsigned index = 0;
        magic = Private::swapEndian(*(uint32_t *) &data[index]);
        index += sizeof(uint32_t);
        if (magic != JAVA_CLASS_MAGIC) throw std::exception(); // throw InvalidClassFile();
        minorVersion = Private::swapEndian(*(uint16_t *) &data[index]);
        index += sizeof(uint16_t);
        majorVersion = Private::swapEndian(*(uint16_t *) &data[index]);
        index += sizeof(uint16_t);

        constantCount = Private::swapEndian(*(uint16_t *) &data[index]);
        index += sizeof(uint16_t);
        pool = JavaPool(*this, constantCount, &data[index], index);

        accessFlags = (AccessFlags) Private::swapEndian(*(uint16_t *) &data[index]);
        index += sizeof(uint16_t);
        thisClass = Private::swapEndian(*(uint16_t *) &data[index]);
        index += sizeof(uint16_t);
        superClass = Private::swapEndian(*(uint16_t *) &data[index]);
        index += sizeof(uint16_t);

        interfaceCount = Private::swapEndian(*(uint16_t *) &data[index]);
        index += sizeof(uint16_t);
        interfaces.reserve(interfaceCount);
        for (int a = 0; a < interfaceCount; a++) {
            interfaces.push_back(Private::swapEndian(*(uint16_t *) &data[index]));
            index += sizeof(uint16_t);
        }

        fieldCount = Private::swapEndian(*(uint16_t *) &data[index]);
        index += sizeof(uint16_t);
        fields.reserve(fieldCount);
        for (int a = 0; a < fieldCount; a++) {
            fields.emplace_back(new JavaPropertyType(*this, &data[index], index));
        }

        methodCount = Private::swapEndian(*(uint16_t *) &data[index]);
        index += sizeof(uint16_t);
        methods.reserve(methodCount);
        for (int a = 0; a < methodCount; a++) {
            methods.emplace_back(new JavaPropertyType(*this, &data[index], index));
        }

        attributeCount = Private::swapEndian(*(uint16_t *) &data[index]);
        index += sizeof(uint16_t);
        attributes.reserve(attributeCount);
        for (int a = 0; a < attributeCount; a++) {
            attributes.push_back(JavaAttributeType::build(*this, &data[index], index));
        }
    }

    JavaClass::JavaClass(const std::string &path) : JavaClass(Private::fromFileGetBinary(path)) { }

    JavaClass::JavaClass(const Kophi::JavaClass &java) {
        magic = java.magic;
        majorVersion = java.majorVersion;
        minorVersion = java.minorVersion;
        accessFlags = java.accessFlags;
        thisClass = java.thisClass;
        superClass = java.superClass;
        constantCount = java.constantCount;
        interfaceCount = java.interfaceCount;
        fieldCount = java.fieldCount;
        methodCount = java.methodCount;
        attributeCount = java.attributeCount;
        pool = JavaPool(java.pool);
        interfaces = std::vector<uint16_t>(java.interfaces);
        fields = std::vector<JavaField>(java.fields);
        methods = std::vector<JavaMethod>(java.methods);
        attributes = std::vector<JavaAttribute>(java.attributes);
    }
}
