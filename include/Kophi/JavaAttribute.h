#ifndef GEISHA_JAVAATTRIBUTE_H
#define GEISHA_JAVAATTRIBUTE_H

#include <Kophi/Utils.h>

#include <Kophi/JavaConstant.h>

namespace Kophi {
    class JavaClass;

    class JavaAttributeType {
    protected:
        static const unsigned headerSize = sizeof(uint16_t) + sizeof(uint32_t);

        JavaAttributeType(const JavaClass &parent, const Byte *data, unsigned &index);

    public:
        const JavaClass &parent;

        uint16_t nameIndex;
        uint32_t length;

        std::string name;
        virtual std::string toString() const = 0;

        static std::shared_ptr<JavaAttributeType> build(const JavaClass &parent,
                const Byte *data, unsigned &index);
        virtual ~JavaAttributeType() = default;
    };
    typedef std::shared_ptr<JavaAttributeType> JavaAttribute;

    class ExceptionEntry {
    public:
        uint16_t startPC;
        uint16_t endPC;
        uint16_t handlerPC;
        uint16_t catchType;

        explicit ExceptionEntry(const Byte *data);
    };

    class JavaAttributeCode : public JavaAttributeType {
    public:
        uint16_t maxStack;
        uint16_t maxLocals;
        uint32_t codeLength;
        std::vector<Byte> code;
        uint16_t exceptionEntryCount;
        std::vector<ExceptionEntry> exceptionEntries;
        uint16_t attributeCount;
        std::vector<JavaAttribute> attributes;

        std::string getDisassembly() const;

        std::string toString() const override;

        JavaAttributeCode(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaAttributeCode *cast(const JavaAttribute &attribute);
    };

    class JavaAttributeSourceFile : public JavaAttributeType {
    public:
        uint16_t sourceFileIndex = 0;

        std::string getSourceFileName() const;

        std::string toString() const override;

        JavaAttributeSourceFile(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaAttributeSourceFile *cast(const JavaAttribute &attribute);
    };

    class LineNumber {
    public:
        uint16_t startPC;
        uint16_t lineNumber;

        explicit LineNumber(const Byte *data);
    };

    class JavaAttributeLineNumberTable : public JavaAttributeType {
    public:
        uint16_t lineNumberCount;
        std::vector<LineNumber> lineNumbers;

        std::string toString() const override;

        JavaAttributeLineNumberTable(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaAttributeLineNumberTable *cast(const JavaAttribute &attribute);
    };

    class LocalVariable {
    public:
        uint16_t startPC;
        uint16_t length;
        uint16_t nameIndex;
        uint16_t descriptorIndex;
        uint16_t index;

        explicit LocalVariable(const Byte *data);
    };

    class JavaAttributeLocalVariableTable : public JavaAttributeType {
    public:
        uint16_t localVariableCount;
        std::vector<LocalVariable> localVariables;

        std::string toString() const override;

        JavaAttributeLocalVariableTable(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaAttributeLocalVariableTable *cast(const JavaAttribute &attribute);
    };

    class JavaAttributeConstantValue : public JavaAttributeType {
    public:
        PoolIndex constantIndex;

        JavaConstant getConstant() const;

        std::string toString() const override;

        JavaAttributeConstantValue(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaAttributeConstantValue *cast(const JavaAttribute &attribute);
    };

    class JavaAttributeStackMapTable : public JavaAttributeType {
    public:
        uint16_t entryCount;
        std::vector<Byte> entries; // TODO: Needs to have its own Class/Cast system.

        std::string toString() const override;

        JavaAttributeStackMapTable(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaAttributeStackMapTable *cast(const JavaAttribute &attribute);
    };

    class JavaAttributeExceptions : public JavaAttributeType {
    public:
        uint16_t exceptionCount;
        std::vector<PoolIndex> exceptions;

        JavaConstantClass *getException(int index);

        std::string toString() const override;

        JavaAttributeExceptions(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaAttributeExceptions *cast(const JavaAttribute &attribute);
    };

    class InnerClass {
    public:
        uint16_t innerClassIndex;
        uint16_t outerClassIndex;
        uint16_t innerNameIndex;
        AccessFlags innerClassAccessFlags;

        explicit InnerClass(const Byte *data);
    };

    class JavaAttributeInnerClasses : public JavaAttributeType {
    public:
        uint16_t classCount;
        std::vector<InnerClass> classes;

        std::string toString() const override;

        JavaAttributeInnerClasses(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaAttributeInnerClasses *cast(const JavaAttribute &attribute);
    };

    // TODO: Add more attributes.
}

#endif //GEISHA_JAVAATTRIBUTE_H
