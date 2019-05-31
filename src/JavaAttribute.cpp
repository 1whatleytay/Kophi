#include <Kophi/Private.h>
#include <Kophi/JavaClass.h>
#include <Kophi/JavaAttribute.h>
#include <Kophi/JavaInstruction.h>

namespace Kophi {
    // Java Source File Attribute
    std::string JavaAttributeSourceFile::getSourceFileName() const {
        return JavaConstantUtf8::cast(parent.pool[sourceFileIndex])->text;
    }

    std::string JavaAttributeSourceFile::toString() const {
        return "Source File (" + getSourceFileName() + ")";
    }

    JavaAttributeSourceFile::JavaAttributeSourceFile(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaAttributeType(parent, data, index) {
        sourceFileIndex = Private::swapEndian(*(uint16_t *)&data[headerSize]);
    }

    JavaAttributeSourceFile* JavaAttributeSourceFile::cast(const JavaAttribute &attribute) {
        if (attribute->name != "SourceFile")
            throw AttributeCastException(attribute->name, "SourceFile");
        return (JavaAttributeSourceFile *)attribute.get();
    }

    // Java Code Attribute
    ExceptionEntry::ExceptionEntry(const Byte *data) {
        startPC = Private::swapEndian(*(uint16_t *)&data[0]);
        endPC = Private::swapEndian(*(uint16_t *)&data[2]);
        handlerPC = Private::swapEndian(*(uint16_t *)&data[4]);
        catchType = Private::swapEndian(*(uint16_t *)&data[6]);
    }

    std::string JavaAttributeCode::getDisassembly() const {
        return createDisasm(parent, &code[0], codeLength);
    }

    std::string JavaAttributeCode::toString() const {
        return "Code (stack: " + std::to_string(maxStack) +
            ", locals: " + std::to_string(maxLocals) + "):\n" + getDisassembly();
    }

    JavaAttributeCode::JavaAttributeCode(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaAttributeType(parent, data, index) {
        unsigned m = headerSize;
        maxStack = Private::swapEndian(*(uint16_t *)&data[m]);
        m += sizeof(uint16_t);
        maxLocals = Private::swapEndian(*(uint16_t *)&data[m]);
        m += sizeof(uint16_t);

        codeLength = Private::swapEndian(*(uint32_t *)&data[m]);
        m += sizeof(uint32_t);
        code = std::vector<Byte>(codeLength);
        std::memcpy(&code[0], &data[m], codeLength);
        m += codeLength;

        exceptionEntryCount = Private::swapEndian(*(uint16_t *)&data[m]);
        m += sizeof(uint16_t);
        exceptionEntries.reserve(exceptionEntryCount);
        for (int a = 0; a < exceptionEntryCount; a++) {
            exceptionEntries.emplace_back(&data[m]);
            m += sizeof(ExceptionEntry);
        }

        attributeCount = Private::swapEndian(*(uint16_t *)&data[m]);
        m += sizeof(uint16_t);
        for (int a = 0; a < attributeCount; a++) {
            attributes.push_back(JavaAttributeType::build(parent, &data[m], m));
        }
    }

    JavaAttributeCode* JavaAttributeCode::cast(const JavaAttribute &attribute) {
        if (attribute->name != "Code")
            throw AttributeCastException(attribute->name, "Code");
        return (JavaAttributeCode *)attribute.get();
    }

    // Java Line Number Table Attribute
    LineNumber::LineNumber(const Byte *data) {
        startPC = Private::swapEndian(*(uint16_t *)&data[0]);
        lineNumber = Private::swapEndian(*(uint16_t *)&data[2]);
    }

    std::string JavaAttributeLineNumberTable::toString() const {
        return "Attribute Line Number Table (" + std::to_string(lineNumberCount) + ")";
    }

    JavaAttributeLineNumberTable::JavaAttributeLineNumberTable(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaAttributeType(parent, data, index) {
        unsigned m = headerSize;

        lineNumberCount = Private::swapEndian(*(uint16_t *)&data[m]); m += sizeof(uint16_t);
        lineNumbers.reserve(lineNumberCount);
        for (int a = 0; a < lineNumberCount; a++) {
            lineNumbers.emplace_back(&data[m]); m += sizeof(LineNumber);
        }
    }

    JavaAttributeLineNumberTable* JavaAttributeLineNumberTable::cast(const JavaAttribute &attribute) {
        if (attribute->name != "LineNumberTable")
            throw AttributeCastException(attribute->name, "LineNumberTable");
        return (JavaAttributeLineNumberTable *)attribute.get();
    }

    // Java Local Variable Table Attribute
    LocalVariable::LocalVariable(const Byte *data) {
        startPC = Private::swapEndian(*(uint16_t *)&data[0]);
        length = Private::swapEndian(*(uint16_t *)&data[2]);
        nameIndex = Private::swapEndian(*(uint16_t *)&data[4]);
        descriptorIndex = Private::swapEndian(*(uint16_t *)&data[6]);
        index = Private::swapEndian(*(uint16_t *)&data[8]);
    }

    std::string JavaAttributeLocalVariableTable::toString() const {
        return "Local Variable Table (" + std::to_string(localVariableCount) + ")";
    }

    JavaAttributeLocalVariableTable::JavaAttributeLocalVariableTable(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaAttributeType(parent, data, index) {
        unsigned m = headerSize;

        localVariableCount = Private::swapEndian(*(uint16_t *)&data[m]); m += sizeof(uint16_t);
        localVariables.reserve(localVariableCount);
        for (int a = 0; a < localVariableCount; a++) {
            localVariables.emplace_back(&data[m]); m += sizeof(LocalVariable);
        }
    }

    JavaAttributeLocalVariableTable* JavaAttributeLocalVariableTable::cast(const JavaAttribute &attribute) {
        if (attribute->name != "LocalVariableTable")
            throw AttributeCastException(attribute->name, "LocalVariableTable");
        return (JavaAttributeLocalVariableTable *)attribute.get();
    }

    // Java Constant Value Attribute
    JavaConstant JavaAttributeConstantValue::getConstant() const {
        return parent.pool[constantIndex];
    }

    std::string JavaAttributeConstantValue::toString() const {
        std::string value;
        JavaConstant constant = getConstant();
        switch (constant->tag) {
            case JavaConstantTag::Integer:
                value = std::to_string(JavaConstantInteger::cast(constant)->value); break;
            case JavaConstantTag::Float:
                value = std::to_string(JavaConstantFloat::cast(constant)->value); break;
            case JavaConstantTag::Long:
                value = std::to_string(JavaConstantLong::cast(constant)->value); break;
            case JavaConstantTag::Double:
                value = std::to_string(JavaConstantDouble::cast(constant)->value); break;
            case JavaConstantTag::String:
                value = JavaConstantString::cast(constant)->getText(); break;
            default: break;
        }

        return "Constant Value " + value;
    }

    JavaAttributeConstantValue::JavaAttributeConstantValue(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaAttributeType(parent, data, index) {
        constantIndex = Private::swapEndian(*(uint16_t *)&data[headerSize]);
    }

    JavaAttributeConstantValue *JavaAttributeConstantValue::cast(const JavaAttribute &attribute) {
        if (attribute->name != "ConstantValue")
            throw AttributeCastException(attribute->name, "ConstantValue");
        return (JavaAttributeConstantValue *)attribute.get();
    }

    // Java Stack Map Table Attribute
    std::string JavaAttributeStackMapTable::toString() const {
        return "Stack Map Table (" + std::to_string(entryCount) + ")";
    }

    JavaAttributeStackMapTable::JavaAttributeStackMapTable(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaAttributeType(parent, data, index) {
        entryCount = Private::swapEndian(*(uint16_t *)&data[headerSize]);
        entries = std::vector<Byte>(length - sizeof(uint16_t));
        std::memcpy(&entries[0], &data[headerSize + 2], length - sizeof(uint16_t));
    }

    JavaAttributeStackMapTable* JavaAttributeStackMapTable::cast(const Kophi::JavaAttribute &attribute) {
        if (attribute->name != "StackMapTable")
            throw AttributeCastException(attribute->name, "StackMapTable");
        return (JavaAttributeStackMapTable *)attribute.get();
    }

    // Java Exceptions Attribute
    JavaConstantClass *JavaAttributeExceptions::getException(int index) {
        return JavaConstantClass::cast(parent.pool[exceptions[index]]);
    }

    std::string JavaAttributeExceptions::toString() const {
        return "Exceptions (" + std::to_string(exceptionCount) + ")";
    }

    JavaAttributeExceptions::JavaAttributeExceptions(const Kophi::JavaClass &parent,
            const Kophi::Byte *data, unsigned &index) : JavaAttributeType(parent, data, index) {
        exceptionCount = Private::swapEndian(*(uint16_t *)&data[headerSize]);
        exceptions = std::vector<PoolIndex>(exceptionCount);
        std::memcpy(&exceptions[0], &data[headerSize + 2], exceptionCount * sizeof(uint16_t));
    }

    JavaAttributeExceptions* JavaAttributeExceptions::cast(const Kophi::JavaAttribute &attribute) {
        if (attribute->name != "Exceptions")
            throw AttributeCastException(attribute->name, "Exceptions");
        return (JavaAttributeExceptions *)attribute.get();
    }

    // Java Inner Classes Attribute
    InnerClass::InnerClass(const Kophi::Byte *data) {
        innerClassIndex = Private::swapEndian(*(uint16_t *)&data[0]);
        outerClassIndex = Private::swapEndian(*(uint16_t *)&data[2]);
        innerNameIndex = Private::swapEndian(*(uint16_t *)&data[4]);
        innerClassAccessFlags = (AccessFlags)Private::swapEndian(*(uint16_t *)&data[6]);
    }

    std::string JavaAttributeInnerClasses::toString() const {
        return "Inner Classes (" + std::to_string(classCount) + ")";
    }

    JavaAttributeInnerClasses::JavaAttributeInnerClasses(const Kophi::JavaClass &parent,
            const Kophi::Byte *data, unsigned &index) : JavaAttributeType(parent, data, index) {
        unsigned m = 0;

        classCount = Private::swapEndian(*(uint16_t *)&data[headerSize]); m += sizeof(uint16_t);
        classes.reserve(classCount);
        for (int a = 0; a < classCount; a++) {
            classes.emplace_back(&data[m]);
            m += sizeof(InnerClass);
        }

        index += m;
    }

    JavaAttributeInnerClasses* JavaAttributeInnerClasses::cast(const Kophi::JavaAttribute &attribute) {
        if (attribute->name == "InnerClasses")
            throw AttributeCastException(attribute->name, "InnerClasses");
        return (JavaAttributeInnerClasses *)attribute.get();
    }

    JavaAttributeType::JavaAttributeType(const JavaClass &parent, const Byte *data, unsigned int &index)
            : parent(parent) {
        nameIndex = Private::swapEndian(*(uint16_t *)&data[0]);
        length = Private::swapEndian(*(uint32_t *)&data[2]);
        name = JavaConstantUtf8::cast(parent.pool[nameIndex])->text;

        index += 6 + length;
    }

    std::shared_ptr<JavaAttributeType> JavaAttributeType::build(const JavaClass &parent,
            const Byte *data, unsigned &index) {
        uint16_t nameIndex = Private::swapEndian(*(uint16_t *)&data[0]);
        std::string name = JavaConstantUtf8::cast(parent.pool[nameIndex])->text;

        if (name == "Code")
            return JavaAttribute(new JavaAttributeCode(parent, data, index));
        else if (name == "SourceFile")
            return JavaAttribute(new JavaAttributeSourceFile(parent, data, index));
        else if (name == "LineNumberTable")
            return JavaAttribute(new JavaAttributeLineNumberTable(parent, data, index));
        else if (name == "LocalVariableTable")
            return JavaAttribute(new JavaAttributeLocalVariableTable(parent, data, index));
        else if (name == "ConstantValue")
            return JavaAttribute(new JavaAttributeConstantValue(parent, data, index));
        else if (name == "StackMapTable")
            return JavaAttribute(new JavaAttributeStackMapTable(parent, data, index));
        else if (name == "Exceptions")
            return JavaAttribute(new JavaAttributeExceptions(parent, data, index));
        else if (name == "InnerClasses")
            return JavaAttribute(new JavaAttributeInnerClasses(parent, data, index));

        // Probably shouldn't throw here, just warn.
        throw UnknownAttribute(name);
    }
}
