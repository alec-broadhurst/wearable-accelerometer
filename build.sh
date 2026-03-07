BUILD_DIR=build

cmake -DCMAKE_TOOLCHAIN_FILE=cmake/avr-toolchain.cmake -S . -B $BUILD_DIR

cmake --build "$BUILD_DIR"

ln -sf "$BUILD_DIR/compile_commands.json" compile_commands.json

echo "Build complete. HEX file in $BUILD_DIR."
