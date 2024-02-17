{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShellNoCC {
  packages = with pkgs; [
    llvmPackages_latest.clang-unwrapped
    llvmPackages_latest.lld
    python3
  ];

  shellHook = ''
    function serve() {
        python3 -m http.server
    }
  '';
}

