#include <quasar/Bitcode.hpp>

namespace quasar::bitcode {
  BasicBlock& Module::operator[](const std::string& key) noexcept {
    return this->Blocks[key];
  }

  void Module::InsertBasicBlock(const std::string& key, const BasicBlock& bb) noexcept {
    this->Blocks[key] = bb;
  }

  ModuleConfiguration Module::GetModuleConfiguration() const noexcept {
    return this->Config;
  }

  std::vector<std::string> Module::GetImportModules() noexcept {
    return this->ImportDeclaredNames;
  }

  Module& Module::Link(const Module& dependency) noexcept {
    for (const auto& [name, block] : dependency.Blocks)
      if (!name.starts_with("__")) this->Blocks[name] = block;

    this->StaticCodeSection.insert(this->StaticCodeSection.end(),
                                  dependency.StaticCodeSection.begin(),
                                  dependency.StaticCodeSection.end());

    return *this;
  }
}  // namespace quasar::bitcode