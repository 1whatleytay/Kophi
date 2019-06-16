#ifndef KOPHI_JAVAINSTRUCTION_H
#define KOPHI_JAVAINSTRUCTION_H

#include <Kophi/Utils.h>

namespace Kophi {
    class JavaClass;

    enum class JavaInstruction : uint8_t {
        Nop = 0x0,
        AConst_Null = 0x1,
        IConst_m1 = 0x2,
        IConst_0 = 0x3,
        IConst_1 = 0x4,
        IConst_2 = 0x5,
        IConst_3 = 0x6,
        IConst_4 = 0x7,
        IConst_5 = 0x8,
        LConst_0 = 0x9,
        LConst_1 = 0xa,
        FConst_0 = 0xb,
        FConst_1 = 0xc,
        FConst_2 = 0xd,
        DConst_0 = 0xe,
        DConst_1 = 0xf,
        BiPush = 0x10,
        SiPush = 0x11,
        Ldc = 0x12,
        Ldc_w = 0x13,
        Ldc2_w = 0x14,
        ILoad = 0x15,
        LLoad = 0x16,
        FLoad = 0x17,
        DLoad = 0x18,
        ALoad = 0x19,
        ILoad_0 = 0x1a,
        ILoad_1 = 0x1b,
        ILoad_2 = 0x1c,
        ILoad_3 = 0x1d,
        LLoad_0 = 0x1e,
        LLoad_1 = 0x1f,
        LLoad_2 = 0x20,
        LLoad_3 = 0x21,
        FLoad_0 = 0x22,
        FLoad_1 = 0x23,
        FLoad_2 = 0x24,
        FLoad_3 = 0x25,
        DLoad_0 = 0x26,
        DLoad_1 = 0x27,
        DLoad_2 = 0x28,
        DLoad_3 = 0x29,
        ALoad_0 = 0x2a,
        ALoad_1 = 0x2b,
        ALoad_2 = 0x2c,
        ALoad_3 = 0x2d,
        IaLoad = 0x2e,
        LaLoad = 0x2f,
        FaLoad = 0x30,
        DaLoad = 0x31,
        AaLoad = 0x32,
        BaLoad = 0x33,
        CaLoad = 0x34,
        SaLoad = 0x35,
        IStore = 0x36,
        LStore = 0x37,
        FStore = 0x38,
        DStore = 0x39,
        AStore = 0x3a,
        IStore_0 = 0x3b,
        IStore_1 = 0x3c,
        IStore_2 = 0x3d,
        IStore_3 = 0x3e,
        LStore_0 = 0x3f,
        LStore_1 = 0x40,
        LStore_2 = 0x41,
        LStore_3 = 0x42,
        FStore_0 = 0x43,
        FStore_1 = 0x44,
        FStore_2 = 0x45,
        FStore_3 = 0x46,
        DStore_0 = 0x47,
        DStore_1 = 0x48,
        DStore_2 = 0x49,
        DStore_3 = 0x4a,
        AStore_0 = 0x4b,
        AStore_1 = 0x4c,
        AStore_2 = 0x4d,
        AStore_3 = 0x4e,
        IaStore = 0x4f,
        LaStore = 0x50,
        FaStore = 0x51,
        DaStore = 0x52,
        AaStore = 0x53,
        BaStore = 0x54,
        CaStore = 0x55,
        SaStore = 0x56,
        Pop = 0x57,
        Pop2 = 0x58,
        Dup = 0x59,
        Dup_x1 = 0x5a,
        Dup_x2 = 0x5b,
        Dup2 = 0x5c,
        Dup2_x1 = 0x5d,
        Dup2_x2 = 0x5e,
        Swap = 0x5f,
        Iadd = 0x60,
        Ladd = 0x61,
        Fadd = 0x62,
        Dadd = 0x63,
        Isub = 0x64,
        Lsub = 0x65,
        Fsub = 0x66,
        Dsub = 0x67,
        Imul = 0x68,
        Lmul = 0x69,
        Fmul = 0x6a,
        Dmul = 0x6b,
        Idiv = 0x6c,
        Ldiv = 0x6d,
        Fdiv = 0x6e,
        Ddiv = 0x6f,
        Irem = 0x70,
        Lrem = 0x71,
        Frem = 0x72,
        Drem = 0x73,
        Ineg = 0x74,
        Lneg = 0x75,
        Fneg = 0x76,
        Dneg = 0x77,
        Ishl = 0x78,
        Lshl = 0x79,
        Ishr = 0x7a,
        Lshr = 0x7b,
        Iushr = 0x7c,
        Lushr = 0x7d,
        Iand = 0x7e,
        Land = 0x7f,
        Ior = 0x80,
        Lor = 0x81,
        Ixor = 0x82,
        Lxor = 0x83,
        Iinc = 0x84,
        I2l = 0x85,
        I2f = 0x86,
        I2d = 0x87,
        L2i = 0x88,
        L2f = 0x89,
        L2d = 0x8a,
        F2i = 0x8b,
        F2l = 0x8c,
        F2d = 0x8d,
        D2i = 0x8e,
        D2l = 0x8f,
        D2f = 0x90,
        I2b = 0x91,
        I2c = 0x92,
        I2s = 0x93,
        Lcmp = 0x94,
        Fcmpl = 0x95,
        Fcmpg = 0x96,
        Dcmpl = 0x97,
        Dcmpg = 0x98,
        Ifeq = 0x99,
        Ifne = 0x9a,
        Iflt = 0x9b,
        Ifge = 0x9c,
        Ifgt = 0x9d,
        Ifle = 0x9e,
        If_icmpeq = 0x9f,
        If_icmpne = 0xa0,
        If_icmplt = 0xa1,
        If_icmpge = 0xa2,
        If_icmpgt = 0xa3,
        If_icmple = 0xa4,
        If_acmpeq = 0xa5,
        If_acmpne = 0xa6,
        Goto = 0xa7,
        Jsr = 0xa8,
        Ret = 0xa9,
        TableSwitch = 0xaa,
        LookupSwitch = 0xab,
        IReturn = 0xac,
        LReturn = 0xad,
        FReturn = 0xae,
        DReturn = 0xaf,
        AReturn = 0xb0,
        Return = 0xb1,
        GetStatic = 0xb2,
        PutStatic = 0xb3,
        GetField = 0xb4,
        PutField = 0xb5,
        InvokeVirtual = 0xb6,
        InvokeSpecial = 0xb7,
        InvokeStatic = 0xb8,
        InvokeInterface = 0xb9,
        InvokeDynamic = 0xba,
        New = 0xbb,
        NewArray = 0xbc,
        ANewArray = 0xbd,
        ArrayLength = 0xbe,
        AThrow = 0xbf,
        CheckCast = 0xc0,
        InstanceOf = 0xc1,
        MonitorEnter = 0xc2,
        MonitorExit = 0xc3,
        Wide = 0xc4,
        MultiANewArray = 0xc5,
        IfNull = 0xc6,
        IfNonNull = 0xc7,
        Goto_w = 0xc8,
        Jsr_w = 0xc9,
    };

    enum class JavaInstructionParameters {
        Numbers,
        Short,
        Indexed,
        Switch,
    };

    class JavaInstructionInfo {
    public:
        JavaInstruction code;
        std::string name;
        unsigned length;
        JavaInstructionParameters parameters;
    };

    std::string createDisasm(const JavaClass &java, const unsigned char *data, unsigned length, unsigned pc = 0);

    const JavaInstructionInfo &lookupInstruction(JavaInstruction inst);
}

#endif //KOPHI_JAVAINSTRUCTION_H
