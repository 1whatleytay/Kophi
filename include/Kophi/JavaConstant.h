#ifndef KOPHI_JAVACONSTANT_H
#define KOPHI_JAVACONSTANT_H

#include <Kophi/Utils.h>

namespace Kophi {
    class JavaClass;

    class JavaConstantType {
    protected:
        static const unsigned headerSize = sizeof(JavaConstantTag);

        JavaConstantType(const JavaClass &parent, const Byte *data, unsigned &index);

    public:
        const JavaClass &parent;

        JavaConstantTag tag = JavaConstantTag::Unknown;

        virtual std::string toString() const = 0;
        virtual ~JavaConstantType() = default;

        static std::shared_ptr<JavaConstantType> build(const JavaClass &parent,
                const Byte *data, unsigned &index, bool &isDouble);
    };
    typedef std::shared_ptr<JavaConstantType> JavaConstant;

    class JavaConstantInteger : public JavaConstantType {
    public:
        const static unsigned size = sizeof(JavaInt);

        JavaInt value;

        std::string toString() const override;

        JavaConstantInteger(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaConstantInteger *cast(const JavaConstant &constant);
    };

    class JavaConstantFloat : public JavaConstantType {
    public:
        const static unsigned size = sizeof(JavaFloat);

        JavaFloat value;

        std::string toString() const override;

        JavaConstantFloat(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaConstantFloat *cast(const JavaConstant &constant);
    };

    class JavaConstantLong : public JavaConstantType {
    public:
        const static unsigned size = sizeof(JavaLong);

        JavaLong value;

        std::string toString() const override;

        JavaConstantLong(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaConstantLong *cast(const JavaConstant &constant);
    };

    class JavaConstantDouble : public JavaConstantType {
    public:
        const static unsigned size = sizeof(JavaDouble);

        JavaDouble value;

        std::string toString() const override;

        JavaConstantDouble(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaConstantDouble *cast(const JavaConstant &constant);
    };

    class JavaConstantNameAndType : public JavaConstantType {
    public:
        const static unsigned size = sizeof(uint16_t) * 2;

        uint16_t nameIndex;
        uint16_t descriptorIndex;

        std::string getName() const;
        std::string getDescriptor() const;

        std::string toString() const override;

        JavaConstantNameAndType(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaConstantNameAndType *cast(const JavaConstant &constant);
    };

    class JavaConstantString : public JavaConstantType {
    public:
        const static unsigned size = sizeof(uint16_t);

        uint16_t stringIndex;

        std::string getText() const;

        std::string toString() const override;

        JavaConstantString(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaConstantString *cast(const JavaConstant &constant);
    };

    class JavaConstantClass : public JavaConstantType {
    public:
        const static unsigned size = sizeof(uint16_t);

        uint16_t nameIndex;

        std::string getName() const;

        std::string toString() const override;

        JavaConstantClass(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaConstantClass *cast(const JavaConstant &constant);
    };

    class JavaConstantUtf8 : public JavaConstantType {
    public:
        const static unsigned size = 0;

        uint16_t length;
        std::string text;

        std::string toString() const override;

        JavaConstantUtf8(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaConstantUtf8 *cast(const JavaConstant &constant);
    };

    class JavaConstantRef : public JavaConstantType {
    public:
        const static unsigned size = sizeof(uint16_t) * 2;

        uint16_t classIndex;
        uint16_t nameAndTypeIndex;

        const JavaConstantClass *getClass() const;
        const JavaConstantNameAndType *getNameAndType() const;

        std::string toString() const override;

        JavaConstantRef(const JavaClass &parent, const Byte *data, unsigned &index);

        static JavaConstantRef *cast(const JavaConstant &constant);
    };
    typedef JavaConstantRef JavaConstantFieldRef;
    typedef JavaConstantRef JavaConstantMethodRef;
    typedef JavaConstantRef JavaConstantInterfaceMethodRef;

    class JavaConstantMethodHandle : public JavaConstantType {
    public:
        const static unsigned size = sizeof(uint8_t) + sizeof(PoolIndex);

        ReferenceKind referenceKind;
        PoolIndex referenceIndex;

        JavaConstantRef *getReference() const;

        std::string toString() const override;

        JavaConstantMethodHandle(const JavaClass &parent, const Byte *data, unsigned &index);

        JavaConstantMethodHandle *cast(const JavaConstant &constant);
    };

    class JavaConstantMethodType : public JavaConstantType {
    public:
        const static unsigned size = sizeof(PoolIndex);

        PoolIndex descriptorIndex;

        std::string getDescriptor() const;

        std::string toString() const override;

        JavaConstantMethodType(const JavaClass &parent, const Byte *data, unsigned &index);

        JavaConstantMethodType *cast(const JavaConstant &constant);
    };

    class JavaConstantDynamic : public JavaConstantType {
    public:
        const static unsigned size = sizeof(PoolIndex) * 2;

        PoolIndex bootstrapMethodIndex;
        PoolIndex nameAndTypeIndex;

        JavaConstantNameAndType *getNameAndType() const;

        std::string toString() const override;

        JavaConstantDynamic(const JavaClass &parent, const Byte *data, unsigned &index);

        JavaConstantDynamic *cast(const JavaConstant &constant);
    };
    typedef JavaConstantDynamic JavaConstantInvokeDynamic;

    class JavaConstantModule : public JavaConstantType {
    public:
        const static unsigned size = sizeof(PoolIndex);

        PoolIndex nameIndex;

        std::string getName() const;

        std::string toString() const override;

        JavaConstantModule(const JavaClass &parent, const Byte *data, unsigned &index);

        JavaConstantModule *cast(const JavaConstant &constant);
    };
    typedef JavaConstantModule JavaConstantPackage;
}

#endif //KOPHI_JAVACONSTANT_H
