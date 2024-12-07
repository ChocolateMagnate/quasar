#ifndef QUASAR_PARSER_HPP
#define QUASAR_PARSER_HPP

#include <quasar/Bitcode.hpp>

namespace quasar {
  /// Parses the source code into bitcode module. Parser expects the code to
  /// contain the entire file through a char pointer. Tip: use memory-mapped
  /// files to efficiently load files and the pointer you get can be passed
  /// here directly. Raises InvalidSyntaxException if source file contains
  /// invalid syntax.
  /// @param source The pointer to source buffer terminated by NULL character.
  /// @throws InvalidSyntaxException if source is invalid Python
  /// @return Bitcode module object for the given source file.
  [[nodiscard]] bitcode::Module Parse(const char* source);
}
#endif //QUASAR_PARSER_HPP
