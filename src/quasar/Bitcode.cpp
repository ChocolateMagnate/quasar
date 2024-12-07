
#include <quasar/Bitcode.hpp>

namespace quasar::bitcode {
  BasicBlock& Module::operator[](const std::string& key) noexcept {
    return this->Blocks[key];
  }
  void Module::InsertBasicBlock(const std::string& key, const BasicBlock& bb) noexcept {
    this->Blocks[key] = bb;
  }

  std::vector<std::string> Module::GetImportModules() noexcept {
    return this->ImportDeclaredNames;
  }
}  // namespace quasar::bitcode