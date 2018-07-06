SRC_DIR=./
DST_DIR=./out
protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/config.proto
