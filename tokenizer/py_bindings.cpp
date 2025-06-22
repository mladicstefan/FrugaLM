#include "tokenizer.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(tokenizer, m) {
    m.doc() = "SentencePiece Tokenizer Python bindings";
    py::class_<Tokenizer>(m, "Tokenizer")
        .def(py::init<const std::string&>(), "Constructor that loads model from path")
        .def("encode", &Tokenizer::encode, "Encode text to token IDs")
        .def("decode", &Tokenizer::decode, "Decode token IDs to text")
        .def("readFile", &Tokenizer::readFile, "Read file contents as string")
        .def("encode_future", &Tokenizer::encode_future, "Async encode text to token IDs")
        .def("decode_future", &Tokenizer::decode_future, "Async decode token IDs to text");
}
