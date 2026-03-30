BUILD_DIR=build

if [ "$1" = "debug" ]; then
    DEBUG_FLAG="-DDEBUG_BUILD=ON"
else
    DEBUG_FLAG=""
fi

cmake -DCMAKE_TOOLCHAIN_FILE=cmake/avr-toolchain.cmake $DEBUG_FLAG -S . -B $BUILD_DIR

cmake --build "$BUILD_DIR"

ln -sf "$BUILD_DIR/compile_commands.json" compile_commands.json

echo "Build complete. HEX file in $BUILD_DIR."
