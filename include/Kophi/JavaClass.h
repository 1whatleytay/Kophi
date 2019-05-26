#ifndef KOPHI_JAVACLASS_H
#define KOPHI_JAVACLASS_H

#include <Kophi/Utils.h>

#include <Kophi/JavaConstant.h>
#include <Kophi/JavaProperty.h>
#include <Kophi/JavaAttribute.h>

namespace Kophi {
    constexpr uint32_t JAVA_CLASS_MAGIC = 0xCAFEBABE;

    class JavaClass {
    public:
        uint32_t magic = 0;
        uint16_t majorVersion = 0;
        uint16_t minorVersion = 0;
        AccessFlags accessFlags = AccessFlags::None;
        PoolIndex thisClass = 0;
        PoolIndex superClass = 0;
        uint16_t constantCount = 0;
        uint16_t interfaceCount = 0;
        uint16_t fieldCount = 0;
        uint16_t methodCount = 0;
        uint16_t attributeCount = 0;
        std::vector <JavaConstant> pool;
        std::vector <uint16_t> interfaces;
        std::vector <JavaField> fields;
        std::vector <JavaMethod> methods;
        std::vector <JavaAttribute> attributes;

        // TODO: make verify method

        const JavaConstantClass *getThisClass() const;
        const JavaConstantClass *getSuperClass() const;

        explicit JavaClass(const std::vector<unsigned char> &data);
        explicit JavaClass(const std::string &path);
    };

    std::string describeClass(const JavaClass &java);
}

#endif //KOPHI_JAVACLASS_H
