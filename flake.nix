{
  description = "Development shell with clang14, cmake, doxygen, and common development tools";

  inputs = {
    # Use the unstable channel to pick up recent llvmPackages_14
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs, ... }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs { inherit system; config = {}; };
      # Pick clang 14 toolset
      llvm = pkgs.llvmPackages_21;
    in {
      devShells = {
        # Enable `nix develop` on x86_64 Linux
        "${system}" = {
          default = (pkgs.mkShell.override {stdenv = llvm.stdenv;}) {
            hardeningDisable = [ "all" ];
            # BuildTime
            nativeBuildInputs = with pkgs; [
              cmake
              clang-analyzer
            ];
            # Runtime or linking
            # dnf install git gcc clang clang-analyzer cmake make libev libev-devel 
            # openssl openssl-devel systemd systemd-devel zlib zlib-devel 
            # libzstd libzstd-devel lz4 lz4-devel libssh libssh-devel 
            # libcurl libcurl-devel python3-docutils libatomic 
            # bzip2 bzip2-devel libarchive libarchive-devel libasan libasan-static
            buildInputs = with pkgs; [
              libev
              openssl
              systemdLibs
              zlib
              zstd
              lz4
              libssh
              curlFull
              (python3.withPackages (ps: with ps; [
                docutils     
              ]))
              gccForLibs # includes libatomic, libasan
              bzip2
              libarchive
              libyaml
            ];

            # Optional: set common environment variables
            shellHook = ''
              echo "pgmoneta devshell"
              '';
          };
        };
      };
    };
}
