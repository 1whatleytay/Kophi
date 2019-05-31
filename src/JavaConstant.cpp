#include <Kophi/Private.h>
#include <Kophi/JavaClass.h>
#include <Kophi/JavaConstant.h>

namespace Kophi {
    std::string JavaConstantInteger::toString() const {
        return "Integer " + std::to_string(value);
    }

    JavaConstantInteger::JavaConstantInteger(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaConstantType(parent, data, index) {
        value = Private::swapEndian(*(JavaInt *)&data[headerSize]);
    }
    
    JavaConstantInteger *JavaConstantInteger::cast(const JavaConstant &constant) {
        if (constant->tag != JavaConstantTag::Integer)
            throw ConstantCastException(constant->tag, JavaConstantTag::Integer);
        return (JavaConstantInteger *)constant.get();
    }

    std::string JavaConstantFloat::toString() const {
        return "Float " + std::to_string(value);
    }
    
    JavaConstantFloat::JavaConstantFloat(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaConstantType(parent, data, index) {
        uint32_t bytes = Private::swapEndian(*(uint32_t *)&data[headerSize]);
        value = *(JavaFloat *)&bytes;
    }
    
    JavaConstantFloat *JavaConstantFloat::cast(const JavaConstant &constant) {
        if (constant->tag != JavaConstantTag::Float)
            throw ConstantCastException(constant->tag, JavaConstantTag::Float);
        return (JavaConstantFloat *)constant.get();
    }

    std::string JavaConstantLong::toString() const {
        return "Long " + std::to_string(value);
    }

    JavaConstantLong::JavaConstantLong(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaConstantType(parent, data, index) {
        value = Private::swapEndian(*(JavaLong *)&data[headerSize]);
    }

    JavaConstantLong *JavaConstantLong::cast(const JavaConstant &constant) {
        if (constant->tag != JavaConstantTag::Long)
            throw ConstantCastException(constant->tag, JavaConstantTag::Long);
        return (JavaConstantLong *)constant.get();
    }

    std::string JavaConstantDouble::toString() const {
        return "Double " + std::to_string(value);
    }

    JavaConstantDouble::JavaConstantDouble(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaConstantType(parent, data, index) {
        uint64_t bytes = Private::swapEndian(*(uint64_t *)&data[headerSize]);
        value = *(JavaDouble *)&bytes;
    }

    JavaConstantDouble* JavaConstantDouble::cast(const JavaConstant &constant) {
        if (constant->tag != JavaConstantTag::Double)
            throw ConstantCastException(constant->tag, JavaConstantTag::Double);
        return (JavaConstantDouble *)constant.get();
    }

    std::string JavaConstantNameAndType::getName() const {
        return ((JavaConstantUtf8 *)parent.pool[nameIndex].get())->text;
    }

    std::string JavaConstantNameAndType::getDescriptor() const {
        return ((JavaConstantUtf8 *)parent.pool[descriptorIndex].get())->text;
    }

    std::string JavaConstantNameAndType::toString() const {
        return "Name and Type " + getDescriptor() + getName();
    }

    JavaConstantNameAndType::JavaConstantNameAndType(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaConstantType(parent, data, index) {
        nameIndex = Private::swapEndian(*(uint16_t *)&data[headerSize]);
        descriptorIndex = Private::swapEndian(*(uint16_t *)&data[headerSize + 2]);
    }

    JavaConstantNameAndType* JavaConstantNameAndType::cast(const JavaConstant &constant) {
        if (constant->tag != JavaConstantTag::NameAndType)
            throw ConstantCastException(constant->tag, JavaConstantTag::NameAndType);
        return (JavaConstantNameAndType *)constant.get();
    }

    std::string JavaConstantString::getText() const {
        return ((JavaConstantUtf8 *)parent.pool[stringIndex].get())->text;
    }

    std::string JavaConstantString::toString() const {
        return "String " + getText();
    }

    JavaConstantString::JavaConstantString(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaConstantType(parent, data, index) {
        stringIndex = Private::swapEndian(*(uint16_t *)&data[headerSize]);
    }

    JavaConstantString* JavaConstantString::cast(const JavaConstant &constant) {
        if (constant->tag != JavaConstantTag::String)
            throw ConstantCastException(constant->tag, JavaConstantTag::String);
        return (JavaConstantString *)constant.get();
    }

    std::string JavaConstantClass::getName() const {
        return ((JavaConstantUtf8 *)parent.pool[nameIndex].get())->text;
    }

    std::string JavaConstantClass::toString() const {
        return "Class " + getName();
    }

    JavaConstantClass::JavaConstantClass(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaConstantType(parent, data, index) {
        nameIndex = Private::swapEndian(*(uint16_t *)&data[headerSize]);
    }

    JavaConstantClass* JavaConstantClass::cast(const JavaConstant &constant) {
        if (constant->tag != JavaConstantTag::Class)
            throw ConstantCastException(constant->tag, JavaConstantTag::Class);
        return (JavaConstantClass *)constant.get();
    }

    std::string JavaConstantUtf8::toString() const {
        return "Utf8 " + text;
    }

    JavaConstantUtf8::JavaConstantUtf8(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaConstantType(parent, data, index) {
        length = Private::swapEndian(*(uint16_t *)&data[headerSize]);
        text = std::string((char *)&data[headerSize + 2], length);
        index += sizeof(uint16_t) + length;
    }

    JavaConstantUtf8* JavaConstantUtf8::cast(const JavaConstant &constant) {
        if (constant->tag != JavaConstantTag::Utf8)
            throw ConstantCastException(constant->tag, JavaConstantTag::Utf8);
        return (JavaConstantUtf8 *)constant.get();
    }

    const JavaConstantClass *JavaConstantRef::getClass() const {
        return (JavaConstantClass *)parent.pool[classIndex].get();
    }

    const JavaConstantNameAndType *JavaConstantRef::getNameAndType() const {
        return (JavaConstantNameAndType *)parent.pool[nameAndTypeIndex].get();
    }

    std::string JavaConstantRef::toString() const {
        return "Reference " + getNameAndType()->getDescriptor() + " "
            + getClass()->getName() + "#" + getNameAndType()->getName();
    }

    JavaConstantRef::JavaConstantRef(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaConstantType(parent, data, index) {
        classIndex = Private::swapEndian(*(uint16_t *)&data[headerSize]);
        nameAndTypeIndex = Private::swapEndian(*(uint16_t *)&data[headerSize + 2]);
    }

    JavaConstantRef *JavaConstantRef::cast(const JavaConstant &constant) {
        if (constant->tag != JavaConstantTag::MethodRef
            && constant->tag != JavaConstantTag::FieldRef
            && constant->tag != JavaConstantTag::InterfaceMethodRef)
            throw ConstantCastException(constant->tag, JavaConstantTag::MethodRef);
        return (JavaConstantRef *)constant.get();
    }

    JavaConstantRef *JavaConstantMethodHandle::getReference() const {
        return JavaConstantRef::cast(parent.pool[referenceIndex]);
    }

    std::string JavaConstantMethodHandle::toString() const {
        return "Method Handle " + getReference()->getNameAndType()->getDescriptor() + " "
            + getReference()->getClass()->getName() + "#"
            + getReference()->getNameAndType()->getName();
    }

    JavaConstantMethodHandle::JavaConstantMethodHandle(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaConstantType(parent, data, index) {
        referenceKind = (ReferenceKind)data[headerSize];
        referenceIndex = Private::swapEndian(*(uint16_t *)&data[headerSize + 1]);
    }

    JavaConstantMethodHandle *JavaConstantMethodHandle::cast(const JavaConstant &constant) {
        if (constant->tag != JavaConstantTag::MethodHandle)
            throw ConstantCastException(constant->tag, JavaConstantTag::MethodHandle);
        return (JavaConstantMethodHandle *)constant.get();
    }

    std::string JavaConstantMethodType::getDescriptor() const {
        return JavaConstantUtf8::cast(parent.pool[descriptorIndex])->text;
    }

    std::string JavaConstantMethodType::toString() const {
        return "Method Type " + getDescriptor();
    }

    JavaConstantMethodType::JavaConstantMethodType(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaConstantType(parent, data, index) {
        descriptorIndex = Private::swapEndian(*(uint16_t *)&data[headerSize]);
    }

    JavaConstantMethodType *JavaConstantMethodType::cast(const JavaConstant &constant) {
        if (constant->tag != JavaConstantTag::MethodType)
            throw ConstantCastException(constant->tag, JavaConstantTag::MethodType);
        return (JavaConstantMethodType *)constant.get();
    }

    JavaConstantNameAndType *JavaConstantDynamic::getNameAndType() const {
        return JavaConstantNameAndType::cast(parent.pool[nameAndTypeIndex]);
    }

    std::string JavaConstantDynamic::toString() const {
        return "Dynamic " + getNameAndType()->getDescriptor() + " " + getNameAndType()->getName();
    }

    JavaConstantDynamic::JavaConstantDynamic(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaConstantType(parent, data, index) {
        bootstrapMethodIndex = Private::swapEndian(*(uint16_t *)&data[headerSize]);
        nameAndTypeIndex = Private::swapEndian(*(uint16_t *)&data[headerSize + 2]);
    }

    JavaConstantDynamic *JavaConstantDynamic::cast(const JavaConstant &constant) {
        if (constant->tag != JavaConstantTag::Dynamic
            && constant->tag != JavaConstantTag::InvokeDynamic)
            throw ConstantCastException(constant->tag, JavaConstantTag::Dynamic);
        return (JavaConstantDynamic *)constant.get();
    }

    std::string JavaConstantModule::toString() const {
        return "Module " + getName();
    }

    std::string JavaConstantModule::getName() const {
        return JavaConstantUtf8::cast(parent.pool[nameIndex])->text;
    }

    JavaConstantModule::JavaConstantModule(const JavaClass &parent,
            const Byte *data, unsigned &index) : JavaConstantType(parent, data, index) {
        nameIndex = Private::swapEndian(*(uint16_t *)&data[headerSize]);
    }

    JavaConstantModule *JavaConstantModule::cast(const JavaConstant &constant) {
        if (constant->tag != JavaConstantTag::Module
            && constant->tag != JavaConstantTag::Package)
            throw ConstantCastException(constant->tag, JavaConstantTag::Module);
        return (JavaConstantModule *)constant.get();
    }

    JavaConstantType::JavaConstantType(const JavaClass &parent,
            const Byte *data, unsigned &index) : parent(parent) {
        unsigned m = 0;

        tag = (JavaConstantTag) *(uint8_t *)&data[m]; m += sizeof(uint8_t);
        switch (tag) {
            case JavaConstantTag::Integer:
                m += JavaConstantInteger::size; break;
            case JavaConstantTag::Float:
                m += JavaConstantFloat::size; break;
            case JavaConstantTag::Long:
                m += JavaConstantLong::size; break;
            case JavaConstantTag::Double:
                m += JavaConstantDouble::size; break;
            case JavaConstantTag::NameAndType:
                m += JavaConstantNameAndType::size; break;
            case JavaConstantTag::String:
                m += JavaConstantString::size; break;
            case JavaConstantTag::Class:
                m += JavaConstantClass::size; break;
            case JavaConstantTag::Utf8: break;
            case JavaConstantTag::FieldRef:
            case JavaConstantTag::MethodRef:
            case JavaConstantTag::InterfaceMethodRef:
                m += JavaConstantRef::size; break;
            case JavaConstantTag::MethodHandle:
                m += JavaConstantMethodHandle::size; break;
            case JavaConstantTag::MethodType:
                m += JavaConstantMethodType::size; break;
            case JavaConstantTag::Dynamic:
            case JavaConstantTag::InvokeDynamic:
                m += JavaConstantDynamic::size; break;
            case JavaConstantTag::Module:
            case JavaConstantTag::Package:
                m += JavaConstantModule::size; break;
            default: assert(false);
        }

        index += m;
    }

    std::shared_ptr<JavaConstantType> JavaConstantType::build(const JavaClass &parent,
            const Byte *data, unsigned &index) {
        JavaConstantTag tag = (JavaConstantTag) *(uint8_t *)&data[0];
        switch (tag) {
            case JavaConstantTag::Integer:
                return JavaConstant(new JavaConstantInteger(parent, data, index));
            case JavaConstantTag::Float:
                return JavaConstant(new JavaConstantFloat(parent, data, index));
            case JavaConstantTag::Long:
                return JavaConstant(new JavaConstantLong(parent, data, index));
            case JavaConstantTag::Double:
                return JavaConstant(new JavaConstantDouble(parent, data, index));
            case JavaConstantTag::NameAndType:
                return JavaConstant(new JavaConstantNameAndType(parent, data, index));
            case JavaConstantTag::String:
                return JavaConstant(new JavaConstantString(parent, data, index));
            case JavaConstantTag::Class:
                return JavaConstant(new JavaConstantClass(parent, data, index));
            case JavaConstantTag::Utf8:
                return JavaConstant(new JavaConstantUtf8(parent, data, index));
            case JavaConstantTag::FieldRef:
            case JavaConstantTag::MethodRef:
            case JavaConstantTag::InterfaceMethodRef:
                return JavaConstant(new JavaConstantRef(parent, data, index));
            case JavaConstantTag::MethodHandle:
                return JavaConstant(new JavaConstantMethodHandle(parent, data, index));
            case JavaConstantTag::MethodType:
                return JavaConstant(new JavaConstantMethodType(parent, data, index));
            case JavaConstantTag::Dynamic:
            case JavaConstantTag::InvokeDynamic:
                return JavaConstant(new JavaConstantDynamic(parent, data, index));
            case JavaConstantTag::Module:
            case JavaConstantTag::Package:
                return JavaConstant(new JavaConstantModule(parent, data, index));
            default:
                assert(false);
                return nullptr;
        }
    }
}
