main:
        cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build
        make -C build
run:
        cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build
        make -C build
        ./build/gl-playground


