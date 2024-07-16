{ pkgs ? import <nixpkgs> {} }: 
let debugger = if pkgs.system == "aarch64-darwin" then pkgs.lldb else pkgs.gdb; 
in pkgs.mkShell {
  nativeBuildInputs = with pkgs; [ clang-tools_16 gcc debugger ];
}
