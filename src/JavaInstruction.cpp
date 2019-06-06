#include <Kophi/JavaInstruction.h>

#include <Kophi/JavaClass.h>

#include <sstream>

namespace Kophi {
    static const JavaInstructionInfo instructionInfo[] = {
            { JavaInstruction::Nop,             "Nop",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::AConst_Null,     "AConst_Null",     1, JavaInstructionParameters::Numbers },
            { JavaInstruction::IConst_m1,       "IConst_m1",       1, JavaInstructionParameters::Numbers },
            { JavaInstruction::IConst_0,        "IConst_0",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::IConst_1,        "IConst_1",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::IConst_2,        "IConst_2",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::IConst_3,        "IConst_3",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::IConst_4,        "IConst_4",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::IConst_5,        "IConst_5",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::LConst_0,        "LConst_0",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::LConst_1,        "LConst_1",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::FConst_0,        "FConst_0",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::FConst_1,        "FConst_1",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::FConst_2,        "FConst_2",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::DConst_0,        "DConst_0",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::DConst_1,        "DConst_1",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::BiPush,          "BiPush",          2, JavaInstructionParameters::Numbers },
            { JavaInstruction::SiPush,          "SiPush",          3, JavaInstructionParameters::Numbers },
            { JavaInstruction::Ldc,             "Ldc",             2, JavaInstructionParameters::Indexed },
            { JavaInstruction::Ldc_w,           "Ldc_w",           3, JavaInstructionParameters::Indexed },
            { JavaInstruction::Ldc2_w,          "Ldc2_w",          3, JavaInstructionParameters::Indexed },
            { JavaInstruction::ILoad,           "ILoad",           2, JavaInstructionParameters::Numbers },
            { JavaInstruction::LLoad,           "LLoad",           2, JavaInstructionParameters::Numbers },
            { JavaInstruction::FLoad,           "FLoad",           2, JavaInstructionParameters::Numbers },
            { JavaInstruction::DLoad,           "DLoad",           2, JavaInstructionParameters::Numbers },
            { JavaInstruction::ALoad,           "ALoad",           2, JavaInstructionParameters::Numbers },
            { JavaInstruction::ILoad_0,         "ILoad_0",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::ILoad_1,         "ILoad_1",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::ILoad_2,         "ILoad_2",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::ILoad_3,         "ILoad_3",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::LLoad_0,         "LLoad_0",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::LLoad_1,         "LLoad_1",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::LLoad_2,         "LLoad_2",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::LLoad_3,         "LLoad_3",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::FLoad_0,         "FLoad_0",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::FLoad_1,         "FLoad_1",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::FLoad_2,         "FLoad_2",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::FLoad_3,         "FLoad_3",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::DLoad_0,         "DLoad_0",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::DLoad_1,         "DLoad_1",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::DLoad_2,         "DLoad_2",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::DLoad_3,         "DLoad_3",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::ALoad_0,         "ALoad_0",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::ALoad_1,         "ALoad_1",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::ALoad_2,         "ALoad_2",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::ALoad_3,         "ALoad_3",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::IaLoad,          "IaLoad",          1, JavaInstructionParameters::Numbers },
            { JavaInstruction::LaLoad,          "LaLoad",          1, JavaInstructionParameters::Numbers },
            { JavaInstruction::FaLoad,          "FaLoad",          1, JavaInstructionParameters::Numbers },
            { JavaInstruction::DaLoad,          "DaLoad",          1, JavaInstructionParameters::Numbers },
            { JavaInstruction::AaLoad,          "AaLoad",          1, JavaInstructionParameters::Numbers },
            { JavaInstruction::BaLoad,          "BaLoad",          1, JavaInstructionParameters::Numbers },
            { JavaInstruction::CaLoad,          "CaLoad",          1, JavaInstructionParameters::Numbers },
            { JavaInstruction::SaLoad,          "SaLoad",          1, JavaInstructionParameters::Numbers },
            { JavaInstruction::IStore,          "IStore",          2, JavaInstructionParameters::Numbers },
            { JavaInstruction::LStore,          "LStore",          2, JavaInstructionParameters::Numbers },
            { JavaInstruction::FStore,          "FStore",          2, JavaInstructionParameters::Numbers },
            { JavaInstruction::DStore,          "DStore",          2, JavaInstructionParameters::Numbers },
            { JavaInstruction::AStore,          "AStore",          2, JavaInstructionParameters::Numbers },
            { JavaInstruction::IStore_0,        "IStore_0",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::IStore_1,        "IStore_1",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::IStore_2,        "IStore_2",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::IStore_3,        "IStore_3",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::LStore_0,        "LStore_0",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::LStore_1,        "LStore_1",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::LStore_2,        "LStore_2",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::LStore_3,        "LStore_3",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::FStore_0,        "FStore_0",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::FStore_1,        "FStore_1",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::FStore_2,        "FStore_2",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::FStore_3,        "FStore_3",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::DStore_0,        "DStore_0",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::DStore_1,        "DStore_1",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::DStore_2,        "DStore_2",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::DStore_3,        "DStore_3",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::AStore_0,        "AStore_0",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::AStore_1,        "AStore_1",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::AStore_2,        "AStore_2",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::AStore_3,        "AStore_3",        1, JavaInstructionParameters::Numbers },
            { JavaInstruction::IaStore,         "IaStore",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::LaStore,         "LaStore",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::FaStore,         "FaStore",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::DaStore,         "DaStore",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::AaStore,         "AaStore",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::BaStore,         "BaStore",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::CaStore,         "CaStore",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::SaStore,         "SaStore",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Pop,             "Pop",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Pop2,            "Pop2",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Dup,             "Dup",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Dup_x1,          "Dup_x1",          1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Dup_x2,          "Dup_x2",          1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Dup2,            "Dup2",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Dup2_x1,         "Dup2_x1",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Dup2_x2,         "Dup2_x2",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Swap,            "Swap",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Iadd,            "Iadd",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Ladd,            "Ladd",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Fadd,            "Fadd",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Dadd,            "Dadd",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Isub,            "Isub",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Lsub,            "Lsub",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Fsub,            "Fsub",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Dsub,            "Dsub",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Imul,            "Imul",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Lmul,            "Lmul",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Fmul,            "Fmul",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Dmul,            "Dmul",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Idiv,            "Idiv",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Ldiv,            "Ldiv",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Fdiv,            "Fdiv",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Ddiv,            "Ddiv",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Irem,            "Irem",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Lrem,            "Lrem",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Frem,            "Frem",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Drem,            "Drem",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Ineg,            "Ineg",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Lneg,            "Lneg",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Fneg,            "Fneg",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Dneg,            "Dneg",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Ishl,            "Ishl",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Lshl,            "Lshl",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Ishr,            "Ishr",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Lshr,            "Lshr",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Iushr,           "Iushr",           1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Lushr,           "Lushr",           1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Iand,            "Iand",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Land,            "Land",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Ior,             "Ior",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Lor,             "Lor",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Ixor,            "Ixor",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Lxor,            "Lxor",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Iinc,            "Iinc",            3, JavaInstructionParameters::Numbers },
            { JavaInstruction::I2l,             "I2l",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::I2f,             "I2f",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::I2d,             "I2d",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::L2i,             "L2i",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::L2f,             "L2f",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::L2d,             "L2d",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::F2i,             "F2i",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::F2l,             "F2l",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::F2d,             "F2d",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::D2i,             "D2i",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::D2l,             "D2l",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::D2f,             "D2f",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::I2b,             "I2b",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::I2c,             "I2c",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::I2s,             "I2s",             1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Lcmp,            "Lcmp",            1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Fcmpl,           "Fcmpl",           1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Fcmpg,           "Fcmpg",           1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Dcmpl,           "Dcmpl",           1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Dcmpg,           "Dcmpg",           1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Ifeq,            "Ifeq",            3, JavaInstructionParameters::Short   },
            { JavaInstruction::Ifne,            "Ifne",            3, JavaInstructionParameters::Short   },
            { JavaInstruction::Iflt,            "Iflt",            3, JavaInstructionParameters::Short   },
            { JavaInstruction::Ifge,            "Ifge",            3, JavaInstructionParameters::Short   },
            { JavaInstruction::Ifgt,            "Ifgt",            3, JavaInstructionParameters::Short   },
            { JavaInstruction::Ifle,            "Ifle",            3, JavaInstructionParameters::Short   },
            { JavaInstruction::If_icmpeq,       "If_icmpeq",       3, JavaInstructionParameters::Short   },
            { JavaInstruction::If_icmpne,       "If_icmpne",       3, JavaInstructionParameters::Short   },
            { JavaInstruction::If_icmplt,       "If_icmplt",       3, JavaInstructionParameters::Short   },
            { JavaInstruction::If_icmpge,       "If_icmpge",       3, JavaInstructionParameters::Short   },
            { JavaInstruction::If_icmpgt,       "If_icmpgt",       3, JavaInstructionParameters::Short   },
            { JavaInstruction::If_icmple,       "If_icmple",       3, JavaInstructionParameters::Short   },
            { JavaInstruction::If_acmpeq,       "If_acmpeq",       3, JavaInstructionParameters::Short   },
            { JavaInstruction::If_acmpne,       "If_acmpne",       3, JavaInstructionParameters::Short   },
            { JavaInstruction::Goto,            "Goto",            3, JavaInstructionParameters::Short },
            { JavaInstruction::Jsr,             "Jsr",             5, JavaInstructionParameters::Numbers },
            { JavaInstruction::Ret,             "Ret",             2, JavaInstructionParameters::Numbers },
            { JavaInstruction::TableSwitch,     "TableSwitch",     0, JavaInstructionParameters::Numbers },
            { JavaInstruction::LookupSwitch,    "LookupSwitch",    0, JavaInstructionParameters::Numbers },
            { JavaInstruction::IReturn,         "IReturn",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::LReturn,         "LReturn",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::FReturn,         "FReturn",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::DReturn,         "DReturn",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::AReturn,         "AReturn",         1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Return,          "Return",          1, JavaInstructionParameters::Numbers },
            { JavaInstruction::GetStatic,       "GetStatic",       3, JavaInstructionParameters::Indexed },
            { JavaInstruction::PutStatic,       "PutStatic",       3, JavaInstructionParameters::Indexed },
            { JavaInstruction::GetField,        "GetField",        3, JavaInstructionParameters::Indexed },
            { JavaInstruction::PutField,        "PutField",        3, JavaInstructionParameters::Indexed },
            { JavaInstruction::InvokeVirtual,   "InvokeVirtual",   3, JavaInstructionParameters::Indexed },
            { JavaInstruction::InvokeSpecial,   "InvokeSpecial",   3, JavaInstructionParameters::Indexed },
            { JavaInstruction::InvokeStatic,    "InvokeStatic",    3, JavaInstructionParameters::Indexed },
            { JavaInstruction::InvokeInterface, "InvokeInterface", 3, JavaInstructionParameters::Indexed },
            { JavaInstruction::InvokeDynamic,   "InvokeDynamic",   3, JavaInstructionParameters::Indexed },
            { JavaInstruction::New,             "New",             3, JavaInstructionParameters::Indexed },
            { JavaInstruction::NewArray,        "NewArray",        2, JavaInstructionParameters::Numbers },
            { JavaInstruction::ANewArray,       "ANewArray",       3, JavaInstructionParameters::Indexed },
            { JavaInstruction::ArrayLength,     "ArrayLength",     1, JavaInstructionParameters::Numbers },
            { JavaInstruction::AThrow,          "AThrow",          1, JavaInstructionParameters::Numbers },
            { JavaInstruction::CheckCast,       "CheckCast",       3, JavaInstructionParameters::Numbers },
            { JavaInstruction::InstanceOf,      "InstanceOf",      3, JavaInstructionParameters::Numbers },
            { JavaInstruction::MonitorEnter,    "MonitorEnter",    1, JavaInstructionParameters::Numbers },
            { JavaInstruction::MonitorExit,     "MonitorExit",     1, JavaInstructionParameters::Numbers },
            { JavaInstruction::Wide,            "Wide",            4, JavaInstructionParameters::Numbers },
            { JavaInstruction::MultiANewArray,  "MultiANewArray",  4, JavaInstructionParameters::Numbers },
            { JavaInstruction::IfNull,          "IfNull",          3, JavaInstructionParameters::Numbers },
            { JavaInstruction::IfNonNull,       "IfNonNull",       3, JavaInstructionParameters::Numbers },
            { JavaInstruction::Goto_w,          "Goto_w",          5, JavaInstructionParameters::Numbers },
            { JavaInstruction::Jsr_w,           "Jsr_w",           5, JavaInstructionParameters::Numbers },
    };

    const JavaInstructionInfo &lookupInstruction(JavaInstruction inst) {
        return instructionInfo[(uint8_t)inst];
    }

    std::string createDisasm(const JavaClass &java, const unsigned char *data, unsigned length, unsigned pc) {
        unsigned index = 0;
        std::stringstream stream;

        while (index < length) {
            JavaInstruction inst = (JavaInstruction) data[index];
            const JavaInstructionInfo &info = lookupInstruction(inst);
            stream << "\t\t\t" << (pc + index) << ": " << info.name;
            switch (info.parameters) {
                case JavaInstructionParameters::Numbers:
                    for (int a = 1; a < info.length; a++) {
                        stream << " " << (unsigned) data[index + a];
                    }
                    break;
                case JavaInstructionParameters::Indexed: {
                    PoolIndex poolIndex = 0;
                    if (info.length == 2) {
                        poolIndex = data[index + 1];
                    } else {
                        poolIndex = (data[index + 1] << 8) | data[index + 2];
                    }

                    stream << " {" << poolIndex << "}: " << java.pool[poolIndex]->toString();
                    break;
                }
                case JavaInstructionParameters::Short: {
                    stream << " " << (short)((data[index + 1] << 8) | data[index + 2]);
                }
            }
            index += info.length;
            if (index < length)
                stream << "\n";
        }

        return stream.str();
    }
}
