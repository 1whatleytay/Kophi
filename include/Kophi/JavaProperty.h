#ifndef KOPHI_JAVAPROPERTY_H
#define KOPHI_JAVAPROPERTY_H

#include <Kophi/Utils.h>

#include <Kophi/JavaAttribute.h>
#include <Kophi/JavaConstant.h>

namespace Kophi {
    class JavaClass;

    class JavaPropertyType {
    public:
        const JavaClass &parent;

        AccessFlags accessFlags;
        uint16_t nameIndex;
        uint16_t descriptorIndex;
        uint16_t attributeCount;
        std::vector<JavaAttribute> attributes;

        std::string getName() const;
        std::string getDescriptor() const;

        JavaAttributeCode *getCode() const;

        JavaAttribute searchAttributes(const std::string &name) const;

        explicit JavaPropertyType(const JavaClass &parent, const unsigned char *data, unsigned &index);
    };
    typedef std::shared_ptr<JavaPropertyType> JavaProperty;

    typedef JavaProperty JavaMethod;
    typedef JavaProperty JavaField;
}

#endif //KOPHI_JAVAPROPERTY_H
