#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity):s(""), cap(capacity), w_num(0), r_num(0) { }

size_t ByteStream::write(const string &data) {
    int buff_len = s.length();
    if (buff_len + static_cast<int>(data.length()) > cap) {
        s.append(data.substr(0, cap - buff_len));
        w_num += cap - buff_len;
        set_error();
        return cap - buff_len;
    }
    s.append(data);
    w_num += data.length();
    return data.length();
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    return s.substr(0, len);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    s = s.substr(len, s.length());
    r_num += len;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string tmp = s.substr(0, len);
    s = s.substr(len, s.length());
    r_num += len;
    return tmp;
}

void ByteStream::end_input() {_end = true;}

bool ByteStream::input_ended() const { return _end; }

size_t ByteStream::buffer_size() const { return s.length(); }

bool ByteStream::buffer_empty() const { return s.empty(); }

bool ByteStream::eof() const { return _end && s.empty(); }

size_t ByteStream::bytes_written() const { return w_num; }

size_t ByteStream::bytes_read() const { return r_num; }

size_t ByteStream::remaining_capacity() const { return cap - s.length(); }
