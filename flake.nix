{
  description = "todo-cpp";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = import nixpkgs { inherit system; };
      in
      {
        devShells.default = pkgs.mkShell {
          env = {
            CMAKE_PREFIX_PATH = "${pkgs.imgui}/lib/cmake:$CMAKE_PREFIX_PATH";
          };
          nativeBuildInputs = with pkgs; [
            pkg-config
            cmake
            clang
            gcc
            clang-tools
            glfw
            python312Packages.glad
            python312
            glm
            gf
            libGL
            imgui
          ];
        };
      }
    );
}
