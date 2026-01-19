{
  description = "QMK environment for qmk_firmware/dev_branch";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    systems.url = "github:nix-systems/default";
  };

  outputs =
    { nixpkgs, systems, ... }:
    let
      eachSystem = nixpkgs.lib.genAttrs (import systems);
    in
    {
      devShells = eachSystem (
        system:
        let
          pkgs = import nixpkgs { inherit system; };
        in
        {
          default = pkgs.mkShell {
            name = "qmk-devshell";
            packages = with pkgs; [
              clang-tools
              dos2unix
              gnumake
              qmk

              # ARM Toolchain (RP2040 / Elite-Pi)
              gcc-arm-embedded

              # Flashing utilities
              dfu-programmer
              dfu-util

              (writeShellScriptBin "build-crkbd" ''
                exec ${pkgs.qmk}/bin/qmk compile -kb crkbd/rev4_1/standard -km hop
              '')
              (writeShellScriptBin "generate-compile-commands" ''
                exec ${pkgs.qmk}/bin/qmk compile -kb crkbd/rev4_1/standard -km hop --compiledb
              '')
              (writeShellScriptBin "flash-crkbd" ''
                exec ${pkgs.qmk}/bin/qmk flash -kb crkbd/rev4_1/standard -km hop
              '')
            ];

            shellHook = /* bash */ ''
              if ! git remote | grep -q "upstream"; then
                echo "Configuring upstream remote..."
                git remote add upstream https://github.com/qmk/qmk_firmware.git
              fi

              export NIX_CLANGD_PATH="${pkgs.clang-tools}/bin/clangd"
              export QMK_HOME=$(git rev-parse --show-toplevel) || exit
              export XDG_CONFIG_DIRS="$QMK_HOME/.nvim_config:$XDG_CONFIG_DIRS"

              echo "QMK_HOME set to $QMK_HOME"
              echo "Added neovim config: $QMK_HOME/.nvim_config"
              echo "Using QMK from: ${pkgs.qmk}"
              echo "Run 'qmk setup' if this is your first time."

              command zsh && exit
            '';
          };
        }
      );
    };
}
