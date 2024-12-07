#ifndef QUASAR_BITCODE_HPP
#define QUASAR_BITCODE_HPP

#include <vector>
#include <string>
#include <variant>

#include <absl/container/flat_hash_map.h>

#include <quasar/Iteration.hpp>

namespace quasar::bitcode {
  enum class Opcode: uint8_t {
    LoadConstant,            // Load a value from static code section into a register
    LoadRegister,            // Load a register into current context

    Add,                     // Sum 2 values (__add__)
    Subtract,                // Subtract 2 values (__sub__)
    Multiply,                // Multiples 2 values (__mul__)
    Divide,                  // Divides 2 values (__truediv__)
    DivideWhole,             // Divides 2 values and rounds to nearest integer (__floordiv__)
    Modulo,                  // Extracts remainder of division (__mod__)
    Exponentiate,            // Raises first argument to the power of the second one (__pow__)
    MatrixMultiply,          // Multiplies 2 matrices (__matmul__)

    BitwiseAnd,              // Checks first AND second operand (__and__)
    BitwiseOr,               // Checks first OR second operand (__or__)
    BitwiseXor,              // Checks first if exactly one operand is true (__xor__)
    BitwiseNor,              // Inverts register (__invert__)
    LeftShift,               // Left shifts a register (__lshift__)
    RightShift,              // Right shifts a register (__rshift)

    CompareLess,             // Compares if first operand is less than second (__lt__)
    CompareLessOrEquals,     // Compares if first operand is less or equal the second (__lte__)
    CompareEquals,           // Compares if first operand equals the second (__eq__)
    CompareNotEquals,        // Compares if first operand does not equal the second (__ne__)
    CompareGreater,          // Compares if first operand is greater than the second (__gt__)
    CompareGreaterOrEquals,  // Compares if first operand is greater or equal than second (__ge__)
    CompareIs,               // Compares if first operand is second (is)
    CompareIsNot,            // Compares if first operand is not second (is not)
    CompareIn,               // Compares if first operand is in second (in)
    CompareNotIn,            // Compares if first operand is not in second (not in)

    Evaluate,                // Evaluates if register value is true or false (__bool__)
    GetAttribute,            // Loads attribute name value into the context (__getattr__)
    SetAttribute,            // Modifies attribute value (__setattr__)
    DeleteAttribute,         // Deletes an attribute from object (__delitem__)
    GetItem,                 // Loads an item by index into the context (__getitem__)
    SetItem,                 // Modifies an item by index (__setitem__)
    DeleteItem,              // Deletes an item from collection by index (__delitem__)

    Iterate,                 // Generates iterator (__iter__)
    Next,                    // Obtains next value in the iterator (__next__)

    EnterContext,            // Enters context manager (__enter__)
    ExitContext,             // Exits context manager (__exit__)

    RaiseException,          // Raises an exception (raise)
    SetupExceptBlock,        // Setups the handler for an exception id (except)
    ExitExceptBlock,         // Deletes handler for exception id
    FinallyBlock,            // Setups a final execution block (finally)

    Yield,                   // Yields a value (yield)
    YieldFrom,               // Yields a value from another generator (yield from)
    Await,                   // Awaits a coroutine

    Map,                     // Maps first operand to second operand in nested context
    Jump,                    // Jumps to code section directly
    Branch,                  // Conditionally jumps to section if condition is true,
    Call,                    // Calls a callable (either executes a function or calls __call__)
    Return                   // Returns From a function
  };

  /// The most primitive unit of bitcode is an instruction. It describes the
  /// operation to commit and any arguments if needed and operates on a set
  /// of sizeof(size_t) / 2 number of virtual registers. Internally an
  /// instruction is simply an opcode and 1 or 2 operands. For Load and Store
  /// opcodes, operand is whole size_t value that represents the pointer, and
  /// for other instructions, a single size_t value is split into 2 operands.
  /// These are interpreted as virtual registers. These are up to 4 billion
  /// virtual registers on 64-bit architectures that begin to route after the end.
  struct Instruction {
    Opcode Opcode;
    std::variant<void*, size_t> Operands;
  };


  typedef std::vector<Instruction> BasicBlock;

  class Module : public RangeBase<BasicBlock, Module> {
    public:
      Module() = default;
      Module(const Module&) = delete;
      Module(Module&&) noexcept = delete;

      Module& operator=(const Module&) = delete;
      Module& operator=(Module&&) noexcept = delete;
      BasicBlock& operator[](const std::string& key) noexcept;

      /// Adds a basic block to the module under the given key.
      /// @param key The key the basic block is available for jumping.
      /// @param bb The basic block to store in the module.
      void InsertBasicBlock(const std::string& key, const BasicBlock& bb) noexcept;

      /// Retrieves list of modules that were imported in the module. Each
      /// element is a typically short string that represent the import
      /// name, like "sys", "os" or any other package name. This method is
      /// useful to obtain what the module depends on and link it later with
      /// the module once it's loaded using Link.
      /// @return Imported packages names.
      [[nodiscard]] std::vector<std::string> GetImportModules() noexcept;

      /// Resolves symbols of module with the dependency. The dependency
      /// represents another module that this module imports, and this
      /// method resolves the symbols from it to invoke it correctly.
      /// @param dependency The imported module whose symbols are resolved.
      /// @return Reference to self to chain link calls.
      Module& Link(const Module& dependency) noexcept;

    private:
      absl::flat_hash_map<std::string, BasicBlock> Blocks;
      std::vector<std::string> StaticCodeSection;
      std::vector<std::string> ImportDeclaredNames;
  };
}
#endif //QUASAR_BITCODE_HPP
