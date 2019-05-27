#include <utility>

#include <Kophi/Utils.h>

namespace Kophi {
    bool hasAccessFlag(AccessFlags flags, AccessFlags check) {
        return (uint16_t)flags & (uint16_t)check;
    }

    std::string describeAccessFlags(AccessFlags flags) {
        return (std::string(hasAccessFlag(flags, AccessFlags::Public) ? " public" : "")
                + (hasAccessFlag(flags, AccessFlags::Private) ? " private" : "")
                + (hasAccessFlag(flags, AccessFlags::Protected) ? " protected" : "")
                + (hasAccessFlag(flags, AccessFlags::Static) ? " static" : "")
                + (hasAccessFlag(flags, AccessFlags::Final) ? " final" : "")
                + (hasAccessFlag(flags, AccessFlags::Synchronized) ? " synchronized" : "")
                + (hasAccessFlag(flags, AccessFlags::Super) ? " super" : "")
                + (hasAccessFlag(flags, AccessFlags::Bridge) ? " bridge" : "")
                + (hasAccessFlag(flags, AccessFlags::VarArgs) ? " varargs" : "")
                + (hasAccessFlag(flags, AccessFlags::Native) ? " native" : "")
                + (hasAccessFlag(flags, AccessFlags::Interface) ? " interface" : "")
                + (hasAccessFlag(flags, AccessFlags::Abstract) ? " abstract" : "")
                + (hasAccessFlag(flags, AccessFlags::Strict) ? " strict" : "")
                + (hasAccessFlag(flags, AccessFlags::Synthetic) ? " synthetic" : "")
                + (hasAccessFlag(flags, AccessFlags::Volatile) ? " volatile" : "")
                + (hasAccessFlag(flags, AccessFlags::Transient) ? " transient" : "")
                + (hasAccessFlag(flags, AccessFlags::Annotation) ? " annotation" : "")
                + (hasAccessFlag(flags, AccessFlags::Enum) ? " enum" : "")
                + (hasAccessFlag(flags, AccessFlags::Module) ? " module" : "")
        ).substr(flags != AccessFlags::None);
    }

    const char *ConstantCastException::what() const noexcept {
        return std::string("Could not cast constant from " + std::to_string((uint8_t)from)
                           + " to " + std::to_string((uint8_t)to) + ".").c_str();
    }

    ConstantCastException::ConstantCastException(JavaConstantTag from, JavaConstantTag to) : from(from), to(to) { }

    const char *AttributeCastException::what() const noexcept {
        return std::string("Could not cast attribute from " + from
                           + " to " + to + ".").c_str();
    }

    AttributeCastException::AttributeCastException(
            std::string from, std::string to) : from(std::move(from)), to(std::move(to)) { }

    const char *UnknownAttribute::what() const noexcept {
        return std::string("Attempted to read unknown attribute \"" + missing + "\".").c_str();
    }

    UnknownAttribute::UnknownAttribute(std::string missing) : missing(std::move(missing)) {}

}
