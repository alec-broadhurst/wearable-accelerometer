BUILD_DIR=build
MODE="$1"

if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR"
fi

case $MODE in
    debug)
        BUILD_FLAG="-DDEBUG_BUILD=ON"
        ;;
    sim)
        BUILD_FLAG="-DSIM_BUILD=ON"
        ;;
    "")
        BUILD_FLAG="" # release
        ;;
    *)
        echo "Usage: $0 [debug|sim]"
        exit 1
        ;;
esac

cmake -DCMAKE_TOOLCHAIN_FILE=cmake/avr-toolchain.cmake $BUILD_FLAG -S . -B $BUILD_DIR

cmake --build "$BUILD_DIR"

ln -sf "$BUILD_DIR/compile_commands.json" compile_commands.json

echo "Build complete. HEX file in $BUILD_DIR."
