#include <utility>

#ifndef KOPHI_UTILS_H
#define KOPHI_UTILS_H

#include <string>
#include <vector>

namespace Kophi {
    typedef uint8_t Byte;
    typedef uint16_t PoolIndex;

    typedef int32_t JavaInt;
    typedef int64_t JavaLong;
    typedef float JavaFloat;
    typedef double JavaDouble;

    enum class AccessFlags : uint16_t {
        None = 0x0000,

        // Class
        Public    = 0x0001,
        Private   = 0x0002,
        Protected = 0x0004,
        Static    = 0x0008,
        Final     = 0x0010,
        Volatile  = 0x0040,
        Transient = 0x0080,
        Synthetic = 0x1000,
        Enum      = 0x4000,

        // Class
        Super      = 0x0020,
        Interface  = 0x0200,
        Abstract   = 0x0400,
        Annotation = 0x2000,
        Module     = 0x8000,

        // Method
        Synchronized = 0x0020,
        Bridge       = 0x0040,
        VarArgs      = 0x0080,
        Native       = 0x0100,
        Strict       = 0x0800,
    };

    enum class ReferenceKind : uint8_t {
        Unknown          = 0,
        GetField         = 1,
        GetStatic        = 2,
        PutField         = 3,
        PutStatic        = 4,
        InvokeVirtual    = 5,
        InvokeStatic     = 6,
        InvokeSpecial    = 7,
        NewInvokeSpecial = 8,
        InvokeInterface  = 9,
    };

    enum class JavaConstantTag : uint8_t {
        Unknown            = 0,
        Utf8               = 1,
        Integer            = 3,
        Float              = 4,
        Long               = 5,
        Double             = 6,
        Class              = 7,
        String             = 8,
        FieldRef           = 9,
        MethodRef          = 10,
        InterfaceMethodRef = 11,
        NameAndType        = 12,
        MethodHandle       = 15,
        MethodType         = 16,
        Dynamic            = 17,
        InvokeDynamic      = 18,
        Module             = 19,
        Package            = 20,
    };

    std::string describeAccessFlags(AccessFlags flags);

    class ConstantCastException : std::exception {
        JavaConstantTag from, to;

    public:
        const char *what() const noexcept override;

        ConstantCastException(JavaConstantTag from, JavaConstantTag to);
    };

    class AttributeCastException : std::exception {
        std::string from, to;

    public:
        const char *what() const noexcept override;

        AttributeCastException(std::string from, std::string to);
    };

    class UnknownAttribute : std::exception {
        std::string missing;

    public:
        const char *what() const noexcept override;

        explicit UnknownAttribute(std::string missing);
    };
}

#endif //KOPHI_UTILS_H
