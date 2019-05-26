#include <Kophi/Private.h>
#include <Kophi/JavaClass.h>
#include <Kophi/JavaProperty.h>

namespace Kophi {
    std::string JavaProperty::getName() const {
        return JavaConstantUtf8::cast(parent.pool[nameIndex])->text;
    }

    std::string JavaProperty::getDescriptor() const {
        return JavaConstantUtf8::cast(parent.pool[descriptorIndex])->text;
    }

    JavaProperty::JavaProperty(const JavaClass &parent, const unsigned char *data, unsigned int &index)
    : parent(parent) {
        unsigned m = 0;
        accessFlags = (AccessFlags) Private::swapEndian(*(uint16_t *) &data[m]);
        m += sizeof(AccessFlags);
        nameIndex = Private::swapEndian(*(uint16_t *) &data[m]);
        m += sizeof(uint16_t);
        descriptorIndex = Private::swapEndian(*(uint16_t *) &data[m]);
        m += sizeof(uint16_t);

        attributeCount = Private::swapEndian(*(uint16_t *) &data[m]);
        m += sizeof(uint16_t);
        attributes.reserve(attributeCount);
        for (int a = 0; a < attributeCount; a++) {
            attributes.push_back(JavaAttributeType::build(parent, &data[m], m));
        }

        index += m;
    }
}
