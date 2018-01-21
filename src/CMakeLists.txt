cmake_minimum_required(VERSION 3.9)
project(tinf C)

set(CMAKE_C_STANDARD 11)

add_executable(huffman_coder huffman_coder.c graph.h graph.c list.c list.h reader.c reader.h types.h)
add_executable(huffman_decoder huffman_decoder.c trie.c trie.h graph.h graph.c reader.h reader.c types.h)
add_executable(lzw_coder lzw_coder.c trie.c trie.h reader.c reader.h graph.h graph.c types.h)
add_executable(lzw_decoder lzw_decoder.c trie.c trie.h reader.c reader.h graph.h graph.c types.h)
