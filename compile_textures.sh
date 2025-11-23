SCRIPT="build_scripts/compile_textures.py"
FROM_DIR="assets/textures/"
TO_DIR="include/assets/textures_precomped.h"

python "$SCRIPT" "$FROM_DIR" "$TO_DIR"