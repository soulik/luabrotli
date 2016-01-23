cmake_minimum_required (VERSION 3.1.0)
project (brotli)

include_directories(dependencies/brotli/dec)
include_directories(dependencies/brotli/enc)

set(brotli_enc_src
    ../../dependencies/brotli/enc/backward_references.cc
    ../../dependencies/brotli/enc/block_splitter.cc
    ../../dependencies/brotli/enc/brotli_bit_stream.cc
    ../../dependencies/brotli/enc/compress_fragment.cc
    ../../dependencies/brotli/enc/compress_fragment_two_pass.cc
    ../../dependencies/brotli/enc/dictionary.cc
    ../../dependencies/brotli/enc/encode.cc
    ../../dependencies/brotli/enc/encode_parallel.cc
    ../../dependencies/brotli/enc/entropy_encode.cc
    ../../dependencies/brotli/enc/histogram.cc
    ../../dependencies/brotli/enc/literal_cost.cc
    ../../dependencies/brotli/enc/metablock.cc
    ../../dependencies/brotli/enc/static_dict.cc
    ../../dependencies/brotli/enc/streams.cc
    ../../dependencies/brotli/enc/utf8_util.cc
)

set(brotli_enc_h
    ../../dependencies/brotli/enc/backward_references.h
    ../../dependencies/brotli/enc/bit_cost.h
    ../../dependencies/brotli/enc/block_splitter.h
    ../../dependencies/brotli/enc/brotli_bit_stream.h
    ../../dependencies/brotli/enc/cluster.h
    ../../dependencies/brotli/enc/command.h
    ../../dependencies/brotli/enc/compress_fragment.h
    ../../dependencies/brotli/enc/compress_fragment_two_pass.h
    ../../dependencies/brotli/enc/context.h
    ../../dependencies/brotli/enc/dictionary.h
    ../../dependencies/brotli/enc/dictionary_hash.h
    ../../dependencies/brotli/enc/encode.h
    ../../dependencies/brotli/enc/encode_parallel.h
    ../../dependencies/brotli/enc/entropy_encode.h
    ../../dependencies/brotli/enc/entropy_encode_static.h
    ../../dependencies/brotli/enc/fast_log.h
    ../../dependencies/brotli/enc/find_match_length.h
    ../../dependencies/brotli/enc/hash.h
    ../../dependencies/brotli/enc/histogram.h
    ../../dependencies/brotli/enc/literal_cost.h
    ../../dependencies/brotli/enc/metablock.h
    ../../dependencies/brotli/enc/port.h
    ../../dependencies/brotli/enc/prefix.h
    ../../dependencies/brotli/enc/ringbuffer.h
    ../../dependencies/brotli/enc/static_dict.h
    ../../dependencies/brotli/enc/static_dict_lut.h
    ../../dependencies/brotli/enc/streams.h
    ../../dependencies/brotli/enc/transform.h
    ../../dependencies/brotli/enc/types.h
    ../../dependencies/brotli/enc/utf8_util.h
    ../../dependencies/brotli/enc/write_bits.h
)

set(brotli_dec_src
    ../../dependencies/brotli/dec/bit_reader.c
    ../../dependencies/brotli/dec/decode.c
    ../../dependencies/brotli/dec/dictionary.c
    ../../dependencies/brotli/dec/huffman.c
    ../../dependencies/brotli/dec/state.c
    ../../dependencies/brotli/dec/streams.c
)

set(brotli_dec_h
    ../../dependencies/brotli/dec/bit_reader.h
    ../../dependencies/brotli/dec/context.h
    ../../dependencies/brotli/dec/decode.h
    ../../dependencies/brotli/dec/dictionary.h
    ../../dependencies/brotli/dec/huffman.h
    ../../dependencies/brotli/dec/port.h
    ../../dependencies/brotli/dec/prefix.h
    ../../dependencies/brotli/dec/state.h
    ../../dependencies/brotli/dec/streams.h
    ../../dependencies/brotli/dec/transform.h
    ../../dependencies/brotli/dec/types.h
)

set(brotli_sources
	${brotli_enc_src} ${brotli_enc_h} ${brotli_dec_src} ${brotli_dec_h}
)

add_library(brotli STATIC
	${brotli_sources}
)

set_target_properties(brotli
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_SYSTEM_PROCESSOR}/bin"
)

target_link_libraries (brotli
)

