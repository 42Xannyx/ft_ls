{
  pkgs ? import <nixpkgs> { },
}:

pkgs.mkShell {
  buildInputs = with pkgs; [
    gnumake
    gcc
    bear
    gdb
    valgrind
  ];
}
