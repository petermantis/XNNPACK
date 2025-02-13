// Copyright 2022 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <cstddef>
#include <cstdint>

#include <xnnpack/assembler.h>

namespace xnnpack {
namespace aarch64 {

constexpr size_t kInstructionSizeInBytesLog2 = 2;

struct XRegister {
  uint8_t code;
};

constexpr XRegister x0{0};
constexpr XRegister x1{1};
constexpr XRegister x2{2};
constexpr XRegister x3{3};
constexpr XRegister x4{4};
constexpr XRegister x5{5};
constexpr XRegister x6{6};
constexpr XRegister x7{7};
constexpr XRegister x8{8};
constexpr XRegister x9{9};
constexpr XRegister x10{10};
constexpr XRegister x11{11};
constexpr XRegister x12{12};
constexpr XRegister x13{13};
constexpr XRegister x14{14};
constexpr XRegister x15{15};
constexpr XRegister x16{16};
constexpr XRegister x17{17};
constexpr XRegister x18{18};
constexpr XRegister x19{19};
constexpr XRegister x20{20};
constexpr XRegister x21{21};
constexpr XRegister x22{22};
constexpr XRegister x23{23};
constexpr XRegister x24{24};
constexpr XRegister x25{25};
constexpr XRegister x26{26};
constexpr XRegister x27{27};
constexpr XRegister x28{28};
constexpr XRegister x29{29};
constexpr XRegister x30{30};
constexpr XRegister xzr{31};
constexpr XRegister sp{31};

struct VRegisterLane {
  uint8_t code;
  uint8_t size;
  uint8_t lane;
  const bool is_s() { return size == 2; };
};

struct ScalarVRegister{
  uint8_t code;
  uint8_t size;

  const VRegisterLane operator[](std::size_t pos) const {
    return VRegisterLane{code, size, static_cast<uint8_t>(pos)};
  }
};

struct VRegister {
  uint8_t code;
  uint8_t size;
  uint8_t q;

  VRegister v8b() const { return {code, 0, 0}; }
  VRegister v16b() const { return {code, 0, 1}; }
  VRegister v4h() const { return {code, 1, 0}; }
  VRegister v8h() const { return {code, 1, 1}; }
  VRegister v2s() const { return {code, 2, 0}; }
  VRegister v4s() const { return {code, 2, 1}; }
  VRegister v1d() const { return {code, 3, 0}; }
  VRegister v2d() const { return {code, 3, 1}; }

  ScalarVRegister s() const { return {code, 2}; }
  ScalarVRegister d() const { return {code, 3}; }

  const bool is_s() { return size == 2; };
};

constexpr VRegister v0{0};
constexpr VRegister v1{1};
constexpr VRegister v2{2};
constexpr VRegister v3{3};
constexpr VRegister v4{4};
constexpr VRegister v5{5};
constexpr VRegister v6{6};
constexpr VRegister v7{7};
constexpr VRegister v8{8};
constexpr VRegister v9{9};
constexpr VRegister v10{10};
constexpr VRegister v11{11};
constexpr VRegister v12{12};
constexpr VRegister v13{13};
constexpr VRegister v14{14};
constexpr VRegister v15{15};
constexpr VRegister v16{16};
constexpr VRegister v17{17};
constexpr VRegister v18{18};
constexpr VRegister v19{19};
constexpr VRegister v20{20};
constexpr VRegister v21{21};
constexpr VRegister v22{22};
constexpr VRegister v23{23};
constexpr VRegister v24{24};
constexpr VRegister v25{25};
constexpr VRegister v26{26};
constexpr VRegister v27{27};
constexpr VRegister v28{28};
constexpr VRegister v29{29};
constexpr VRegister v30{30};
constexpr VRegister v31{31};

struct VRegisterList {
  VRegisterList(VRegister vt1)
      : vt1(vt1), length(1) {}
  VRegisterList(VRegister vt1, VRegister vt2)
      : vt1(vt1), vt2(vt2), length(2) {}
  VRegisterList(VRegister vt1, VRegister vt2, VRegister vt3)
      : vt1(vt1), vt2(vt2), vt3(vt3), length(3) {}
  VRegisterList(VRegister vt1, VRegister vt2, VRegister vt3, VRegister vt4)
      : vt1(vt1), vt2(vt2), vt3(vt3), vt4(vt4), length(4) {}

  VRegister vt1;
  VRegister vt2;
  VRegister vt3;
  VRegister vt4;
  uint8_t length;
};

struct SRegister {
  uint8_t code;
};

constexpr SRegister s0{0};
constexpr SRegister s1{1};
constexpr SRegister s2{2};
constexpr SRegister s3{3};
constexpr SRegister s4{4};
constexpr SRegister s5{5};
constexpr SRegister s6{6};
constexpr SRegister s7{7};
constexpr SRegister s8{8};
constexpr SRegister s9{9};
constexpr SRegister s10{10};
constexpr SRegister s11{11};
constexpr SRegister s12{12};
constexpr SRegister s13{13};
constexpr SRegister s14{14};
constexpr SRegister s15{15};
constexpr SRegister s16{16};
constexpr SRegister s17{17};
constexpr SRegister s18{18};
constexpr SRegister s19{19};
constexpr SRegister s20{20};
constexpr SRegister s21{21};
constexpr SRegister s22{22};
constexpr SRegister s23{23};
constexpr SRegister s24{24};
constexpr SRegister s25{25};
constexpr SRegister s26{26};
constexpr SRegister s27{27};
constexpr SRegister s28{28};
constexpr SRegister s29{29};
constexpr SRegister s30{30};
constexpr SRegister s31{31};

struct DRegister {
  uint8_t code;
};

constexpr DRegister d0{0};
constexpr DRegister d1{1};
constexpr DRegister d2{2};
constexpr DRegister d3{3};
constexpr DRegister d4{4};
constexpr DRegister d5{5};
constexpr DRegister d6{6};
constexpr DRegister d7{7};
constexpr DRegister d8{8};
constexpr DRegister d9{9};
constexpr DRegister d10{10};
constexpr DRegister d11{11};
constexpr DRegister d12{12};
constexpr DRegister d13{13};
constexpr DRegister d14{14};
constexpr DRegister d15{15};
constexpr DRegister d16{16};
constexpr DRegister d17{17};
constexpr DRegister d18{18};
constexpr DRegister d19{19};
constexpr DRegister d20{20};
constexpr DRegister d21{21};
constexpr DRegister d22{22};
constexpr DRegister d23{23};
constexpr DRegister d24{24};
constexpr DRegister d25{25};
constexpr DRegister d26{26};
constexpr DRegister d27{27};
constexpr DRegister d28{28};
constexpr DRegister d29{29};
constexpr DRegister d30{30};
constexpr DRegister d31{31};

struct QRegister {
  uint8_t code;
};

constexpr QRegister q0{0};
constexpr QRegister q1{1};
constexpr QRegister q2{2};
constexpr QRegister q3{3};
constexpr QRegister q4{4};
constexpr QRegister q5{5};
constexpr QRegister q6{6};
constexpr QRegister q7{7};
constexpr QRegister q8{8};
constexpr QRegister q9{9};
constexpr QRegister q10{10};
constexpr QRegister q11{11};
constexpr QRegister q12{12};
constexpr QRegister q13{13};
constexpr QRegister q14{14};
constexpr QRegister q15{15};
constexpr QRegister q16{16};
constexpr QRegister q17{17};
constexpr QRegister q18{18};
constexpr QRegister q19{19};
constexpr QRegister q20{20};
constexpr QRegister q21{21};
constexpr QRegister q22{22};
constexpr QRegister q23{23};
constexpr QRegister q24{24};
constexpr QRegister q25{25};
constexpr QRegister q26{26};
constexpr QRegister q27{27};
constexpr QRegister q28{28};
constexpr QRegister q29{29};
constexpr QRegister q30{30};
constexpr QRegister q31{31};

// C1.3.3 Load/Store addressing modes
enum class AddressingMode {
  kOffset, // Base plus offset: [base{, #imm}] ; [base, Xm{, LSL #imm}].
  kPostIndex, // Post-index: [base], #imm ; [base], Xm.
  kPreIndex, // Pre-index: [base, #imm]!
};

struct MemOperand {
  MemOperand(XRegister xn): base(xn), mode(AddressingMode::kOffset), offset(0) {}
  MemOperand(XRegister xn, int32_t offset): base(xn), mode(AddressingMode::kOffset), offset(offset) {}
  MemOperand(XRegister xn, int32_t offset, AddressingMode mode): base(xn), mode(mode), offset(offset) {}

  // Overload postfix increment to indicate a pre-index addressing mode for load/stores.
  MemOperand operator++(int) {
    mode = AddressingMode::kPreIndex;
    return *this;
  }

  XRegister base;
  AddressingMode mode;
  int32_t offset;
};

static inline MemOperand operator,(XRegister r, int32_t offset) {
  return MemOperand(r, offset);
}

// Helper struct for some syntax sugar to look like native assembly, see mem.
struct MemOperandHelper {
  MemOperand operator[](MemOperand op) const { return op; }
  MemOperand operator[](XRegister r) const { return MemOperand(r, 0); }
};

// Use "mem" (and its overload of array subscript operator) to get some syntax
// that looks closer to native assembly when accessing memory. For example:
// - ldp(x0, x1, mem[rn, offset]); // offset
// - ldp(x0, x1, mem[rn], offset); // post-indexed
constexpr MemOperandHelper mem;

enum PrefetchOp {
  kPLDL1KEEP = 0
};

enum Condition : uint32_t {
  kEQ = 0x0,
  kNE = 0x1,
  kCS = 0x2,
  kCC = 0x3,
  kMI = 0x4,
  kPL = 0x5,
  kVS = 0x6,
  kVC = 0x7,
  kHI = 0x8,
  kLS = 0x9,
  kGE = 0xa,
  kLT = 0xB,
  kGT = 0xC,
  kLE = 0xD,
  kAL = 0xE,
  kHS = kCS,
  kLO = kCC,
};

enum class BranchType {
  kConditional,
  // For encoding, TBZ and TBNZ are treated similarly, called TBXZ here.
  kTbxz,
  kUnconditional,
};

// Instruction to use for alignment.
// kNop should be used for loops, branch targets. kHlt for end of function.
enum class AlignInstruction {
  kHlt,
  kNop,
};

class Assembler : public AssemblerBase {
 public:
  using AssemblerBase::AssemblerBase;

  // Base instructions.
  void add(XRegister xd, XRegister xn, uint16_t imm12);
  void add(XRegister xd, XRegister xn, XRegister xm);
  void b(Label& l);
  void b_eq(Label& l) { return b(kEQ, l); }
  void b_hi(Label& l) { return b(kHI, l); }
  void b_hs(Label& l) { return b(kHS, l); }
  void b_lo(Label& l) { return b(kLO, l); }
  void b_ne(Label& l) { return b(kNE, l); }
  void cmp(XRegister xn, uint16_t imm12);
  void cmp(XRegister xn, XRegister xm);
  void csel(XRegister xd, XRegister xn, XRegister xm, Condition c);
  void hlt();
  void ldp(XRegister xt1, XRegister xt2, MemOperand xn);
  void ldp(XRegister xt1, XRegister xt2, MemOperand xn, int32_t imm);
  void ldr(XRegister xt, MemOperand xn);
  void ldr(XRegister xt, MemOperand xn, int32_t imm);
  void mov(XRegister xd, XRegister xn);
  void nop();
  void prfm(PrefetchOp prfop, MemOperand xn);
  void ret();
  void stp(XRegister xt1, XRegister xt2, MemOperand xn);
  void str(XRegister xt1, MemOperand xn);
  void sub(XRegister xd, XRegister xn, XRegister xm);
  void subs(XRegister xd, XRegister xn, uint16_t imm12);
  void tbnz(XRegister xd, uint8_t bit, Label& l);
  void tbz(XRegister xd, uint8_t bit, Label& l);
  // Only immediates with lowest N bits set are supported.
  void tst(XRegister xn, uint8_t imm);

  // SIMD instructions
  void dup(DRegister dd, VRegisterLane vn);
  void fadd(VRegister vd, VRegister vn, VRegister vm);
  void fmax(VRegister vd, VRegister vn, VRegister vm);
  void fmin(VRegister vd, VRegister vn, VRegister vm);
  void fmla(VRegister vd, VRegister vn, VRegisterLane vm);
  void ld1(VRegisterList vs, MemOperand xn, int32_t imm);
  void ld1r(VRegisterList xs, MemOperand xn);
  void ld2r(VRegisterList xs, MemOperand xn);
  void ldp(DRegister dt1, DRegister dt2, MemOperand xn);
  void ldp(DRegister dt1, DRegister dt2, MemOperand xn, int32_t imm);
  void ldp(QRegister qt1, QRegister qt2, MemOperand xn, int32_t imm);
  void ldr(DRegister dt, MemOperand xn, int32_t imm);
  void ldr(QRegister qt, MemOperand xn, int32_t imm);
  void ldr(SRegister st, MemOperand xn, int32_t imm);
  void mov(VRegister vd, VRegister vn);
  void movi(VRegister vd, uint8_t imm);
  void st1(VRegisterList vs, MemOperand xn, XRegister xm);
  void stp(DRegister dt1, DRegister dt2, MemOperand xn);
  void stp(QRegister qt1, QRegister qt2, MemOperand xn);
  void stp(QRegister qt1, QRegister qt2, MemOperand xn, int32_t imm);
  void str(DRegister dt, MemOperand xn, int32_t imm);
  void str(QRegister qt, MemOperand xn, int32_t imm);
  void str(SRegister st, MemOperand xn);
  void str(SRegister st, MemOperand xn, int32_t imm);

  // Aligns the buffer to n (must be a power of 2).
  void align(uint8_t n, AlignInstruction instr);
  void align(uint8_t n) { align(n, AlignInstruction::kNop); }
  // Binds Label l to the current location in the code buffer.
  void bind(Label& l);

 private:
  void b(Condition c, Label& l);
  void branch_to_label(uint32_t opcode, BranchType bt, Label& l);
  void ldr(uint32_t size, uint32_t opc, MemOperand xn, int32_t imm, uint8_t rt_code);
  void str(uint32_t size, uint32_t opc, MemOperand xn, int32_t imm, uint8_t rt_code);
  void tb_helper(uint32_t op, XRegister xd, uint8_t bit, Label& l);

};

}  // namespace aarch64
}  // namespace xnnpack
